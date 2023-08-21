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

void SC_PlayfieldEvent_Handler(g64_Event* thisEvent, char name[16]);
extern void SC_PlayfieldOpenMenu_Handler(g64_Event* thisEvent, char name[16]);
g64_PlayfieldEvent PlayfieldEvent;
g64_GameTimer PlayfieldDelay = { 0, 0, 1.0f };


g64_PlayfieldEvent BuildTypeChangeEvent;

g64_PlayfieldEvent LandscapeEvent;

g64_PlayfieldEvent BuildObjectEvent;

g64_PlayfieldEvent BuildMenuEvent;




g64_PlayfieldEvent DemolishObjectEvent;
g64_PlayfieldEvent RepairObjectEvent;
g64_PlayfieldEvent ExamineObjectEvent;
g64_PlayfieldEvent DigPlotEvent;
g64_PlayfieldEvent FillPlotEvent;

g64_PlayfieldEvent PauseEvent;

g64_TimeEvent ErosionEvent;
g64_TimeEvent JobsCheckEvent;
g64_TimeEvent ResidentCheckEvent;

g64_TimeEvent PropertyTaxEvent;
g64_TimeEvent SalesTaxEvent;
g64_GameTimer tempTimer = { 0, 1, 10.0f };

void SC_BuildingType_Handler();
void SC_BuildingEvent_Update();
void SC_TestEventHandler();




//----- Notes ------ Title Screen Events ----------
g64_PlayfieldEvent OpenTitleMenuEvent;
g64_PlayfieldEvent SelectTitleMenuEvent;
//g64_PlayfieldEvent InstructionsMenuEvent;
g64_GameTimer LoadDelay = { 0, 0, 4.0f };




//------------------------------------------------



void SC_Events_Init() {

    //----- Note ----- Playfield Events
    gin64_Event_Init(&BuildObjectEvent);
    gin64_PlayfieldEvent_Set("Building", &BuildObjectEvent, &playfieldCursor, &SC_PlayfieldEvent_Handler);

    gin64_Event_Init(&LandscapeEvent);
    gin64_PlayfieldEvent_Set("Landscape", &LandscapeEvent, &playfieldCursor, &SC_PlayfieldEvent_Handler);

    gin64_Event_Init(&BuildTypeChangeEvent);
    gin64_PlayfieldEvent_Set("Build Type", &BuildTypeChangeEvent, &playfieldCursor, &SC_BuildingType_Handler);

    gin64_Event_Init(&BuildMenuEvent);
    gin64_PlayfieldEvent_Set("Build Menu", &BuildMenuEvent, &playfieldCursor, &SC_PlayfieldOpenMenu_Handler);

   // gin64_Event_Init(&DemolishObjectEvent);
   // gin64_PlayfieldEvent_Set("Build Menu", &DemolishObjectEvent, &playfieldCursor, &SC_PlayfieldOpenMenu_Handler);
   
    gin64_Event_Init(&OpenTitleMenuEvent);
    gin64_PlayfieldEvent_Set("Title Menu Event", &OpenTitleMenuEvent, &playfieldCursor, &SC_Title_Menu_Handler);

    
    gin64_Event_Init(&SelectTitleMenuEvent);
    gin64_PlayfieldEvent_Set("Title Menu Event", &SelectTitleMenuEvent, &playfieldCursor, &SC_Title_Selection_Handler);

    gin64_Event_Init(&PauseEvent);
    gin64_PlayfieldEvent_Set("Pause Event", &PauseEvent, &playfieldCursor, &SC_PauseEventHandler);

    
    /*
    gin64_Event_Init(&InstructionsMenuEvent);
    gin64_PlayfieldEvent_Set("Title Menu Event", &InstructionsMenuEvent, &playfieldCursor, &SC_Title_Menu_Handler);
    */
   
   
   //----- Note ----- Timed Events

    tempTimer = gin64_SetGameTimer(0, 1, 15.0f);
    gin64_Event_Init(&SalesTaxEvent);
    gin64_TimeEvent_Set("Sales Tax Event", &SalesTaxEvent, tempTimer, true);

    tempTimer = gin64_SetGameTimer(0, 2, 30.0f);
    gin64_Event_Init(&PropertyTaxEvent);
    gin64_TimeEvent_Set("Property Tax Event", &PropertyTaxEvent, tempTimer, true);

    tempTimer = gin64_SetGameTimer(0, 0, 25.0f);
    gin64_Event_Init(&ErosionEvent);
    gin64_TimeEvent_Set("Erosion Event", &ErosionEvent, tempTimer, true);

    tempTimer = gin64_SetGameTimer(0, 0, 15.0f);
    gin64_Event_Init(&JobsCheckEvent);
    gin64_TimeEvent_Set("Jobs Check Event", &JobsCheckEvent, tempTimer, true);

    tempTimer = gin64_SetGameTimer(0, 0, 30.0f);
    gin64_Event_Init(&ResidentCheckEvent);
    gin64_TimeEvent_Set("Resident Check Event", &ResidentCheckEvent, tempTimer, true);


    editModeState = Building;
    landscapeTypeState = Dirt;
    buildingTypeState = SmallTower;

}

u8 currentEditingMode;
u8 currentBuildingType;
u8 currentLandscapeType;


void SC_TestEventHandler() {
   // fprintf(stderr, "\nCalling SC_TestEventHandler() '\n\n");
}

