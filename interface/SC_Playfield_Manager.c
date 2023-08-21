#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>

#include "../ngin64/nGin64.h"
#include "SC_Interface.h"
#include "../scenes/prefabs/castles/SC_CastlesTypes.h"


extern gl_XP64_Vert vert_SelectStructureUI[];
extern uint16_t poly_SelectStructureUI[];
extern uint16_t SCGet_poly_SelectStructureUI_Size();
uint16_t poly_SelectStructureUI_Size;

extern gl_XP64_Vert vert_SelectGroundUI[];
extern uint16_t poly_SelectGroundUI_Beach[];
extern uint16_t SCGet_poly_SelectGroundUI_Beach_Size();
uint16_t poly_SelectGroundUI_Beach_Size;

extern gl_XP64_Vert vert_BeachPlayfield[];

extern int editableBlocks[16][7][4];

CursorObject playfieldCursor;

extern playerState player; 
extern cityState city;


void SC_PlayfieldTaxEvents_Update();

void SC_PlayfieldErosion_Update(g64_EventArgs* tempArgs);
void SC_PlayfieldJobsCheck_Update(g64_EventArgs* tempArgs);
void SC_PlayfieldResidentsCheck_Update(g64_EventArgs* tempArgs);


void SC_PlayfieldSalesTax_Update(g64_EventArgs* tempArgs);
void SC_PlayfieldPropertyTax_Update(g64_EventArgs* tempArgs);
void SC_PlayfieldBuildEvent(g64_EventArgs* tempArgs);

void SC_PlayfieldLandscapeEvent(g64_EventArgs* tempArgs);

void SC_Playfield_Cursor_Init() {

    poly_SelectGroundUI_Beach_Size = SCGet_poly_SelectGroundUI_Beach_Size();
    S_PlayfieldState_Pending[8][4].cursorActive = true;

    playfieldCursor.column = 8;
    playfieldCursor.row = 4;


    gin64_Event_Subscribe(&SalesTaxEvent.OnTimerEnd, &SC_PlayfieldSalesTax_Update);
    gin64_Event_Subscribe(&PropertyTaxEvent.OnTimerEnd, &SC_PlayfieldPropertyTax_Update);

    gin64_Event_Subscribe(&ErosionEvent.OnTimerEnd, &SC_PlayfieldErosion_Update);
    gin64_Event_Subscribe(&JobsCheckEvent.OnTimerEnd, &SC_PlayfieldJobsCheck_Update);
    gin64_Event_Subscribe(&ResidentCheckEvent.OnTimerEnd, &SC_PlayfieldResidentsCheck_Update);




    gin64_Event_Subscribe(&BuildObjectEvent.OnTrigger, &SC_PlayfieldBuildEvent);
    gin64_Event_Subscribe(&LandscapeEvent.OnTrigger, &SC_PlayfieldLandscapeEvent);

   // gin64_Event_Subscribe(&BuildMenuEvent.OnTrigger, &BuildMenuEvent);
    //gin64_Event_Subscribe(&BuildMenuEvent.OnCompletion, &BuildMenuEvent);

    //LandscapeEvent

    //----- Note ----- initiate the state of the city

    SC_CityStats.propertyTaxRate = 2;
    SC_CityStats.salesTaxRate = 1;
    SC_CityStats.residents = 0;
    SC_CityStats.buildings = 0;
    SC_CityStats.mood = 1;


    #ifdef DEBUG_NGIN64_INTERFACE
        //fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
        fprintf(stderr, "\n > RUN SC_Playfield_Control_Init!\n");
    #endif




}

void SC_Playfield_Control_Movement() {   

                playfieldCursor.obj.pos = SCGet_Playfield_Tile_Position(playfieldCursor.column, playfieldCursor.row);

                #ifdef DEBUG_NGIN64_INTERFACE
                                fprintf(stderr, "\n > New Cursor Position: X %.2f | Y %.2f | Z %.2f\n", (playfieldCursor.obj.pos.x), (playfieldCursor.obj.pos.y), (playfieldCursor.obj.pos.z));
                #endif


}

