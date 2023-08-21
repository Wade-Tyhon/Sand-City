#ifndef SC_INTERFACE_H
#define SC_INTERFACE_H

#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../ngin64/nGin64.h"

/**/



//----- Note ----- Menu Functions
extern void SC_Playfield_Structure_Menu_Init();
extern void SC_Playfield_Structure_Menu_Update();
extern void SC_Playfield_Structure_Menu_Draw();

extern void SC_Playfield_Pause_Menu_Draw();

extern void SC_PlayfieldOpenMenu_EventListener(g64_EventArgs* tempArgs);
extern void SC_PlayfieldOpenMenu_Update();

extern void SC_NewGame_MenuEvent(char* keyWord);
extern void SC_Instructions_MenuEvent(char* keyWord);

extern g64_Menu_Collections MenuList_EditStructures;


//----- Note ----- Title Screen Menu Functions
extern void SC_Title_Menu_Init();
extern void SC_Title_Menu_Handler(g64_Event* thisEvent, char name[16]);
extern void SC_Title_Start_EventListener(g64_EventArgs* tempArgs);
extern void SC_Title_Instructions_EventListener(g64_EventArgs* tempArgs);
extern void SC_Title_Selection_Handler(g64_Event* thisEvent, char name[16]);

extern void SC_Title_Screen_Update();
extern void SC_Title_Menu_Draw();



//----- Note ----- Playfield References
extern playerState player;
extern cityState SC_CityStats;
extern playfieldState S_PlayfieldState_Pending[16][7];
extern playfieldState S_PlayfieldState_Current[16][7];
extern Vector3 SCGet_Playfield_Tile_Position(int column, int row);
extern u8 SC_Set_PlayfieldTile(int column, int row, char update[12]);
extern void SC_PauseEventHandler(g64_Event* thisEvent, char name[16]);

extern enum g64_PlayfieldEventState playfieldEventState;
extern enum g64_EditModeState editModeState;
extern enum g64_LandscapeTypeState landscapeTypeState;
extern enum g64_BuildingTypeState buildingTypeState;


enum g64_EditModeState {

    NoEditMode,
    Landscape,
    Building,
    EditModeSize

};

enum g64_BuildingTypeState {

    NoBuildingType,
    SmallTower, LargeTower,
    WatchTower,
    BuildingTypeSize
    //WatchTower, Lighthouse,
    //OfficeBuilding, Condomenium,
    //PowerPlant, Walls,
    

};



enum g64_LandscapeTypeState {

    NoLandscape,
    Dirt,
    LandscapeTypeSize
    //Water,
    
};


enum g64_PlayfieldEventState {

    NoState,
    Build, Demolish, Repair,
    Examine,
    Dig, Fill,
    EndState
};

//----- Note ----- Controller Inputs
extern g64_Controller g64_Pad[4];


//----- Note ------ Assets
extern GLuint textures[16];

//----- Note ----- Interface Updates
extern void SC_Interface_Init();
extern void SC_Interface_Update();


//----- Note ----- Playfield Control References


//----- Note ----- Menu Control Updates


//----- Note ----- Playfield Control Updates
extern void SC_Playfield_Cursor_Init();
extern void SC_Playfield_Cursor_Update();
extern void SC_Playfield_Cursor_Draw();



//----- Note ----- UI Events

//extern g64_GUIEvent PlayfieldObjectEvent;
//extern g64_GameTimer PlayfieldObjectDelayTimer;



extern g64_TimeEvent ErosionEvent;
extern g64_TimeEvent JobsCheckEvent;
extern g64_TimeEvent ResidentCheckEvent;
extern g64_TimeEvent PropertyTaxEvent;
extern g64_TimeEvent SalesTaxEvent;
extern g64_GameTimer tempTimer;

extern g64_PlayfieldEvent PlayfieldEvent;
extern g64_GameTimer PlayfieldDelay;

extern g64_PlayfieldEvent BuildObjectEvent;
extern g64_PlayfieldEvent BuildTypeChangeEvent;
extern g64_PlayfieldEvent LandscapeEvent;
extern g64_PlayfieldEvent BuildMenuEvent;

extern void SC_Events_Init();
extern void SC_Events_Update();
#endif