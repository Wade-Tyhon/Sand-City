#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../ngin64/nGin64.h"

#include "SC_Interface.h"

//extern void g64_ControllerInput();
//Gin64_GameplayInput
/*
extern gl_XP64_Vert vert_SelectStructureUI[];
extern uint16_t poly_SelectStructureUI[];
extern uint16_t SCGet_poly_SelectStructureUI_Size();

extern gl_XP64_Vert vert_SelectGroundUI[];
extern uint16_t poly_SelectGroundUI_Beach[];
extern uint16_t SCGet_poly_SelectGroundUI_Beach_Size();
*/

extern cityState SC_CityStats;
extern playerState player;
void SC_Building_Update();


g64_GUI_Window currentStatsWindow = {
    true,//.active
    {250, 90}, //.pos
    {120, 130}, //.size
    //{255, 255, 255, 190} //.color
    {50, 150, 165, 190}, //.color
    false,
    {250, 90}, //.pos
    {120, 130}, //.size
    0,
};


void SC_Building_Menu_Window(g64_EventArgs* tempArgs);



/*typedef struct {
    Coords2 pos;    Coords2 size;    RGBA color;        }g64_GUI_Window; */


g64_GUI_TexWindow currentStatsTexWindow = {
    NULL,
    1,
    {250, 90}, //.pos
    {120, 130}, //.size
    {255, 255, 255, 190} //.color

};

//----- Note ----- Text Elements --------------------


g64_GUI_Text UI_BuildType = {
    "BRLNSDB", //UI Font Name
    {252, 67},
    {58, 138, 127 }, //Font color    
    "Building ",
};

g64_GUI_Text UI_Sand = {
    "BRLNSDB", //UI Font Name
    {275, 113}, //Screen Coordinates
    {160, 235, 235 }, //Font color    
    "Sand ",
};

g64_GUI_Text UI_Shells = {
    "BRLNSDB", //UI Font Name
    {275, 143},
    {160, 235, 235 }, //Font color     
    "Shells ",
};

g64_GUI_Text UI_Residents = {
    "BRLNSDB", //UI Font Name
    {275, 173},
    {160, 235, 235 }, //Font color    
    "Residents ",
};

g64_GUI_Text UI_Buildings = {
    "BRLNSDB", //UI Font Name
    {275, 203},
    {160, 235, 235 }, //Font color    
    "Buildings ",
};

g64_GUI_Text* PlayfieldUI_Elements[5] = {
    &UI_Sand, &UI_Shells, &UI_BuildType, &UI_Residents, &UI_Buildings
};


//----- Note ----- Sprite Elements --------------------

const int guiSpritesTotal = 15;
sprite_t* guiSprites[15];

static const char* guiSprites_path[15] = {
    "rom:/circle0.sprite",
    "rom:/diamond0.sprite",
    "rom:/pentagon0.sprite",
    "rom:/ui/UI_Icon_Castle_1.ci4.sprite",
    "rom:/ui/UI_Icon_Castle_2.ci4.sprite",
    "rom:/ui/UI_Icon_Castle_3.ci4.sprite",
    "rom:/ui/UI_Icon_Crab_1.ci4.sprite",
    "rom:/ui/UI_Icon_Crab_2.ci4.sprite",
    "rom:/ui/UI_Icon_Sand_1.ci4.sprite",
    "rom:/ui/UI_Icon_Dollar_1.ci4.sprite",
    "rom:/ui/UI_Icon_Dollar_2.ci4.sprite",
    "rom:/ui/UI_Icon_Dollar_3.ci4.sprite",
    "rom:/ui/UI_Icon_Dollar_4.ci4.sprite",
    "rom:/ui/UI_Icon_Dollar_5.ci4.sprite",
    "rom:/ui/UI_Icon_Dollar_6.ci4.sprite",
};

g64_GUI_Sprite UI_CastleIcon = {
    NULL, // .sprite (initially set as NULL, a reference is given in "SC_Interface_Init"
    2, //.spriteID
    {258, 10}, //.pos
    {0.5f, 0.5f}, //.scl
    {58, 138, 127 }, //.color
    false, //.alpha
    255, //.transparency
};


