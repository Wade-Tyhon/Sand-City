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

extern cityState city;
extern playerState player;
void SC_Building_Update();



g64_GUI_Window currentStatsWindow = {
    {250, 90}, //.pos
    {120, 130}, //.size
    //{255, 255, 255, 190} //.color
    {50, 150, 165, 190} //.color

};

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


/*
* 
* 
* 
* 
* 
* g64_GUI_TexWindow currentStatsTexWindow = {
    NULL,
    1,
    {210, 20}, //.pos
    {95, 80}, //.size
    {255, 255, 255, 150} //.color

};



g64_GUI_Text UI_Sand = {
    "BRLNSDB", //UI Font Name
    {230, 37}, //Screen Coordinates
    {58, 138, 127 }, //Font color
    "Sand ",
};

g64_GUI_Text UI_Shells = {
    "BRLNSDB", //UI Font Name
    {230, 52},
    {58, 138, 127 }, //Font color
    "Shells ",
};

g64_GUI_Text UI_BuildType = {
    "BRLNSDB", //UI Font Name
    {230, 67},
    {58, 138, 127 }, //Font color
    "Building ",
};

g64_GUI_Text UI_Residents = {
    "BRLNSDB", //UI Font Name
    {230, 87},
    {58, 138, 127 }, //Font color
    "Residents ",
};

g64_GUI_Text UI_Buildings = {
    "BRLNSDB", //UI Font Name
    {270, 87},
    {58, 138, 127 }, //Font color
    "Buildings ",
};

g64_GUI_Sprite UI_SandIcon = {
    NULL, // .sprite (initially set as NULL, a reference is given in "SC_Interface_Init"
    1, //.spriteID
    {220, 30}, //.pos
    {0.25f, 0.25f}, //.scl
    {58, 138, 127 }, //.color
    false, //.alpha
    255, //.transparency
};


g64_GUI_Sprite UI_ShellsIcon = {
    NULL, // .sprite (initially set as NULL, a reference is given in "SC_Interface_Init"
    2, //.spriteID
    {220, 45}, //.pos
    {0.25f, 0.25f}, //.scl
    {58, 138, 127 }, //.color
    false, //.alpha
    255, //.transparency
};


g64_GUI_Sprite UI_CastleIcon = {
    NULL, // .sprite (initially set as NULL, a reference is given in "SC_Interface_Init"
    2, //.spriteID
    {220, 60}, //.pos
    {0.5f, 0.5f}, //.scl
    {58, 138, 127 }, //.color
    false, //.alpha
    255, //.transparency
};


g64_GUI_Sprite UI_ResidentsIcon = {
    NULL, // .sprite (initially set as NULL, a reference is given in "SC_Interface_Init"
    6, //.spriteID
    {220, 80}, //.pos
    {1, 1}, //.scl
    {58, 138, 127 }, //.color
    false, //.alpha
    255, //.transparency
};

g64_GUI_Sprite UI_PropertiesIcon = {
    NULL, // .sprite (initially set as NULL, a reference is given in "SC_Interface_Init"
    3, //.spriteID
    {260, 80}, //.pos
    {1, 1}, //.scl
    {58, 138, 127 }, //.color
    false, //.alpha
    255, //.transparency
};
*/
/*typedef struct {
    sprite_t* sprite;   int spriteID;    Coords2 coords;    Vector2 scale;    RGB color;    bool alpha;    u8 transparency;   }g64_GUI_Sprite;*/

const int guiPlayfieldIconsTotal = 5;
g64_GUI_Sprite* UI_PlayfieldIcons[5] = {
    &UI_SandIcon,       &UI_ShellsIcon,     &UI_ResidentsIcon,   &UI_PropertiesIcon,    &UI_CastleIcon
};








char BuildTypeText;
u8 variableTest = 1;

void SC_Interface_Init() {
#ifdef DEBUG_NGIN64_INTERFACE
	//fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
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

}



void SC_Interface_Update() {

#ifdef DEBUG_NGIN64_INTERFACE
	//fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
	fprintf(stderr, "\n > RUN SC_Interface_Update!\n");
#endif

	SC_Playfield_Cursor_Update();
    SC_Building_Update();

}





void SC_Interface_Draw() {

	SC_Playfield_Cursor_Draw();


    gin64_GUI_Window_Draw(&currentStatsWindow);

    //gin64_GUI_TexWindow_Draw(&currentStatsTexWindow);


    for (uint32_t i = 0; i < guiPlayfieldIconsTotal - 1; i++) {
        // guiSprites[i] = sprite_load(guiSprites_path[i]);
        gin64_GUI_Sprite_Draw(UI_PlayfieldIcons[i]);
        //UI_PlayfieldIcons[i]->sprite = guiSprites[UI_PlayfieldIcons[i]->spriteID];
    }



    rdpq_font_begin(RGBA32(UI_BuildType.color.r, UI_BuildType.color.g, UI_BuildType.color.b, 255));
    gin64_GUI_Text_Draw(&UI_BuildType);
    rdpq_font_begin(RGBA32(UI_Shells.color.r, UI_Shells.color.g, UI_Shells.color.b, 255));
    gin64_GUI_Text_Draw(&UI_Shells);
    gin64_GUI_Text_Draw(&UI_Sand);
    gin64_GUI_Text_Draw(&UI_Residents);
    gin64_GUI_Text_Draw(PlayfieldUI_Elements[4]);


    
    //gin64_GUI_Sprite_Draw();




}
extern enum g64_EditModeState editModeState;
extern enum g64_BuildingTypeState buildingTypeState;
extern enum g64_LandscapeTypeState landscapeTypeState;

extern enum g64_PlayfieldEventState playfieldEventState;





void SC_Building_Update() {

    sprintf(UI_Residents.write, "%i", city.residents);
    sprintf(UI_Buildings.write, "%i", city.buildings);
    sprintf(UI_Sand.write, "%i", player.mat_sand);
    sprintf(UI_Shells.write, "%i", player.mat_shells);



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