void SC_Playfield_Control_Camera() {

}


int previousFrame = 0;
bool canUpdate = true;
u8 updateRate = 2;
double inputDelay = 0.2; // ~ 0.0495ms
double inputTimer = 0.0;

bool directionHold = false;


int itemToPlace = 0; //----- Note ----- Temporary variable for selecting which item to place... 0 for smallTower, 1 for watchTower, 2 for tallTower



bool DEBUG_TEST_STATE = false;
void SC_DEBUG_RUN_ONCE() {

    for (int column = 0; column < 16; column++)
        for (int row = 0; row < 7; row++) {

            S_PlayfieldState_Pending[column][row].updating = true;
            S_PlayfieldState_Pending[column][row].structure = SC_WatchTower_PF;
            S_PlayfieldState_Pending[column][row].structure.obj.pos = SCGet_Playfield_Tile_Position(column, row);

        }

}


void SC_Playfield_Cursor_Update() {

        //----- Note ----- Run city state update each frame before all other playfield updates  
        //                  This will update things like material reserves, shell reserves, unlock items and new events 

    if (DEBUG_TEST_STATE == true) {

        SC_DEBUG_RUN_ONCE();
        DEBUG_TEST_STATE = false;
    }
    



    #ifdef DEBUG_NGIN64_INTERFACE
	    //fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
	    fprintf(stderr, "\n > RUN SC_Playfield_Control_Update!\n");
    #endif



        if (SC_GameState.playfieldMenu.active) //If a playfield object menu is active, do not run this script
            return;
        
        if (directionHold == false) {

            if (g64_Pad[0].Press.D_Right == 1) {
                if ((playfieldCursor.column + 1) <= 15)
                    playfieldCursor.column += 1;
                else
                    playfieldCursor.column = 0;
            }

            else if (g64_Pad[0].Press.D_Left == 1) {
                if ((playfieldCursor.column - 1) >= 0)
                    playfieldCursor.column -= 1;
                else
                    playfieldCursor.column = 15;
            }



            if (g64_Pad[0].Press.D_Up == 1) {
                if ((playfieldCursor.row + 1) <= 6)
                    playfieldCursor.row += 1;
                else
                    playfieldCursor.row = 0;
            }

            else if (g64_Pad[0].Press.D_Down == 1) {
                if ((playfieldCursor.row - 1) >= 0)
                    playfieldCursor.row -= 1;
                else
                    playfieldCursor.row = 6;
            }
        }

        else if (directionHold == true) {

            if (gin64_GetPlaybackTick(10) - previousFrame >= updateRate)
            {
                previousFrame = gin64_GetPlaybackTick(10);
                canUpdate = true; //will stay true until the next input from the player
            }


            if (canUpdate == true)
            {
                //currentFrame = gin64_GetPlaybackTick();

                previousFrame = gin64_GetPlaybackTick(10);
                if (g64_Pad[0].Dpad.x != 0) {

                    if ((playfieldCursor.column + g64_Pad[0].Dpad.x) < 16 && (playfieldCursor.column + g64_Pad[0].Dpad.x) >= 0)
                        playfieldCursor.column += g64_Pad[0].Dpad.x;

                    else if ((playfieldCursor.column + g64_Pad[0].Dpad.x) >= 16)
                        playfieldCursor.column = 0;

                    else if ((playfieldCursor.column + g64_Pad[0].Dpad.x) < 0)
                        playfieldCursor.column = 15;

                    canUpdate = false;
                    //updateRate = 1; // if held down, the next frame update will be sooner

                }

                if (g64_Pad[0].Dpad.y != 0) {

                    if ((playfieldCursor.row + g64_Pad[0].Dpad.y) < 7 && (playfieldCursor.row + g64_Pad[0].Dpad.y) >= 0)
                        playfieldCursor.row += g64_Pad[0].Dpad.y;

                    else if ((playfieldCursor.row + g64_Pad[0].Dpad.y) >= 7)
                        playfieldCursor.row = 0;

                    else if ((playfieldCursor.row + g64_Pad[0].Dpad.y) < 0)
                        playfieldCursor.row = 6;

                    canUpdate = false;
                    //updateRate = 1; // if held down, the next frame update will be sooner
                }

            }

        }

        //------ Note ------ Check for holding the Dpad as a directional input for fast movement
        if (g64_Pad[0].Dpad.x >= 0 || g64_Pad[0].Dpad.y >= 0) {

            inputTimer += gin64_GetDeltaTime();

            if (inputTimer >= 0.2200) {
                updateRate = 1;
                directionHold = true;
            }

        }

        if (g64_Pad[0].Dpad.x == 0 && g64_Pad[0].Dpad.y == 0 && inputTimer >= 0.1) {

            inputTimer = 0;
            updateRate = 1;
            directionHold = true;
        }

        else if (g64_Pad[0].Dpad.x == 0 && g64_Pad[0].Dpad.y == 0) {

            inputTimer = 0;
            updateRate = 2;
            directionHold = false;
        }
        


        #ifdef DEBUG_NGIN64_INTERFACE
                fprintf(stderr, "\n > Column: %i | Row: %i \n", (playfieldCursor.column), (playfieldCursor.row));
                fprintf(stderr, "\n > directionHold: %i | inputTimer: %.2f \n", (directionHold), (inputTimer));
        #endif


        //SC_Playfield_Control_Movement();

        playfieldCursor.obj.pos = SCGet_Playfield_Tile_Position(playfieldCursor.column, playfieldCursor.row);

        #ifdef DEBUG_NGIN64_INTERFACE
                fprintf(stderr, "\n > New Cursor Position: X %.2f | Y %.2f | Z %.2f\n", (playfieldCursor.obj.pos.x), (playfieldCursor.obj.pos.y), (playfieldCursor.obj.pos.z));
        #endif


                // 42949672
       //unsigned int tempRandNum = (RAND_MAX + 1u) / 40;

              //  unsigned int tempRandNum = rand() / (RAND_MAX / 450 + 1);
      // fprintf(stderr, "\n\n--------\n!!! RANDOM NUMBER TEST %i !!! \n--------\n\n", tempRandNum);
}