g64_GUI_Sprite UI_SandIcon = {
    NULL, // .sprite (initially set as NULL, a reference is given in "SC_Interface_Init"
    8, //.spriteID
    {258, 100}, //.pos
    {0.5f, 0.5f}, //.scl
    {58, 138, 127 }, //.color
    false, //.alpha
    255, //.transparency
};


g64_GUI_Sprite UI_ShellsIcon = {
    NULL, // .sprite (initially set as NULL, a reference is given in "SC_Interface_Init"
    9, //.spriteID
    {258, 130}, //.pos
    {0.5f, 0.5f}, //.scl
    {58, 138, 127 }, //.color
    false, //.alpha
    255, //.transparency
};


g64_GUI_Sprite UI_ResidentsIcon = {
    NULL, // .sprite (initially set as NULL, a reference is given in "SC_Interface_Init"
    6, //.spriteID
    {258, 160}, //.pos
    {0.5f, 0.5f}, //.scl
    {58, 138, 127 }, //.color
    false, //.alpha
    255, //.transparency
};

g64_GUI_Sprite UI_PropertiesIcon = {
    NULL, // .sprite (initially set as NULL, a reference is given in "SC_Interface_Init"
    3, //.spriteID
    {258, 190}, //.pos
    {0.5f, 0.5f}, //.scl
    {58, 138, 127 }, //.color
    false, //.alpha
    255, //.transparency
};


const int guiPlayfieldIconsTotal = 5;
g64_GUI_Sprite* UI_PlayfieldIcons[5] = {
    &UI_SandIcon,       &UI_ShellsIcon,     &UI_ResidentsIcon,   &UI_PropertiesIcon,    &UI_CastleIcon
};



char BuildTypeText;
u8 variableTest = 1;

void SC_Interface_Init() {


    SC_Playfield_Structure_Menu_Init();
    gin64_Event_Subscribe(&BuildMenuEvent.OnTrigger, &SC_Building_Menu_Window);

#ifdef DEBUG_NGIN64_INTERFACE    
    fprintf(stderr, "\n > RUN SC_Interface_Init!\n");
#endif

    SC_Playfield_Cursor_Init();
    gin64_GUI_Init();

    for (uint32_t i = 0; i < guiSpritesTotal; i++)    {
        guiSprites[i] = sprite_load(guiSprites_path[i]);
    }

    for (uint32_t i = 0; i < guiPlayfieldIconsTotal; i++) {
       // guiSprites[i] = sprite_load(guiSprites_path[i]);
        UI_PlayfieldIcons[i]->sprite = guiSprites[UI_PlayfieldIcons[i]->spriteID];
    }



    SC_Title_Menu_Init();

}



void SC_Interface_Update() {

#ifdef DEBUG_NGIN64_INTERFACE
	//fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
	fprintf(stderr, "\n > RUN SC_Interface_Update!\n");
#endif





    if (SC_GameState.titleScreen.active) { //If playfield object menu is active

        //SC_PlayfieldOpenMenu_Update();
        //SC_Menu_Building_Update();


        SC_Title_Screen_Update();
    }

    else if (SC_GameState.pauseScreen.active) {

        //Do nothing...
    }

    else if (SC_GameState.playfieldMenu.active) { //If playfield object menu is active
    
        SC_PlayfieldOpenMenu_Update();
        //SC_Menu_Building_Update();
    }

    

    else if (!SC_GameState.playfieldMenu.active) { //If playfield object menu is not active
        SC_Playfield_Cursor_Update();
        SC_Building_Update();
    }



}





