#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../ngin64/nGin64.h"
#include "SC_Interface.h"
#include "../scenes/prefabs/castles/SC_CastlesTypes.h"

//g64_GUIEvent PlayfieldObjectEvent;
//g64_GameTimer PlayfieldObjectDelayTimer = { 0, 0, 1.0f };



/*----- Note -----	Set up all events here in UI Events
*					- create an enum for g64_PlayfieldEventState
*                   - create an enum for g64_BuildSelectionState
*                   - navigate these states inside of 'SC_Events_Update()'
*                   - add object placement functionality back into gameplay using events

*/

//enum ObjectEventEnum



enum g64_PlayfieldEventState playfieldEventState;

/* enum g64_EditModeState {
    NoEditMode,    Landscaping,    Building,    EditModeSize }; */

enum g64_EditModeState editModeState;
//bool EditModeSwitch

/* enum g64_LandscapeTypeState {
    NoLandscaping,    Dirt,    Water,    LandscapingTypeSize };*/
enum g64_LandscapeTypeState landscapeTypeState;

/* enum g64_BuildingTypeState {
    NoBuildingType,    SmallTower, LargeTower,    WatchTower, Lighthouse,    OfficeBuilding, Condomenium,    PowerPlant, Walls,    BuildingTypeSize };*/
enum g64_BuildingTypeState buildingTypeState;


/* enum g64_PlayfieldEventState {
    NoState,    Build, Demolish, Repair,    Examine,    Dig, Fill,    EndState}; */

//void SC_PlayfieldEvent_Handler(g64_Event* thisEvent);
void SC_PlayfieldEvent_Handler(g64_Event* thisEvent, char name[16]);
g64_PlayfieldEvent PlayfieldEvent;
g64_GameTimer PlayfieldDelay = { 0, 0, 1.0f };


g64_PlayfieldEvent BuildTypeChangeEvent;

g64_PlayfieldEvent LandscapeEvent;

g64_PlayfieldEvent BuildObjectEvent;



g64_PlayfieldEvent DemolishObjectEvent;
g64_PlayfieldEvent RepairObjectEvent;
g64_PlayfieldEvent ExamineObjectEvent;
g64_PlayfieldEvent DigPlotEvent;
g64_PlayfieldEvent FillPlotEvent;

g64_TimeEvent PropertyTaxEvent;
g64_TimeEvent SalesTaxEvent;
g64_GameTimer tempTimer = { 0, 1, 10.0f };

void SC_BuildingType_Handler();
void SC_BuildingEvent_Update();
void SC_TestEventHandler();



void SC_Events_Init() {

    //----- Note ----- Playfield Events
    gin64_Event_Init(&BuildObjectEvent);
    gin64_PlayfieldEvent_Set("Building", &BuildObjectEvent, &playfieldCursor, &SC_PlayfieldEvent_Handler);

    gin64_Event_Init(&LandscapeEvent);
    gin64_PlayfieldEvent_Set("Landscape", &LandscapeEvent, &playfieldCursor, &SC_PlayfieldEvent_Handler);

    gin64_Event_Init(&BuildTypeChangeEvent);
    gin64_PlayfieldEvent_Set("Build Type", &BuildTypeChangeEvent, &playfieldCursor, &SC_BuildingType_Handler);


    //----- Note ----- Timed Events

    tempTimer = gin64_SetGameTimer(0, 1, 10.0f);
    gin64_Event_Init(&SalesTaxEvent);
    gin64_TimeEvent_Set("Sales Tax Event", &SalesTaxEvent, tempTimer, true);

    tempTimer = gin64_SetGameTimer(0, 0, 30.0f);
    gin64_Event_Init(&PropertyTaxEvent);
    gin64_TimeEvent_Set("Sales Tax Event", &PropertyTaxEvent, tempTimer, true);

    editModeState = Building;
    landscapeTypeState = Dirt;
    buildingTypeState = SmallTower;

}

u8 currentEditingMode;
u8 currentBuildingType;
u8 currentLandscapeType;


void SC_TestEventHandler() {
    fprintf(stderr, "\nCalling SC_TestEventHandler() '\n\n");
}


void SC_BuildingType_Handler() {

    fprintf(stderr, "\nCalling SC_BuildingType_Handler() '\n\n");

    //----- Note ----- Switch between edit modes (landscaping, buildings, etc

    currentEditingMode = editModeState;
    
    if (g64_Pad[0].Press.C_Down == 1) {


        if (currentEditingMode == 0)
            currentEditingMode += 1;
        else if ((currentEditingMode + 1) < EditModeSize) {
            currentEditingMode += 1;
        }

        
        else {
            currentEditingMode = 1;
        }
    }
    editModeState = currentEditingMode;
    //editModeState

    currentLandscapeType = landscapeTypeState;
    currentBuildingType = buildingTypeState;

    if (editModeState == Building) {
        if (g64_Pad[0].Press.C_Right == 1) {

            if ((currentBuildingType + 1) < BuildingTypeSize) {
                currentBuildingType += 1;
            }
            else {
                currentBuildingType = 1;
            }
        }

        else if (g64_Pad[0].Press.C_Left == 1) {
            if ((currentBuildingType - 1) > NoBuildingType) {
                currentBuildingType -= 1;
            }

            else
                currentBuildingType = BuildingTypeSize - 1;
        }

        buildingTypeState = currentBuildingType;
    }

    else if (editModeState == Landscape) {
        if (g64_Pad[0].Press.C_Right == 1) {

            if ((currentLandscapeType + 1) < LandscapeTypeSize) {
                currentLandscapeType += 1;
            }
            else {
                currentLandscapeType = 1;
            }
        }

        else if (g64_Pad[0].Press.C_Left == 1) {
            if ((currentLandscapeType - 1) > NoLandscape) {
                currentLandscapeType -= 1;
            }

            else
                currentLandscapeType = LandscapeTypeSize - 1;
        }

        landscapeTypeState = currentLandscapeType;
    }

}

char tempName[12] = "Fill";

//if (strcmp(update, "Dig") == 0) {

void SC_PlayfieldEvent_Handler(g64_Event* thisEvent, char name[16]) {
    if (g64_Pad[0].Press.A == 1) {

        if (editModeState == Landscape && (strcmp(name, "Landscape") == 0)) {        

            thisEvent->args.trigger = true;
            sprintf(thisEvent->args.key, "Fill");
        }

        //tempName = "Building";
        if (editModeState == Building && (strcmp(name, "Building") == 0)) {
            thisEvent->args.trigger = true;
            sprintf(thisEvent->args.key, "Build");
        }        
    }

    else if (g64_Pad[0].Press.B == 1) {

        if (editModeState == Landscape && (strcmp(name, "Landscape") == 0)) {

            thisEvent->args.trigger = true;
            sprintf(thisEvent->args.key, "Dig");
        }

        //tempName = "Building";
        if (editModeState == Building && (strcmp(name, "Building") == 0)) {
            thisEvent->args.trigger = true;
            sprintf(thisEvent->args.key, "Demolish");
        }
    }
}