bool assigned = false;

void SC_Playfield_Cursor_Draw() {

    glPushMatrix();

    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_COLOR_MATERIAL);

    glDisable(GL_FOG);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glTranslatef((playfieldCursor.obj.pos.x), (playfieldCursor.obj.pos.y), (playfieldCursor.obj.pos.z));
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glDisable(GL_CULL_FACE);
    glEnable(GL_ALPHA_TEST);
    glDepthMask(GL_FALSE);

    glVertexPointer(3, GL_FLOAT, sizeof(gl_XP64_Vert), (void*)(0 * sizeof(float) + (void*)vert_SelectGroundUI));
    glTexCoordPointer(2, GL_FLOAT, sizeof(gl_XP64_Vert), (void*)(3 * sizeof(float) + (void*)vert_SelectGroundUI));
    glNormalPointer(GL_FLOAT, sizeof(gl_XP64_Vert), (void*)(5 * sizeof(float) + (void*)vert_SelectGroundUI));
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(gl_XP64_Vert), (void*)(8 * sizeof(float) + (void*)vert_SelectGroundUI));

    glDrawElements(GL_TRIANGLES, poly_SelectGroundUI_Beach_Size / sizeof(uint16_t), GL_UNSIGNED_SHORT, poly_SelectGroundUI_Beach);


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