void SC_PauseEventHandler(g64_Event* thisEvent, char name[16]) {
    // fprintf(stderr, "\nCalling SC_TestEventHandler() '\n\n");

    //SC_GameState.playfieldMenu.active

    if (SC_GameState.playfieldMain.active){

        if (thisEvent->args.constTrigger == false) {
            if (g64_Pad[0].Press.Start == 1) {

                //fprintf(stderr, "\n > RUN 'PAUSE' SC_PauseEventHandler!\n");

                SC_GameState.pauseScreen.active = true;
                thisEvent->args.constTrigger = true;
            }
        }

        else if (thisEvent->args.constTrigger == true) {
            if (g64_Pad[0].Press.Start == 1) {

                SC_GameState.pauseScreen.active = false;
                thisEvent->args.constTrigger = false;
            }
        }

    }
}

void SC_BuildingType_Handler() {

    //fprintf(stderr, "\nCalling SC_BuildingType_Handler() '\n\n");

    //----- Note ----- Switch between edit modes (landscaping, buildings, etc



    if (!SC_GameState.pauseScreen.active) {

        currentEditingMode = editModeState;


        if (SC_GameState.playfieldMenu.active) //If a playfield object menu is active, do not run this script
            return;


        /*
        if (g64_Pad[0].Press.C_Down == 1) {


            if (currentEditingMode == 0)
                currentEditingMode += 1;
            else if ((currentEditingMode + 1) < EditModeSize) {
                currentEditingMode += 1;
            }


            else {
                currentEditingMode = 1;
            }
        }*/

        if (g64_Pad[0].Press.L == 1) {
            currentEditingMode = Landscape;
            gin64_Audio_SFX_Play("rom:/MenuOpen1.wav64");
        }

        else if (g64_Pad[0].Press.R == 1) {
            currentEditingMode = Building;
            gin64_Audio_SFX_Play("rom:/MenuClose1.wav64");
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
                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }

            else if (g64_Pad[0].Press.C_Left == 1) {
                if ((currentBuildingType - 1) > NoBuildingType) {
                    currentBuildingType -= 1;
                }

                else
                    currentBuildingType = BuildingTypeSize - 1;
                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
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
                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }

            else if (g64_Pad[0].Press.C_Left == 1) {
                if ((currentLandscapeType - 1) > NoLandscape) {
                    currentLandscapeType -= 1;
                }

                else
                    currentLandscapeType = LandscapeTypeSize - 1;
                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }

            landscapeTypeState = currentLandscapeType;
        }

    }
}

char tempName[12] = "Fill";

void SC_PlayfieldEvent_Handler(g64_Event* thisEvent, char name[16]) {
    
    
    if (!SC_GameState.pauseScreen.active) {
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
                //  thisEvent->args.trigger = true;
              //    sprintf(thisEvent->args.key, "BuildMenu");

            }
        }
    }
}

extern playfieldState S_PlayfieldState_Current[16][7];


/*
void SC_PlayfieldOpenMenu_Handler(g64_Event* thisEvent, char name[16]) {

    if (S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.staticModel_LOD[2].glDisplayList) {

        fprintf(stderr, "\n > RUN SC_PlayfieldOpenMenu_Handler!\n");
        if (thisEvent->args.constTrigger == false && editModeState == Building && (strcmp(name, "Build Menu") == 0)) {

            if (g64_Pad[0].Press.B == 1) {
                fprintf(stderr, "\n >RUN SC_PlayfieldOpenMenu_Handler Menu Open!\n");
                thisEvent->args.constTrigger = true;
                SC_GameState.playfieldMenu.active = true;
                sprintf(thisEvent->args.key, "TriggerMenu");
            }

        }

        if (SC_GameState.playfieldMenu.active == false) {
            thisEvent->args.constTrigger = false;
        }
    }

}*/

void SC_PlayfieldOpenMenu_Handler_OLD(g64_Event* thisEvent, char name[16]) {

//#ifdef DEBUG_NGIN64_INTERFACE
    //fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
    

    //thisEvent->args.trigger = false;

    
    //if(S_PlayfieldState_Current[0][0].structure.staticModel_LOD[2].glDisplayList){
    if (S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.staticModel_LOD[2].glDisplayList) {

        //fprintf(stderr, "\n > RUN SC_PlayfieldOpenMenu_Handler!\n");
        if (thisEvent->args.constTrigger == false && editModeState == Building && (strcmp(name, "Build Menu") == 0)) {
            
            if (g64_Pad[0].Press.B == 1) {
                thisEvent->args.constTrigger = true;
                 sprintf(thisEvent->args.key, "TriggerMenu");            
            }

        }
    
        else if (thisEvent->args.constTrigger == true && editModeState == Building && (strcmp(name, "Build Menu") == 0)){
            //fprintf(stderr, "\n >RUN SC_PlayfieldOpenMenu_Handler Menu Open!\n");
            if (g64_Pad[0].Press.B == 1) {
                thisEvent->args.constTrigger = false;
                sprintf(thisEvent->args.key, "CloseMenu");

            }

            /*
            if (g64_Pad[0].Press.A == 1) {
                thisEvent->args.constTrigger = false;
                sprintf(thisEvent->args.key, "M_Demolish");

            }
            */
        }

    
        if (strcmp(thisEvent->args.key, "TriggerMenu") == 0) {
            SC_GameState.playfieldMenu.active = true;
            //fprintf(stderr, "\n > RUN Open Menu!\n");
        }
        
        else if (strcmp(thisEvent->args.key, "CloseMenu") == 0){
            SC_GameState.playfieldMenu.active = false;
            //fprintf(stderr, "\n > RUN Close Menu!\n");
        }
        /*
        else if (strcmp(thisEvent->args.key, "M_Demolish") == 0) {
            SC_GameState.playfieldMenu.active = false;
            //fprintf(stderr, "\n > RUN Close Menu and Demolish property!\n");
        }
        */
    
    }

}

