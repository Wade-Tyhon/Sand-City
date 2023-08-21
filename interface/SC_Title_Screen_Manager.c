#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../ngin64/nGin64.h"
#include "SC_Interface.h"



//g64_Pad[0].Hold.Start

//g64_Menu_Item TitleMenu_PressStart;
g64_Menu_Item TitleMenu_NewGame;
g64_Menu_Item TitleMenu_Instructions;

g64_Menu_Collections TitleMenu_Options = {

    {110, 125}, //.pos
    {&TitleMenu_NewGame, &TitleMenu_Instructions}, //.item[10]
    0, //.selectedItem
    {20, 10}, //.padding
    {160, 235, 235 }, //.baseColor
    {225, 255, 255 }, //.selectColor
};


g64_GUI_Window titleScreenOverlay = {
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

g64_GUI_Window instructionsBox = {
    false, //.active
    {60, 40}, //.pos
    {200, 160}, //.size
    //{255, 255, 255, 190} //.color
    {50, 150, 165, 255}, //.color
    false,
    {250, 90}, //.pos
    {120, 0}, //.size
    6,
};

g64_GUI_Window newGameFade = {
    false, //.active
    {0, 0}, //.pos
    {320, 240}, //.size
    //{255, 255, 255, 190} //.color
    {255, 255, 255, 0}, //.color
    false,
    {250, 90}, //.pos
    {120, 0}, //.size
    6,
};


g64_GUI_Window titleScreenMenuWindow = {
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



g64_GUI_Text TitleMenu_PressStart = {
    "BRLNSDB", //UI Font Name
    {120, 155}, //.pos
    {50, 150, 165 }, //.baseColor
    "PRESS START",
};

g64_GUI_Text TitleMenu_PressStartShadow = {
    "BRLNSDB", //UI Font Name
    {119, 156}, //.pos
    {225, 255, 255 }, //.baseColor
    "PRESS START",
};


g64_GUI_Text TitleMenu_Goals = {
    "BRLNSDB", //UI Font Name
    {119, 20}, //.pos
    {50, 150, 165 }, //.baseColor
    "GOALS | 1/4",
};

g64_GUI_Text TitleMenu_Controls = {
    "BRLNSDB", //UI Font Name
    {119, 20}, //.pos
    {50, 150, 165 }, //.baseColor
    "CONTROLS | 2/4",
};

g64_GUI_Text TitleMenu_Credits = {
    "BRLNSDB", //UI Font Name
    {119, 20}, //.pos
    {50, 150, 165 }, //.baseColor
    "CREDITS | 3/4",
};

g64_GUI_Text TitleMenu_About = {
    "BRLNSDB", //UI Font Name
    {119, 20}, //.pos
    {50, 150, 165 }, //.baseColor
    "ABOUT | 4/4",
};


u8 instructionPageNumber;


g64_GUI_Text* instructionTitles[4] = {
    &TitleMenu_Goals,
    &TitleMenu_Controls,
    &TitleMenu_Credits,
    &TitleMenu_About
};

/*
char* instructionTitles[4] = {
    "SAND CITY INSTRUCTIONS  |  1 of 3",
    "SAND CITY CONTROLS  |  2 of 3",
    "SAND CITY ABOUT  |  3 of 3",
    "SAND CITY CREDITS  |  4 of 3",
};
*/

char* instructionWindows[4] =
{
    "In Sand City, you are building up a sand castle\
    city for the crabby inhabitants on the beach.\
    Attract residents by building housing accomodations.\
    As your city grows, more crabs will move in! Over time, your residents\
    will pay property and sales tax, allowing city to grow.\n",
    "'L' - View Landscape Commands\n"
    "'R' - View Building Commands\n"
    "'C Left & C Right' - Browse Commands\n"
    "'D Pad' - Place Your Cursor\n"
    "'A' - Select a Command\n"
    "'B' - Secondary Command\n",      
    "Concept and Programming - WadeTyhon\n"
    "Modeling and Texturing - WadeTyhon\n"
    "Music Composition - cyrb\n"
    "SFX and Bug Testing - cyrb\n",
    "This project was built with Libdragon, using the \
    Unstable branch which brings OpenGL to the N64 for the first time!\n\n"
    "To learn more visit the\n"
    "N64Brew Discord\n",

};

/*

static const g64_Menu_Item* Title_Menu_List_Structures[2] = {
    &Menu_Start, &Menu_Instructions,
};
*/
/*
g64_GUI_Text TitleMenu_PressStart = {
    "BRLNSDB", //UI Font Name
    {30, 40},
    {160, 235, 235 }, //.baseColor
    "PRESS START ",
};

g64_GUI_Text TitleMenu_NewGame = {
   "BRLNSDB", //UI Font Name
   {30, 55},
   {160, 235, 235 }, //.baseColor
   "New Game ",
};

g64_GUI_Text TitleMenu_Instructions = {
    "BRLNSDB", //UI Font Name
    {30, 70},
    {160, 235, 235 }, //.baseColor
    "Instructions ",
};
*/

//extern void SC_Title_Menu_Event(char* keyWord);
void SC_Title_Menu_Init() {


  //  g64_Menu_Item TitleMenu_PressStart;
  //  g64_Menu_Item TitleMenu_NewGame;
  //  g64_Menu_Item TitleMenu_Instructions;
    
   // sprintf(TitleMenu_PressStart.name, "PRESS START");
   // TitleMenu_PressStart.handlerFunc = &SC_PlayfieldModifyEvent;


    //bool firstBoot = true;


    


    sprintf(TitleMenu_NewGame.name, "New Game");
    TitleMenu_NewGame.handlerFunc = &SC_NewGame_MenuEvent;

    sprintf(TitleMenu_Instructions.name, "Instructions");
    TitleMenu_Instructions.handlerFunc = &SC_Instructions_MenuEvent;

    SC_GameState.beginNewGame.active = false;

    //gin64_Event_Subscribe(&BuildMenuEvent.OnTrigger, &SC_PlayfieldOpenMenu_EventListener);
    
}


void SC_Title_Menu_Handler(g64_Event* thisEvent, char name[16]) {

    if (SC_GameState.titleScreen.active && !SC_GameState.titleInstruction.active)
    {

        //----- Note ----- Press start to open the menu
        if(thisEvent->args.constTrigger == false){
            if (g64_Pad[0].Press.Start == 1) {
                //thisEvent->args.constTrigger = false;
                sprintf(thisEvent->args.key, "Start");

               // fprintf(stderr, "\n > RUN 'Open Title Menu' in SC_Title_Menu_Handler Event Listener!\n");


                SC_GameState.titleMenuScreen.active = true;
                thisEvent->args.constTrigger = true;
                sprintf(thisEvent->args.key, "TriggerMenu");
                gin64_Audio_SFX_Play("rom:/MenuOpen1.wav64");
            }
        }
        
        //----- Note ----- Once the menu is open, select an option
        else if (thisEvent->args.constTrigger == true) {

          //  fprintf(stderr, "\n > RUN 'Open Title Menu' in SC_Title_Menu_Handler Event Listener!\n");
            
            if (g64_Pad[0].Press.B == 1) {
            
           //     fprintf(stderr, "\n > RUN 'Close Title Menu' in SC_Title_Menu_Handler Event Listener!\n");
                SC_GameState.titleMenuScreen.active = false;
                SC_GameState.beginNewGame.active = false;
                thisEvent->args.constTrigger = false;
                sprintf(thisEvent->args.key, "CloseMenu");
                gin64_Audio_SFX_Play("rom:/MenuClose1.wav64");
            }

        }

    }
    
}


void SC_Title_Selection_Handler(g64_Event* thisEvent, char name[16]) {

    

    if (SC_GameState.titleInstruction.active) {


        if (g64_Pad[0].Press.D_Left == 1) {
            if ((instructionPageNumber - 1) >= 0) {
                instructionPageNumber -= 1;
                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }
            else {
                instructionPageNumber = 0;
                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }
        }

        else if (g64_Pad[0].Press.D_Right == 1) {
            if ((instructionPageNumber + 1) <= 3) {
                instructionPageNumber += 1;
                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }
            else {
                instructionPageNumber = 3;
                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }
        }



        if (g64_Pad[0].Press.B == 1) {
            gin64_Audio_SFX_Play("rom:/MenuClose1.wav64");
            SC_GameState.titleInstruction.active = false;
            SC_GameState.titleMenuScreen.active = true;
        }
    }

    else if (SC_GameState.titleMenuScreen.active) {

        if (g64_Pad[0].Press.D_Up == 1) {
            if ((TitleMenu_Options.selectedItem - 1) >= 0) {
            TitleMenu_Options.selectedItem -= 1;
            gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
        }
            else {
                TitleMenu_Options.selectedItem = 0;
                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }
        }

        else if (g64_Pad[0].Press.D_Down == 1) {
            if ((TitleMenu_Options.selectedItem + 1) < 1) {
                TitleMenu_Options.selectedItem += 1;
                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }
            else {
                TitleMenu_Options.selectedItem = 1;
                gin64_Audio_SFX_Play("rom:/MenuNav3.wav64");
            }
        }

        //else if (thisEvent->args.constTrigger == true) {

        

        if (g64_Pad[0].Press.A == 1) {

            //sprintf(thisEvent->args.key, "Select");
            //thisEvent->args.trigger = true;

            //SC_GameState.beginNewGame.active = true;

            if (TitleMenu_Options.item[TitleMenu_Options.selectedItem]->handlerFunc != NULL)
                TitleMenu_Options.item[TitleMenu_Options.selectedItem]->handlerFunc(TitleMenu_Options.item[TitleMenu_Options.selectedItem]->name);



            

        }

    }





}

//extern SC_Setup();

void SC_Title_Screen_Update() {


    if (SC_GameState.beginNewGame.active) {

    //    fprintf(stderr, "\n > RUN 'Open Title Menu' in SC_Title_Menu_Handler Event Listener!\n");
        if (newGameFade.color.a < 250)
            newGameFade.color.a += 5;
        else {
            newGameFade.color.a = 255;

            gin64_Audio_Music_Play("rom:/Island_next_full.wav64");

            SC_GameState.titleMenuScreen.active = false;
            SC_GameState.beginNewGame.active = false;
            SC_GameState.titleScreen.active = false;

            SC_GameState.playfieldMain.active = true;

        }
            //lerpInt(newGameFade.color.a, 255, .1f);
    }

    else if (SC_GameState.titleInstruction.active) {

        SC_GameState.titleMenuScreen.active = false;
        SC_GameState.beginNewGame.active = false;
        SC_GameState.playfieldMain.active = false;

    }

    
}

//void SC_Title_Start_EventListener(g64_EventArgs* tempArgs) {
void SC_NewGame_MenuEvent(char* keyWord) {
    
    
    gin64_Audio_Music_Play("rom:/Start.wav64");
    SC_GameState.beginNewGame.active = true;
    
    /*
    if (gin64_EventKeyCheck(tempArgs->key, "Select")) {

        fprintf(stderr, "\n > RUN SC_PlayfieldOpenMenu_EventListener!\n");

        if (MenuList_EditStructures.item[MenuList_EditStructures.selectedItem]->handlerFunc != NULL)
            MenuList_EditStructures.item[MenuList_EditStructures.selectedItem]->handlerFunc(MenuList_EditStructures.item[MenuList_EditStructures.selectedItem]->name);

        sprintf(tempArgs->key, "CloseMenu");
    }
    */
}



void SC_Instructions_MenuEvent(char* keyWord) {


    gin64_Audio_SFX_Play("rom:/MenuOpen1.wav64");
    SC_GameState.beginNewGame.active = false;
    SC_GameState.titleInstruction.active = true;

    

    /*
    if (gin64_EventKeyCheck(tempArgs->key, "Select")) {

        fprintf(stderr, "\n > RUN SC_PlayfieldOpenMenu_EventListener!\n");

        if (MenuList_EditStructures.item[MenuList_EditStructures.selectedItem]->handlerFunc != NULL)
            MenuList_EditStructures.item[MenuList_EditStructures.selectedItem]->handlerFunc(MenuList_EditStructures.item[MenuList_EditStructures.selectedItem]->name);

        sprintf(tempArgs->key, "CloseMenu");
    }
    */
}




char* gameInstructions =
"SAND CITY INSTRUCTIONS\n"
"In Sand City, you are building up a sand castle\
city to house the many crabby inhabitants along the shoreline.\
In order to attract residents, you need to build housing accomodations.\
As you build up your city, more crabs will move in! Over time your residents\
will pay property and sales taxes, allowing you to build out your city further.";






void SC_Title_Menu_Draw() {


    gin64_GUI_BlitImage_Draw();

    if (SC_GameState.beginNewGame.active) {

      //  fprintf(stderr, "\n > RUN 'Open Title Menu' in SC_Title_Menu_Handler Event Listener!\n");
      //  if(newGameFade.color.a <= 255)
      //      lerpInt(newGameFade.color.a, 255, (float)gin64_GetDeltaTime()*.05 );


       //gin64_GUI_Screen_Fade(newGameFade.color);
        gin64_GUI_Window_Draw(&newGameFade);
    }

    else if (SC_GameState.titleInstruction.active) {
        gin64_GUI_Window_Draw(&titleScreenOverlay);
        gin64_GUI_Window_Draw(&instructionsBox);
        //gin64_GUI_Paragraph_Draw(gameInstructions);

        
        //gin64_GUI_Text_Draw(instructionTitles[instructionPageNumber]);
        gin64_GUI_Paragraph_Draw(instructionWindows[instructionPageNumber]);
        
        //gin64_GUI_Menu_Draw(&TitleMenu_Options);
    }

    else if (SC_GameState.titleMenuScreen.active) {
        gin64_GUI_Window_Draw(&titleScreenOverlay);
        gin64_GUI_Menu_Draw(&TitleMenu_Options);
    }
    
    else {

        gin64_GUI_Text_Draw(&TitleMenu_PressStartShadow);
        
        gin64_GUI_Text_Draw(&TitleMenu_PressStart);

    }

    //fprintf(stderr, "\n > RUN SC_Title_Menu_Draw!\n");



    /*
    gin64_GUI_Window_Draw(&fullScreenOverlay);
    gin64_GUI_Window_Draw(&buildingMenuWindow);

    gin64_GUI_Text_Draw(&Menu_StabilityStat);
    gin64_GUI_Text_Draw(&Menu_JobsStat);
    gin64_GUI_Text_Draw(&Menu_ResidentsStat);
    gin64_GUI_Text_Draw(&Menu_MoodStat);
    gin64_GUI_Text_Draw(&Menu_AlertStat);
    //gin64_GUI_Text_Draw(&Menu_BuiltTime);

    gin64_GUI_Menu_Draw(&MenuList_EditStructures);
    */

}