void SC_PlayfieldLandscapeEvent(g64_EventArgs* tempArgs) {

    bool completed = false;
    u8 sandVolume = 0;

    //----- Note ----- Confirm that no object is currently built on this tile
    if (!S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.staticModel_LOD[2].glDisplayList) {

        switch (landscapeTypeState) {

            case 1: //Ground adjustment
                if (strcmp(tempArgs->key, "Dig") == 0) {
                    sandVolume = SC_Set_PlayfieldTile(playfieldCursor.column, playfieldCursor.row, tempArgs->key);
                    //if (sandVolume > 0)
                    SC_CityStats.mat_sand += sandVolume; //use up your source of sand to create a hill
                }

                if ((strcmp(tempArgs->key, "Fill") == 0) && (SC_CityStats.mat_sand - 8 >= 0)) {
                    sandVolume = SC_Set_PlayfieldTile(playfieldCursor.column, playfieldCursor.row, tempArgs->key);
                    //if (sandVolume > 0)
                    SC_CityStats.mat_sand -= sandVolume; //use up your source of sand to create a hill
                }

                break;

            case 2:
             ////   fprintf(stderr, "\n\n--------\n!!! Fill Water Event !!! \n--------\n\n");
             //   fprintf(stderr, "\n\n--------\n!!! Fill Water Event !!! \n--------\n\n");
             //   fprintf(stderr, "\n\n--------\n!!! Fill Water Event !!! \n--------\n\n");
            //    fprintf(stderr, "\n\n--------\n!!! Fill Water Event !!! \n--------\n\n");
                break;

            default: //Water Fill / Drain
                //Do nothing
                break;

            }
        }
    
    
}


