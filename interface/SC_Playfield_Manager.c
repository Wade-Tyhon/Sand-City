#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

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
    gin64_Event_Subscribe(&BuildObjectEvent.OnTrigger, &SC_PlayfieldBuildEvent);
    gin64_Event_Subscribe(&LandscapeEvent.OnTrigger, &SC_PlayfieldLandscapeEvent);


    //LandscapeEvent

    //----- Note ----- initiate the state of the city

    city.propertyTaxRate = 2;
    city.salesTaxRate = 1;
    city.residents = 0;
    city.buildings = 0;
    city.mood = 10;


    #ifdef DEBUG_NGIN64_INTERFACE
        //fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
        fprintf(stderr, "\n > RUN SC_Playfield_Control_Init!\n");
    #endif
}

void SC_Playfield_Control_Movement() {   

                playfieldCursor.pos = SCGet_Playfield_Tile_Position(playfieldCursor.column, playfieldCursor.row);

                #ifdef DEBUG_NGIN64_INTERFACE
                                fprintf(stderr, "\n > New Cursor Position: X %.2f | Y %.2f | Z %.2f\n", (playfieldCursor.pos.x), (playfieldCursor.pos.y), (playfieldCursor.pos.z));
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




void SC_Playfield_Cursor_Update() {

        //----- Note ----- Run city state update each frame before all other playfield updates  
        //                  This will update things like material reserves, shell reserves, unlock items and new events 


    #ifdef DEBUG_NGIN64_INTERFACE
	    //fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
	    fprintf(stderr, "\n > RUN SC_Playfield_Control_Update!\n");
    #endif

        if(directionHold == false){

            if( g64_Pad[0].Press.D_Right == 1){
                if ((playfieldCursor.column + 1) <= 15)
                    playfieldCursor.column += 1;
                else
                    playfieldCursor.column = 0;
            }

            else if (g64_Pad[0].Press.D_Left == 1){
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

            if (inputTimer >= 0.2200){
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

        playfieldCursor.pos = SCGet_Playfield_Tile_Position(playfieldCursor.column, playfieldCursor.row);

        #ifdef DEBUG_NGIN64_INTERFACE
                fprintf(stderr, "\n > New Cursor Position: X %.2f | Y %.2f | Z %.2f\n", (playfieldCursor.pos.x), (playfieldCursor.pos.y), (playfieldCursor.pos.z));
        #endif
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
    
    glTranslatef((playfieldCursor.pos.x), (playfieldCursor.pos.y), (playfieldCursor.pos.z));
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
  
    switch (landscapeTypeState) {

        case 1: //Ground adjustment
                if (strcmp(tempArgs->key, "Dig") == 0){
                    completed = SC_Set_PlayfieldTile(playfieldCursor.column, playfieldCursor.row, tempArgs->key);
                    if (completed)
                        player.mat_sand += 10; //use up your source of sand to create a hill
                }

                if ((strcmp(tempArgs->key, "Fill") == 0) && (player.mat_sand - 10 >= 0)) {
                    completed = SC_Set_PlayfieldTile(playfieldCursor.column, playfieldCursor.row, tempArgs->key);
                    if (completed)
                        player.mat_sand -= 10; //use up your source of sand to create a hill
                }

            break;

        case 2:
                fprintf(stderr, "\n\n--------\n!!! Fill Water Event !!! \n--------\n\n");
                fprintf(stderr, "\n\n--------\n!!! Fill Water Event !!! \n--------\n\n");
                fprintf(stderr, "\n\n--------\n!!! Fill Water Event !!! \n--------\n\n");
                fprintf(stderr, "\n\n--------\n!!! Fill Water Event !!! \n--------\n\n");
            break;

        default: //Water Fill / Drain
            //Do nothing
            break;

    }
    
}


void SC_PlayfieldBuildEvent(g64_EventArgs* tempArgs) {
    fprintf(stderr, "\n\n--------\n!!! Place Object Event !!! \n--------\n\n");

    switch (buildingTypeState) {

        case 1: //Build a small tower
            //fprintf(stderr, "\n\n--------\n!!! Place Object !!! \n--------\n\n");
            if ((SC_SimpleTower_PF.pointsB <= player.mat_sand) && (SC_SimpleTower_PF.pointsC <= player.mat_shells)) { //Check to make sure you have enough materials to build
                S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
                S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_SimpleTower_PF;
                player.mat_sand -= SC_SimpleTower_PF.pointsB; // source the raw materials for this with sand
                player.mat_shells -= SC_SimpleTower_PF.pointsC; // pay for this build with shells
                city.residents += 2;
                city.buildings += 1;
            }
        
            break;

        case 2: //Build a large tower
            if ((SC_LargeTower_PF.pointsB <= player.mat_sand) && (SC_LargeTower_PF.pointsC <= player.mat_shells)) { //Check to make sure you have enough materials to build
                S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
                S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_LargeTower_PF;
                player.mat_sand -= SC_LargeTower_PF.pointsB; // source the raw materials for this with sand
                player.mat_shells -= SC_LargeTower_PF.pointsC; // pay for this build with shells
                city.residents += 4;
                city.buildings += 1;
            }
            break;

        case 3: //Build a watch tower
            if ((SC_WatchTower_PF.pointsB <= player.mat_sand) && (SC_WatchTower_PF.pointsC <= player.mat_shells)) { //Check to make sure you have enough materials to build
                S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
                S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_WatchTower_PF;
                player.mat_sand -= SC_WatchTower_PF.pointsB; // source the raw materials for this with sand
                player.mat_shells -= SC_WatchTower_PF.pointsC; // pay for this build with shells
                city.residents += 1;
                city.buildings += 1;
            }
            break;

            //----- Note ----- placeholder until all other models are completed
        default:
            if ((SC_LargeTower_PF.pointsB <= player.mat_sand) && (SC_LargeTower_PF.pointsC <= player.mat_shells)) { //Check to make sure you have enough materials to build
                S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
                S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_LargeTower_PF;
                player.mat_sand -= SC_LargeTower_PF.pointsB; // source the raw materials for this with sand
                player.mat_shells -= SC_LargeTower_PF.pointsC; // pay for this build with shells
                city.residents += 4;
                city.buildings += 1;
            }
            break;
    }

    S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.obj.pos = SCGet_Playfield_Tile_Position(playfieldCursor.column, playfieldCursor.row);

}

void SC_PlayfieldSalesTax_Update(g64_EventArgs* tempArgs) {

    int salesTaxIncome = (1 + (city.mood * .25)) * (city.residents * city.salesTaxRate);

    if(player.mat_shells + salesTaxIncome < 10000)
        player.mat_shells += salesTaxIncome;
    else
        player.mat_shells = 99999;
    
}

void SC_PlayfieldPropertyTax_Update(g64_EventArgs* tempArgs) {

    int propTaxIncome = (2 * (city.buildings * city.propertyTaxRate));

    if (player.mat_sand + propTaxIncome < 1000)
        player.mat_sand += propTaxIncome;
    else
        player.mat_sand = 999;

}