void SC_Interface_Draw() {


    



    if (SC_GameState.titleScreen.active) { //If playfield object menu is active
    
        //SC_Playfield_Cursor_Draw();
        
        SC_Title_Menu_Draw();








        glPushMatrix();
        glColor3f(1, 1, 1);

        glDisableClientState(GL_VERTEX_ARRAY);

        glDisableClientState(GL_COLOR_ARRAY);
        glEnable(GL_CULL_FACE);
        glDepthMask(GL_TRUE);
        glDisable(GL_ALPHA_TEST);
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_FOG);

        glPopMatrix();



    }

   

    
    if (SC_GameState.playfieldMain.active) {
        SC_Playfield_Cursor_Draw();


        gin64_GUI_Window_Draw(&currentStatsWindow);

        if (SC_GameState.playfieldMenu.active) {

            SC_Playfield_Structure_Menu_Draw();
            // gin64_GUI_Window_Draw(&buildingMenuWindow);
            // gin64_GUI_Menu_Draw(&MenuList_EditStructures);
        }

        if (SC_GameState.pauseScreen.active) {

           // gin64_GUI_Text_Draw(&UI_Shells);
          //  gin64_GUI_Text_Draw(&UI_Sand);

            SC_Playfield_Pause_Menu_Draw();

        }
        //gin64_GUI_TexWindow_Draw(&currentStatsTexWindow);


        for (uint32_t i = 0; i < guiPlayfieldIconsTotal - 1; i++) {
            // guiSprites[i] = sprite_load(guiSprites_path[i]);
            gin64_GUI_Sprite_Draw(UI_PlayfieldIcons[i]);
            //UI_PlayfieldIcons[i]->sprite = guiSprites[UI_PlayfieldIcons[i]->spriteID];
        }

        // rdpq_font_begin(RGBA32(UI_BuildType.color.r, UI_BuildType.color.g, UI_BuildType.color.b, 255));
        gin64_GUI_Text_Draw(&UI_BuildType);
        //  rdpq_font_begin(RGBA32(UI_Shells.color.r, UI_Shells.color.g, UI_Shells.color.b, 255));
        gin64_GUI_Text_Draw(&UI_Shells);
        gin64_GUI_Text_Draw(&UI_Sand);
        gin64_GUI_Text_Draw(&UI_Residents);
        gin64_GUI_Text_Draw(PlayfieldUI_Elements[4]);
    }

}



extern enum g64_EditModeState editModeState;
extern enum g64_BuildingTypeState buildingTypeState;
extern enum g64_LandscapeTypeState landscapeTypeState;

extern enum g64_PlayfieldEventState playfieldEventState;





void SC_Building_Update() {

    sprintf(UI_Residents.write, "%i", SC_CityStats.residents);
    sprintf(UI_Buildings.write, "%i", SC_CityStats.buildings);
    sprintf(UI_Sand.write, "%i", SC_CityStats.mat_sand);
    sprintf(UI_Shells.write, "%i", SC_CityStats.mat_shells);



    if(editModeState == Building){

        switch (buildingTypeState) {

            case(1):
                sprintf(UI_BuildType.write, "Small");
                break;
            case(2):
                sprintf(UI_BuildType.write, "Large");
                break;
            case(3):                  
                sprintf(UI_BuildType.write, "Watch");
                break;
            case(4):
                sprintf(UI_BuildType.write, "Lighthouse");
                break;
            case(5):
                sprintf(UI_BuildType.write, "Office");
                break;
            case(6):
                sprintf(UI_BuildType.write, "Condo");
                break;
            case(7):
                sprintf(UI_BuildType.write, "Powerplant");
                break;
            case(8):
                sprintf(UI_BuildType.write, "Walls");
                break;
            default:
                sprintf(UI_BuildType.write, "None");
                break;

        }
    }
    
    else if (editModeState == Landscape) {

        switch (landscapeTypeState) {

        case(1):
            sprintf(UI_BuildType.write, "Ground");
            break;
        case(2):
            sprintf(UI_BuildType.write, "Water");
            break;
        default:
            sprintf(UI_BuildType.write, "None");
            break;

        }
    }
    
}




void SC_Building_Menu_Window(g64_EventArgs* tempArgs) {

    SC_GameState.playfieldMenu.active = true;

}