#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../ngin64/nGin64.h"
#include "SC_Interface.h"
#include "../scenes/prefabs/castles/SC_CastlesTypes.h"


/*
g64_Menu_Item Menu_Repair = {true, "Repair", &SalesTaxEvent };
g64_Menu_Item Menu_Upgrade = { true, "Upgrade", &SalesTaxEvent };
g64_Menu_Item Menu_Demolish = { true, "Demolish", &SalesTaxEvent };
*/

g64_Menu_Item Menu_Repair;
g64_Menu_Item Menu_Upgrade;
g64_Menu_Item Menu_Demolish;



g64_Menu_Collections MenuList_EditStructures = {

    {10, 100}, //.pos
    {&Menu_Repair, &Menu_Upgrade, &Menu_Demolish,}, //.item[10]
    0, //.selectedItem
    {20, 10}, //.padding
    {160, 235, 235 }, //.baseColor
    {225, 255, 255 }, //.selectColor
};


g64_GUI_Window fullScreenOverlay = {
    false, //.active
    {0, 0}, //.pos
    {320, 240}, //.size
    //{255, 255, 255, 190} //.color
    {50, 50, 50, 190}, //.color
    false,
    {250, 90}, //.pos
    {120, 0}, //.size
    6,
};

g64_GUI_Window buildingMenuWindow = {
    false, //.active
    {20, 20}, //.pos
    {100, 160}, //.size
    //{255, 255, 255, 190} //.color
    {50, 150, 165, 190}, //.color
    false,
    {250, 90}, //.pos
    {120, 0}, //.size
    6,
};






g64_GUI_Sprite UI_ObjectType = {
    NULL, // .sprite (initially set as NULL, a reference is given in "SC_Interface_Init"
    6, //.spriteID
    {258, 160}, //.pos
    {0.5f, 0.5f}, //.scl
    {58, 138, 127 }, //.color
    false, //.alpha
    255, //.transparency
};
extern playfieldState S_PlayfieldState_Current[16][7];

g64_GUI_Text Menu_StabilityStat = {
    "BRLNSDB", //UI Font Name
    {30, 40},
    {160, 235, 235 }, //.baseColor
    "Stability ",
};

g64_GUI_Text Menu_JobsStat = {
   "BRLNSDB", //UI Font Name
   {30, 55},
   {160, 235, 235 }, //.baseColor
   "Jobs ",
};

g64_GUI_Text Menu_ResidentsStat = {
    "BRLNSDB", //UI Font Name
    {30, 70},
    {160, 235, 235 }, //.baseColor
    "Residents ",
};

g64_GUI_Text Menu_MoodStat = {
    "BRLNSDB", //UI Font Name
    {30, 85},
    {160, 235, 235 }, //.baseColor
    "Mood ",
};

g64_GUI_Text Menu_AlertStat = {
    "BRLNSDB", //UI Font Name
    {30, 100},
    {160, 235, 235 }, //.baseColor
    "Alert ",
};


g64_GUI_Text Menu_BuiltTime = {
    "BRLNSDB", //UI Font Name
    {30, 60},
    {160, 235, 235 }, //.baseColor
    "BuiltTime ",
};


g64_GUI_Text Menu_ElapsedTime = {
    "BRLNSDB", //UI Font Name
    {30, 60},
    {160, 235, 235 }, //.baseColor
    "ElapsedTime ",
};


g64_GUI_Text Menu_Pause = {
    "BRLNSDB", //UI Font Name
    {120, 135}, //.pos
    {50, 150, 165 }, //.baseColor
    "PAUSED",
};

g64_GUI_Text Menu_PauseShadow = {
    "BRLNSDB", //UI Font Name
    {119, 136}, //.pos
    {225, 255, 255 }, //.baseColor
    "PAUSED",
};


//extern void SC_Playfield_Structure_Menu_Update();
//void SC_Playfield_Structure_Menu_Update(g64_EventArgs* tempArgs);
extern void SC_PlayfieldModifyEvent(char* keyWord);
void SC_Playfield_Structure_Menu_Init() {

    sprintf(Menu_Repair.name, "Repair");    
    Menu_Repair.handlerFunc = &SC_PlayfieldModifyEvent;

    sprintf(Menu_Upgrade.name, "Upgrade");
    Menu_Upgrade.handlerFunc = &SC_PlayfieldModifyEvent;

    sprintf(Menu_Demolish.name, "Demolish");
    Menu_Demolish.handlerFunc = &SC_PlayfieldModifyEvent;

    gin64_Event_Subscribe(&BuildMenuEvent.OnTrigger, &SC_PlayfieldOpenMenu_EventListener);

}


