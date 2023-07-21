#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../ngin64/nGin64.h"
#include "SC_Interface.h"
#include "../scenes/prefabs/castles/SC_CastlesTypes.h"

//extern void g64_ControllerInput();
//Gin64_GameplayInput


/* ----- To Do Notes for Sand City -----
* 
*   - I am now storing references to prefab display lists inside of 'S_PlayfieldState_Pending'
*       - these will be saved in the variable 'g64_EnvObjectPrefab* structure';
*       - these will be drawn at the end of each frame after the environment and playfield but before transparent objects
*       - Create a NEW render function where all of the objects can be cycled through at the end of each frame such as:
*           RenderInstanceObjects()
*               - look for instances of 'SC_TallTower_PF' inside of 'S_PlayfieldState_Pending'
*               - draw each instance of each object with a rendering function 
*       - look at 'RenderInstanceObj(&Beach_palm_single001,3000); //RenderInstanceObj(instance object name, LODStep) (ex > 5000 = LOD1, ? 10000 = LOD2)'

* 
* 
* 
* 
* 
*   - Figure out how to do alpha transparency with vector colors...
*   - Refine the playback framerate function 'SC_Playfield_Control_Update' to make for smooth movement 
    - Create a playback framerate function counter in ngin64_tools for animations fo textures, models, and cursor movements 

*   - Tie position of the 'poly_SelectGroundUI_Beach' interface element to the playfield state 'S_PlayfieldState_Current'
*   - Get player input from g64_Pad[0], which is saved in ngin64_ControllerInput
*       -   Test different options for input includign Dpad, Cpad and Analog stick input
*       -   If directional input is held down: 
            Immediately initiate movement then hold for a fraction of a second
            If direction is still held down, move a second time then wait for a smaller fraction of a second
            If direction is still held down, move a third time then wait for a smaller fraction of a second

    
*
*/
/*
typedef struct {

    //Vector2 activeTile;
    int column;
    int row;
    Vector3 pos;
}CursorObject;
*/

extern gl_XP64_Vert vert_SelectStructureUI[];
extern uint16_t poly_SelectStructureUI[];
extern uint16_t SCGet_poly_SelectStructureUI_Size();
uint16_t poly_SelectStructureUI_Size;

extern gl_XP64_Vert vert_SelectGroundUI[];
extern uint16_t poly_SelectGroundUI_Beach[];
extern uint16_t SCGet_poly_SelectGroundUI_Beach_Size();
uint16_t poly_SelectGroundUI_Beach_Size;

extern gl_XP64_Vert vert_BeachPlayfield[];
extern playfieldState S_PlayfieldState_Pending[16][7];
extern playfieldState S_PlayfieldState_Current[16][7];
extern int editableBlocks[16][7][4];
extern Vector3 SCGet_Playfield_Tile_Position(int column, int row);
extern bool SC_Set_PlayfieldTile(int column, int row, char update[12]);


CursorObject playfieldCursor;


//Vector3 newCursorPosition;

void SC_Playfield_Control_Init() {

    poly_SelectGroundUI_Beach_Size = SCGet_poly_SelectGroundUI_Beach_Size();
    S_PlayfieldState_Pending[8][4].cursorActive = true;

    playfieldCursor.column = 8;
    playfieldCursor.row = 4;

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

void SC_Playfield_Control_Update() {

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



        //----- Note ----- Check for filling or digging into the sand
        //g64_Pad[0].Press.A = press.c[0].A;
        // g64_Pad[0].Press.B = press.c[0].B;

        bool completed = false;

        if (g64_Pad[0].Press.B == 1) {
            char command[12] = "Dig";
            completed = SC_Set_PlayfieldTile(playfieldCursor.column, playfieldCursor.row, command);
        }

        else if (g64_Pad[0].Press.A == 1){
            char command[12] = "Fill";
            completed = SC_Set_PlayfieldTile(playfieldCursor.column, playfieldCursor.row, command);
        }


        if (g64_Pad[0].Press.L == 1) {
            S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].updating = true;
            S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure = SC_SimpleTower_PF;
            S_PlayfieldState_Pending[playfieldCursor.column][playfieldCursor.row].structure.obj.pos = SCGet_Playfield_Tile_Position(playfieldCursor.column, playfieldCursor.row);
        }


        if (completed == false) {

            #ifdef DEBUG_NGIN64_INTERFACE
                    fprintf(stderr, "\n > SC_Playfield_Control_Update - Playfield Not Updated! \n");
            #endif
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

void SC_Playfield_Control_Draw() {

    if (assigned == false){
        S_PlayfieldState_Pending[8][4].updating = true;
        S_PlayfieldState_Pending[8][4].structure = SC_SimpleTower_PF;
        S_PlayfieldState_Pending[8][4].structure.obj.pos = SCGet_Playfield_Tile_Position(8, 4);


        S_PlayfieldState_Pending[6][4].updating = true;
        S_PlayfieldState_Pending[6][4].structure = SC_TallTower_PF;
        S_PlayfieldState_Pending[6][4].structure.obj.pos = SCGet_Playfield_Tile_Position(6, 4);

        assigned = true;
    }

    glPushMatrix();

    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    // Apply vertex color as material color.
    // Because the cube has colors set per vertex, we can color each face seperately
    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_FOG)
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