void SC_PlayfieldBuildEvent(g64_EventArgs* tempArgs) {
 //   fprintf(stderr, "\n\n--------\n!!! Place Object Event !!! \n--------\n\n");

    /*
    if (editModeState == Building && (strcmp(name, "Building") == 0)) {
        thisEvent->args.trigger = true;
        sprintf(thisEvent->args.key, "Demolish");
    }
    */
    if (strcmp(tempArgs->key, "BuildMenu") == 0) {
    
        //Wait for input and display edit screen



    }

    if (strcmp(tempArgs->key, "Build") == 0) {


        g64_GameTimer currentTime = gin64_GetGameTime(); //Get the current starting time

        if (!S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.staticModel_LOD[2].glDisplayList) {
            switch (buildingTypeState) {

            case 1: //Build a small tower
                //fprintf(stderr, "\n\n--------\n!!! Place Object !!! \n--------\n\n");
                if ((SC_SimpleTower_PF.pointsB <= SC_CityStats.mat_sand) && (SC_SimpleTower_PF.pointsC <= SC_CityStats.mat_shells)) { //Check to make sure you have enough materials to build
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_SimpleTower_PF;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.buildTime = gin64_SetGameTimer(currentTime.hours, currentTime.minutes, currentTime.seconds);
                    SC_CityStats.mat_sand -= SC_SimpleTower_PF.pointsB; // source the raw materials for this with sand
                    SC_CityStats.mat_shells -= SC_SimpleTower_PF.pointsC; // pay for this build with shells
                    SC_CityStats.residents += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.residents[0];
                    SC_CityStats.jobs += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.jobs[0];
                    SC_CityStats.buildings += 1;
                    
                }

                break;

            case 2: //Build a large tower
                if ((SC_LargeTower_PF.pointsB <= SC_CityStats.mat_sand) && (SC_LargeTower_PF.pointsC <= SC_CityStats.mat_shells)) { //Check to make sure you have enough materials to build
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_LargeTower_PF;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.buildTime = gin64_SetGameTimer(currentTime.hours, currentTime.minutes, currentTime.seconds);
                    SC_CityStats.mat_sand -= SC_LargeTower_PF.pointsB; // source the raw materials for this with sand
                    SC_CityStats.mat_shells -= SC_LargeTower_PF.pointsC; // pay for this build with shells
                    SC_CityStats.residents += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.residents[0];
                    SC_CityStats.jobs += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.jobs[0];
                    SC_CityStats.buildings += 1;
                }
                break;

            case 3: //Build a watch tower


                if ((SC_WatchTower_PF.pointsB <= SC_CityStats.mat_sand) && (SC_WatchTower_PF.pointsC <= SC_CityStats.mat_shells)) { //Check to make sure you have enough materials to build
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_WatchTower_PF;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.buildTime = gin64_SetGameTimer(currentTime.hours, currentTime.minutes, currentTime.seconds);
                    SC_CityStats.mat_sand -= SC_WatchTower_PF.pointsB; // source the raw materials for this with sand
                    SC_CityStats.mat_shells -= SC_WatchTower_PF.pointsC; // pay for this build with shells
                    SC_CityStats.residents += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.residents[0];
                    SC_CityStats.jobs += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.jobs[0];
                    SC_CityStats.buildings += 1;
                }
                break;


            case 4: //Build an office tower
                if ((SC_OfficeTower_PF.pointsB <= SC_CityStats.mat_sand) && (SC_OfficeTower_PF.pointsC <= SC_CityStats.mat_shells)) { //Check to make sure you have enough materials to build
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_OfficeTower_PF;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.buildTime = gin64_SetGameTimer(currentTime.hours, currentTime.minutes, currentTime.seconds);
                    SC_CityStats.mat_sand -= SC_OfficeTower_PF.pointsB; // source the raw materials for this with sand
                    SC_CityStats.mat_shells -= SC_OfficeTower_PF.pointsC; // pay for this build with shells
                    SC_CityStats.residents += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.residents[0];
                    SC_CityStats.jobs += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.jobs[0];
                    SC_CityStats.buildings += 1;
                }
                break;

            case 5: //Build an office tower
                if ((SC_OfficeTower_PF.pointsB <= SC_CityStats.mat_sand) && (SC_OfficeTower_PF.pointsC <= SC_CityStats.mat_shells)) { //Check to make sure you have enough materials to build
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_OfficeTower_PF;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.buildTime = gin64_SetGameTimer(currentTime.hours, currentTime.minutes, currentTime.seconds);
                    SC_CityStats.mat_sand -= SC_OfficeTower_PF.pointsB; // source the raw materials for this with sand
                    SC_CityStats.mat_shells -= SC_OfficeTower_PF.pointsC; // pay for this build with shells
                    SC_CityStats.residents += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.residents[0];
                    SC_CityStats.jobs += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.jobs[0];
                    SC_CityStats.buildings += 1;
                }
                break;

                //
            case 6: //Build a high density residential tower
                if ((SC_ResidentialTower_PF.pointsB <= SC_CityStats.mat_sand) && (SC_ResidentialTower_PF.pointsC <= SC_CityStats.mat_shells)) { //Check to make sure you have enough materials to build
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_ResidentialTower_PF;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.buildTime = gin64_SetGameTimer(currentTime.hours, currentTime.minutes, currentTime.seconds);
                    SC_CityStats.mat_sand -= SC_ResidentialTower_PF.pointsB; // source the raw materials for this with sand
                    SC_CityStats.mat_shells -= SC_ResidentialTower_PF.pointsC; // pay for this build with shells
                    SC_CityStats.residents += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.residents[0];
                    SC_CityStats.jobs += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.jobs[0];
                    SC_CityStats.buildings += 3;
                }
                break;

                //----- Note ----- placeholder until all other models are completed
            default:
                if ((SC_LargeTower_PF.pointsB <= SC_CityStats.mat_sand) && (SC_LargeTower_PF.pointsC <= SC_CityStats.mat_shells)) { //Check to make sure you have enough materials to build
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_LargeTower_PF;
                    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.buildTime = gin64_SetGameTimer(currentTime.hours, currentTime.minutes, currentTime.seconds);
                    SC_CityStats.mat_sand -= SC_LargeTower_PF.pointsB; // source the raw materials for this with sand
                    SC_CityStats.mat_shells -= SC_LargeTower_PF.pointsC; // pay for this build with shells
                    SC_CityStats.residents += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.residents[0];
                    SC_CityStats.jobs += S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.jobs[0];
                    SC_CityStats.buildings += 1;
                }
                break;
            }
        }

    }
    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.obj.pos = SCGet_Playfield_Tile_Position(playfieldCursor.column, playfieldCursor.row);

}





