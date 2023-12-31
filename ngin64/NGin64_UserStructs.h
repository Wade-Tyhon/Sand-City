#ifndef TEST_H
#define TEST_H

#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "nGin64.h"

//int editableBlocks[16][7][4]

typedef struct {
	//For use with collision tests
	//u8 blockState[16][7][4]; //[Columns][Rows][update, groundHeight, structure, event]
	bool updating;
    bool cursorActive; //The cursor is currently placed over this element
	u8 groundHeight; //Position of playfield: standard, raised, lowered
	u8 water; // no water, high water, mid water, low water, 
	u8 strutureType; //House unit, tower, wall, lighthouse, etc
	u8 eventType; //0 by default (no event), other events could be: "new resident" "received power" "upgrading to new structure" "damaged by waves" etc
	u8 status; //New, damaged, deteriorating, destroyed
	bool power; //Is power available in this structure (if applicable)
	u8 residents; //Number of animal residents in this structure (if applicable)
    g64_EnvObjectPrefab structure;
	
}playfieldState;


typedef struct {

    int mat_sand;
    int mat_shells;

}playerState;

typedef struct {

    u8 propertyTaxRate;
    u8 salesTaxRate;
    u8 buildings;
    u8 jobs;
    u8 residents;    
    u8 mood;

    int expenses;

    int mat_sand;
    int mat_shells;
    
    //u8 mat_sand;
    //u8 mat_shells;

}cityState;


typedef struct {
    char* name;
    bool active;
}g64_PlayState;

typedef struct {

    g64_PlayState titleScreen;
    g64_PlayState titleMenuScreen;
    g64_PlayState titleInstruction;
    g64_PlayState beginNewGame;    
    g64_PlayState pauseScreen;
    g64_PlayState playfieldMain;
    g64_PlayState playfieldMenu;
    g64_PlayState playfieldObjMenu;
    g64_PlayState playfieldDialog;
    g64_PlayState playfieldFreeCam;

}g64_GameState;


/*
typedef struct {
    bool trigger;
    bool constTrigger;
    int i[3];
    float f[3];
    g64_GameTimer time;
    char key[12];
    char* keyB;
} g64_EventArgs;

extern g64_EventArgs defaultArgs;

typedef struct {
    char* name;
    //void (*listenerFunc)();
    void(*listenerFunc)(g64_EventArgs*);
}g64_EventListeners;

typedef struct {
    char* name;
    //g64_EventType* type;
    g64_EventArgs args;
    //g64_EventHandler* handler;
    void (*handlerFunc)();
    g64_EventListeners listeners[10];
} g64_Event;

*/





typedef struct {
    bool unlock_watchtower; //after certain conditions are met, allow the user to place walls
    bool unlock_wall; //after certain conditions are met, allow the user to place walls
    bool unlock_lighthouse; //after certain conditions are met, allow the user to place a single lighthouse on the playfield
    bool unlock_powerplant;
    bool unlock_condo;
    bool unlock_office;
}g64_GameFlags;

typedef struct {

    InputVector2 cursor; //D Pad, C Pad  or Analog - selecting which tile to interact with
    InputVector2 camera; //C Buttons - rotate around the currently selected object and select a camera mode (c left and c right rotates, c up changes camera mode, c down zooms into inspect current tile
    InputButton confirm; //A button
    InputButton cancel; //B button

    InputButton speed; //R - toggles simulation speed
    InputButton pause; //START - Open pause menu
    InputButton menu1; //Z - toggles menu to select 
    InputVector2 menuH; //Nav menu horizontal movement
    InputVector2 menuV; //Nav menu vertical movement

}g64_GameplayInput;

typedef struct {

    InputVector2 menuH; //Nav menu horizontal movement
    InputVector2 menuV; //Nav menu vertical movement
    InputButton select;
    InputButton cancel;
    InputButton nextWindow;
    InputButton previousWindow;

}g64_MenuInput;


#endif