void SC_PlayfieldOpenMenu_Handler(g64_Event* thisEvent, char name[16]) {



    if (!SC_GameState.pauseScreen.active) {
        if (S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.staticModel_LOD[2].glDisplayList) {

            if (SC_GameState.playfieldMenu.active == false && editModeState == Building && (gin64_EventKeyCheck(name, "Build Menu"))) {

                if (g64_Pad[0].Press.B == 1) {
                    thisEvent->args.constTrigger = true;
                    //thisEvent->args.trigger = true;
                    //SC_GameState.playfieldMenu.active = true;
                    sprintf(thisEvent->args.key, "TriggerMenu");

                    gin64_Audio_SFX_Play("rom:/MenuOpen1.wav64");
                }
            }

            else if (thisEvent->args.constTrigger == true && editModeState == Building && (gin64_EventKeyCheck(name, "Build Menu"))) {
                //fprintf(stderr, "\n >RUN SC_PlayfieldOpenMenu_Handler Menu Open!\n");
                if (g64_Pad[0].Press.B == 1) {
                    thisEvent->args.constTrigger = false;
                    sprintf(thisEvent->args.key, "CloseMenu");
                    gin64_Audio_SFX_Play("rom:/MenuClose1.wav64");
                }

                if (g64_Pad[0].Press.A == 1) {
                    //thisEvent->args.constTrigger = false;
                    sprintf(thisEvent->args.key, "Select");
                }
            }

            //if (strcmp(thisEvent->args.key, "TriggerMenu") == 0) {
            if (gin64_EventKeyCheck(thisEvent->args.key, "TriggerMenu")) {
                SC_GameState.playfieldMenu.active = true;
            }

            //else if (strcmp(thisEvent->args.key, "CloseMenu") == 0) {
            else if (gin64_EventKeyCheck(thisEvent->args.key, "CloseMenu")) {
                SC_GameState.playfieldMenu.active = false;
            }

            //else if (strcmp(thisEvent->args.key, "Select") == 0) {
            else if (gin64_EventKeyCheck(thisEvent->args.key, "Select")) {

                thisEvent->args.trigger = true;
            }


        }

        else if (gin64_EventKeyCheck(thisEvent->args.key, "CloseMenu")) {
            SC_GameState.playfieldMenu.active = false;
        }

    }
    
}


void SC_PlayfieldOpenMenu_EventListener(g64_EventArgs* tempArgs) {


    if(gin64_EventKeyCheck(tempArgs->key, "Select")){

        gin64_Audio_SFX_Play("rom:/MenuClose1.wav64");

       // fprintf(stderr, "\n > RUN SC_PlayfieldOpenMenu_EventListener!\n");

        if (MenuList_EditStructures.item[MenuList_EditStructures.selectedItem]->handlerFunc != NULL)
            MenuList_EditStructures.item[MenuList_EditStructures.selectedItem]->handlerFunc(MenuList_EditStructures.item[MenuList_EditStructures.selectedItem]->name);

        sprintf(tempArgs->key, "CloseMenu");
    }

}
    //extern void SC_Playfield_Structure_Menu_Update();

void SC_PlayfieldOpenMenu_Update() {


    if (!SC_GameState.pauseScreen.active) {

        if (SC_GameState.playfieldMenu.active) {

            if (g64_Pad[0].Press.D_Up == 1) {
                if ((MenuList_EditStructures.selectedItem - 1) >= 0)
                    MenuList_EditStructures.selectedItem -= 1;
                else
                    MenuList_EditStructures.selectedItem = 0;

                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }

            else if (g64_Pad[0].Press.D_Down == 1) {
                if ((MenuList_EditStructures.selectedItem + 1) < 2)
                    MenuList_EditStructures.selectedItem += 1;
                else
                    MenuList_EditStructures.selectedItem = 2;

                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }

        }
    }





    sprintf(Menu_StabilityStat.write, "Stability %i", S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.pointsH);
    sprintf(Menu_JobsStat.write, "Jobs %i", S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.jobs[0]);
    sprintf(Menu_ResidentsStat.write, "Residents %i", S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.residents[0]);
    sprintf(Menu_MoodStat.write, "Mood %i", S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.mood[0]);
    //sprintf(Menu_AlertStat.write, "%s", "Need Jobs!");
    sprintf(Menu_AlertStat.write, "%i | %i", playfieldCursor.column, playfieldCursor.row);
    //sprintf(Menu_StabilityStat.write, "Residents %i", S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.residents);
    //sprintf(Menu_StabilityStat.write, "Mood %i", S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.pointsH);
    //sprintf(Menu_StabilityStat.write, "Alert %s", S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.pointsH);

    //Menu_BuiltTime







    sprintf(Menu_BuiltTime.write, "Build %i . %i . %i", S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.buildTime.hours,
        S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.buildTime.minutes, 
        (int)S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.buildTime.seconds);
    //% i :% i : % .2f !!!\n--------\n\n", currentTime.hours, currentTime.minutes, currentTime.seconds
    
}


void SC_Playfield_Pause_Menu_Draw() {
    //Menu_Pause Menu_PauseShadow
    
    gin64_GUI_Window_Draw(&fullScreenOverlay);

    gin64_GUI_Text_Draw(&Menu_PauseShadow);
    gin64_GUI_Text_Draw(&Menu_Pause);

}

void SC_Playfield_Structure_Menu_Draw() {

    
    
    gin64_GUI_Window_Draw(&fullScreenOverlay);
    gin64_GUI_Window_Draw(&buildingMenuWindow);

    gin64_GUI_Text_Draw(&Menu_StabilityStat);
    gin64_GUI_Text_Draw(&Menu_JobsStat);
    gin64_GUI_Text_Draw(&Menu_ResidentsStat);
    gin64_GUI_Text_Draw(&Menu_MoodStat);
    //gin64_GUI_Text_Draw(&Menu_AlertStat);
    //gin64_GUI_Text_Draw(&Menu_BuiltTime);

    gin64_GUI_Menu_Draw(&MenuList_EditStructures);


}