void SC_PlayfieldModifyEvent(char* keyWord) {

    //char tempKeyWord[16];
    //fprintf(stderr, "\n\n--------\n!!! %s Object Event !!! \n--------\n\n", keyWord);
    //sprintf(tempKeyWord, keyWord);


    if (gin64_EventKeyCheck(keyWord, "Repair")){

    //    fprintf(stderr, "\n\n--------\n!!! Repair Object Event !!! \n--------\n\n");

        S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
        S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_Empty_PF;
        SC_CityStats.mat_sand += (SC_SimpleTower_PF.pointsB * .5f); // source the raw materials for this with sand
        SC_CityStats.mat_shells -= (SC_SimpleTower_PF.pointsC * .5f); // pay for this build with shells
        SC_CityStats.residents -= S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.residents[0];
        SC_CityStats.jobs -= S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.jobs[0];
        SC_CityStats.buildings -= 1;

    }

    else if (gin64_EventKeyCheck(keyWord, "Upgrade")){

      //  fprintf(stderr, "\n\n--------\n!!! Upgrade Object Event !!! \n--------\n\n");

    }

    else if (gin64_EventKeyCheck(keyWord, "Demolish")){

        if (S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.staticModel_LOD[2].glDisplayList) {
         //   fprintf(stderr, "\n\n--------\n!!! Demolish Object Event !!! \n--------\n\n");

            S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
            S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_Empty_PF;
            SC_CityStats.mat_sand += (SC_SimpleTower_PF.pointsB * .5f); // source the raw materials for this with sand
            SC_CityStats.mat_shells -= (SC_SimpleTower_PF.pointsC * .5f); // pay for this build with shells
            SC_CityStats.residents -= S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.residents[0];
            SC_CityStats.jobs -= S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.jobs[0];
            SC_CityStats.buildings -= 1;
            //SC_CityStats.residents -= 1;

        }

    }

    //tempKeyWord






    //S_PlayfieldState_Current
        


  //  fprintf(stderr, "\n\n--------\n!!! %s Object Event !!! \n--------\n\n", keyWord);
 //   fprintf(stderr, "\n\n--------\n!!! %s Object Event !!! \n--------\n\n", keyWord);
  //  fprintf(stderr, "\n\n--------\n!!! %s Object Event !!! \n--------\n\n", keyWord);
}

#define RAN_N_RANGE 450
#define RAN_N_RANGEB 1000

void SC_PlayfieldJobsCheck_Update(g64_EventArgs* tempArgs) {

   // g64_GameTimer currentTime = gin64_GetGameTime(); //Get the current starting time

    unsigned int tempRandNum;   

    for (int column = 0; column < 16; column++){
        for (int row = 0; row < 7; row++) {

            if (S_PlayfieldState_Current[column][row].structure.staticModel_LOD[2].glDisplayList) {

                tempRandNum = rand() / (RAND_MAX / RAN_N_RANGE + 1);
                //fprintf(stderr, "\n\n--------\n!!! RANDOM NUMBER TEST %i !!! \n--------\n\n", tempRandNum);

                if (tempRandNum >= (RAN_N_RANGE * .55f) && (S_PlayfieldState_Current[column][row].structure.jobs[0] < S_PlayfieldState_Current[column][row].structure.jobs[1])){
                    S_PlayfieldState_Current[column][row].structure.jobs[0] += 1;
                    SC_CityStats.jobs += 1;
                }
            }
        }

    }
}

void SC_PlayfieldResidentsCheck_Update(g64_EventArgs* tempArgs) {

    unsigned int tempRandNum;
    unsigned int jobsBoost;

    for (int column = 0; column < 16; column++) {
        for (int row = 0; row < 7; row++) {

            if (S_PlayfieldState_Current[column][row].structure.staticModel_LOD[2].glDisplayList) {

                tempRandNum = rand() / (RAND_MAX / RAN_N_RANGEB + 1);
                jobsBoost = (SC_CityStats.jobs - SC_CityStats.residents)*10;

                //fprintf(stderr, "\n\n--------\n!!! RANDOM NUMBER TEST %i !!! \n--------\n\n", tempRandNum);

                if (tempRandNum + jobsBoost >= (RAN_N_RANGE * .45f) && (S_PlayfieldState_Current[column][row].structure.residents[0] < S_PlayfieldState_Current[column][row].structure.residents[1])){
                    S_PlayfieldState_Current[column][row].structure.residents[0] += 1;
                    SC_CityStats.residents += 1;
                }
            }
        }

    }
}


void SC_PlayfieldErosion_Update(g64_EventArgs* tempArgs) {
    
    g64_GameTimer currentTime = gin64_GetGameTime(); //Get the current starting time

    for (int column = 0; column < 16; column++)
        for (int row = 0; row < 7; row++) {
            g64_GameTimer timeDifference;
            if(S_PlayfieldState_Current[column][row].structure.staticModel_LOD[2].glDisplayList){

                //S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.buildTime;

                timeDifference = gin64_CompareGameTimers(S_PlayfieldState_Current[column][row].structure.buildTime, currentTime);

                //----- Note ----- Calculate the total number of seconds that has passed
                float secondsElapsed = (timeDifference.minutes * 60) + timeDifference.seconds;

                if (secondsElapsed >= 45.0f) {
                    //gin64_CompareGameTimers(S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.pointsH -= 1);
                    S_PlayfieldState_Current[column][row].structure.pointsH -= 1;
                //    fprintf(stderr, "\n\n--------\n!!! Time Difference: %i : %i : %.2f !!! \n--------\n\n", timeDifference.hours, timeDifference.minutes, timeDifference.seconds);
                 //   fprintf(stderr, "\n\n--------\n!!! Resetting to: %i : %i : %.2f !!! \n--------\n\n", currentTime.hours, currentTime.minutes, currentTime.seconds);

                    //----- Note ----- Reset build time
                    S_PlayfieldState_Current[column][row].structure.buildTime = gin64_SetGameTimer(currentTime.hours, currentTime.minutes, currentTime.seconds);
                }

            }

        }
    
    /*
    int salesTaxIncome = (1 + (SC_CityStats.mood * .25)) * (SC_CityStats.residents * SC_CityStats.salesTaxRate);

    if (SC_CityStats.mat_shells + salesTaxIncome < 10000)
        SC_CityStats.mat_shells += salesTaxIncome;
    else
        SC_CityStats.mat_shells = 99999;
        */
}


void SC_PlayfieldSalesTax_Update(g64_EventArgs* tempArgs) {

    int salesTaxIncome = (1 + (SC_CityStats.mood * .25)) * (SC_CityStats.residents * SC_CityStats.salesTaxRate);

    if(SC_CityStats.mat_shells + salesTaxIncome < 10000)
        SC_CityStats.mat_shells += salesTaxIncome;
    else
        SC_CityStats.mat_shells = 99999;
    
}

void SC_PlayfieldPropertyTax_Update(g64_EventArgs* tempArgs) {

    int propTaxIncome = (2 * (SC_CityStats.buildings * SC_CityStats.propertyTaxRate));

    if (SC_CityStats.mat_sand + propTaxIncome < 1000)
        SC_CityStats.mat_sand += propTaxIncome;
    else
        SC_CityStats.mat_sand = 999;

}