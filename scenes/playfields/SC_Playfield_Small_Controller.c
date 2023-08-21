#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../../ngin64/nGin64.h"
#include "../../interface/SC_Interface.h"
#include "../prefabs/castles/SC_CastlesTypes.h"



extern gl_XP64_Vert vert_BeachPlayfield[];
extern uint16_t poly_BeachPlayfield_Beach[];

extern uint16_t get_BeachPlayfield_Size();


playfieldState S_PlayfieldState_Current[16][7];
playfieldState S_PlayfieldState_Pending[16][7];

playfieldState S_PlayfieldState_TEMPSTORAGE[16][7];

extern u8 currentEditingMode;
//extern enum g64_EditModeState;
//extern enum g64_EditModeState editModeState;


extern GLuint textures[];
extern u8 textureTotal;

bool updateTopology = false;
bool recalcTopology = false;

const u8 pos_LOW = 4;
const u8 pos_MID = 6;
const u8 pos_HIGH = 8;

u8 next_position = 8;

u8 vColor_LOW[4] = { 165, 130, 140, 255 };
u8 vColor_MID[4] = { 211, 207, 207, 255 };
u8 vColor_HIGH[4] = { 255, 255, 255, 255 };

u8 next_vColor[4] = { 255, 255, 255, 255 };

int updateColumn = 0;
int updateRow = 0;


//int editableBlocks [112][4]
int editableBlocks[16][7][4] = {
    {{11,12,21,22},{12,13,22,23},{13,14,23,24},{14,15,24,25},{15,16,25,26},{16,17,26,27},{17,18,27,28},},
    {{21,22,31,32},{22,23,32,33},{23,24,33,34},{24,25,34,35},{25,26,35,36},{26,27,36,37},{27,28,37,38},},
    {{31,32,41,42},{32,33,42,43},{33,34,43,44},{34,35,44,45},{35,36,45,46},{36,37,46,47},{37,38,47,48},},
    {{41,42,51,52},{42,43,52,53},{43,44,53,54},{44,45,54,55},{45,46,55,56},{46,47,56,57},{47,48,57,58},},

    {{51,52,61,62},{52,53,62,63},{53,54,63,64},{54,55,64,65},{55,56,65,66},{56,57,66,67},{57,58,67,68},},
    {{61,62,71,72},{62,63,72,73},{63,64,73,74},{64,65,74,75},{65,66,75,76},{66,67,76,77},{67,68,77,78},},
    {{71,72,81,82},{72,73,82,83},{73,74,83,84},{74,75,84,85},{75,76,85,86},{76,77,86,87},{77,78,87,88},},
    {{81,82,91,92},{82,83,92,93},{83,84,93,94},{84,85,94,95},{85,86,95,96},{86,87,96,97},{87,88,97,98},},

    {{91,92,101,102},{92,93,102,103},{93,94,103,104},{94,95,104,105},{95,96,105,106},{96,97,106,107},{97,98,107,108},},
    {{101,102,111,112},{102,103,112,113},{103,104,113,114},{104,105,114,115},{105,106,115,116},{106,107,116,117},{107,108,117,118},},
    {{111,112,121,122},{112,113,122,123},{113,114,123,124},{114,115,124,125},{115,116,125,126},{116,117,126,127},{117,118,127,128},},
    {{121,122,131,132},{122,123,132,133},{123,124,133,134},{124,125,134,135},{125,126,135,136},{126,127,136,137},{127,128,137,138},},

    {{131,132,141,142},{132,133,142,143},{133,134,143,144},{134,135,144,145},{135,136,145,146},{136,137,146,147},{137,138,147,148},},
    {{141,142,151,152},{142,143,152,153},{143,144,153,154},{144,145,154,155},{145,146,155,156},{146,147,156,157},{147,148,157,158},},
    {{151,152,161,162},{152,153,162,163},{153,154,163,164},{154,155,164,165},{155,156,165,166},{156,157,166,167},{157,158,167,168},},
    {{161,162,171,172},{162,163,172,173},{163,164,173,174},{164,165,174,175},{165,166,175,176},{166,167,176,177},{167,168,177,178},},

};

u8 columnCounter = 0;
u8 tileCounter = 0;

u8 updatePlayfield = 0;

void s_playfield_init() {

    //updatePlayfield += 1;
    for(int column = 0; column < 16;  column++)
        for (int row = 0; row < 7; row++) {

            //----- Note -----  S_PlayfieldState_Current holds the current state of the playfield
            S_PlayfieldState_Current[column][row].updating = false; //Currently in the process of updating, no further changes can be made until completed
            S_PlayfieldState_Current[column][row].cursorActive = false; //Position of the cursor
            S_PlayfieldState_Current[column][row].groundHeight = pos_MID; //Position of playfield: standard, raised, lowered
            S_PlayfieldState_Current[column][row].water = 0; // no water, high water, mid water, low water, 
            S_PlayfieldState_Current[column][row].strutureType = 0; //House unit, tower, wall, lighthouse, etc
            S_PlayfieldState_Current[column][row].eventType = 0; //0 by default (no event), other events could be: "new resident" "received power" "upgrading to new structure" "damaged by waves" etc
            S_PlayfieldState_Current[column][row].status = 0; //New, damaged, deteriorating, destroyed
            S_PlayfieldState_Current[column][row].power = false; //Is power available in this structure (if applicable)
            S_PlayfieldState_Current[column][row].residents = 0; //Number of animal residents in this structure (if applicable)
            //S_PlayfieldState_Pending[column][row].structure = SC_WatchTower_PF;
            //S_PlayfieldState_Current[column][row].residents = NULL;

            //----- Note -----  S_PlayfieldState_Pending For assigning updates to the playfield... when boolean 'updating' is set to true on a particular tile, 
            //                  the updates will be compared against S_PlayfieldState_Current to figure out what changes need to be made
            S_PlayfieldState_Pending[column][row].updating = false; //Currently in the process of updating, no further changes can be made until completed
            S_PlayfieldState_Pending[column][row].cursorActive = false; //Currently in the process of updating, no further changes can be made until completed
            S_PlayfieldState_Pending[column][row].groundHeight = pos_MID; //Position of playfield: standard, raised, lowered
            S_PlayfieldState_Pending[column][row].water = 0; // no water, high water, mid water, low water, 
            S_PlayfieldState_Pending[column][row].strutureType = 0; //House unit, tower, wall, lighthouse, etc
            S_PlayfieldState_Pending[column][row].eventType = 0; //0 by default (no event), other events could be: "new resident" "received power" "upgrading to new structure" "damaged by waves" etc
            S_PlayfieldState_Pending[column][row].status = 0; //New, damaged, deteriorating, destroyed
            S_PlayfieldState_Pending[column][row].power = false; //Is power available in this structure (if applicable)
            S_PlayfieldState_Pending[column][row].residents = 0; //Number of animal residents in this structure (if applicable)
            //S_PlayfieldState_Pending[column][row].structure = SC_WatchTower_PF;
            //S_PlayfieldState_Pending[column][row].residents = NULL;
        }

    /*

    for (int column = 0; column < 16; column++)
        for (int row = 0; row < 7; row++) {

            S_PlayfieldState_Pending[column][row].updating = true;
            S_PlayfieldState_Pending[column][row].structure = SC_WatchTower_PF;

        }
    */

#ifdef DEBUG_NGIN64_INITFUNC
    fprintf(stderr, "\nInitiate Playfield\n\n");    
#endif

    recalcTopology = true;

}

void s_playfield_update(int column, int row) {


    if(editModeState == Landscape){

        updatePlayfield += 1;


    #ifdef DEBUG_NGIN64_INITFUNC
        fprintf(stderr, "\nUpdating Current [%i] to be Pending [%i]\n\n", S_PlayfieldState_Current[column][row].groundHeight, S_PlayfieldState_Pending[column][row].groundHeight);
    #endif

            
            
            

            
            
            S_PlayfieldState_TEMPSTORAGE[column][row].groundHeight = S_PlayfieldState_Current[column][row].groundHeight;
            

           // for (int i = 0; i < 4; i++){


            bool sharedVertices[4] = { true, true, true, true };

            int tempColumn = 0;
            int tempRow = 0;


            //----- Note -----  Do a check of surrounding tiles to see if they share vertices with the one aboutto be edited. 
            //                  If they do and they have an object on them, then do not update this vertex height.

            for (int i = 0; i < 8; i++)
            {
                if (i == 0)
                    tempColumn = column - 1;
                else if (i == 1)
                    tempColumn = column + 1;
                else if (i == 2)
                    tempRow = row - 1;
                else if (i == 3)
                    tempRow = row + 1;
                else if (i == 4) {
                    tempColumn = column - 1;
                    tempRow = row - 1;
                }
                else if (i == 5) {
                    tempColumn = column + 1;
                    tempRow = row - 1;
                }
                else if (i == 6) {
                    tempColumn = column - 1;
                    tempRow = row + 1;
                }
                else if (i == 6) {
                    tempColumn = column + 1;
                    tempRow = row + 1;
                }



                if (S_PlayfieldState_Current[tempColumn][tempRow].structure.staticModel_LOD[2].glDisplayList) {
                


                    

                    S_PlayfieldState_TEMPSTORAGE[tempColumn][tempRow].groundHeight = S_PlayfieldState_Current[tempColumn][tempRow].groundHeight;
                    /*
                    for (int i = 0; i < 4; i++) {
                    
                        for (int z = 0; z < 4; z++) {

                            if (editableBlocks[column][row][i] == editableBlocks[tempColumn][tempRow][z])
                                sharedVertices[i] = false;
                        }
                    }*/
                }
                
            }

            S_PlayfieldState_Current[column][row].groundHeight = S_PlayfieldState_Pending[column][row].groundHeight;


            for (int i = 0; i < 4; i++) {


               // if (sharedVertices[i] == true) {

                    //if(vert_BeachPlayfield[editableBlocks[column][row][i]].pos[2] != S_PlayfieldState_Pending[column][row].groundHeight){
                     //if (!S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.staticModel_LOD[2].glDisplayList){

                    vert_BeachPlayfield[editableBlocks[column][row][i]].pos[2] = S_PlayfieldState_Pending[column][row].groundHeight;

                    if (S_PlayfieldState_Current[column][row].groundHeight == pos_LOW) {
                        vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[0] = vColor_LOW[0];
                        vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[1] = vColor_LOW[1];
                        vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[2] = vColor_LOW[2];
                    }

                    else if (S_PlayfieldState_Current[column][row].groundHeight == pos_MID) {
                        vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[0] = vColor_MID[0];
                        vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[1] = vColor_MID[1];
                        vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[2] = vColor_MID[2];
                    }

                    else if (S_PlayfieldState_Current[column][row].groundHeight == pos_HIGH) {
                        vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[0] = vColor_HIGH[0];
                        vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[1] = vColor_HIGH[1];
                        vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[2] = vColor_HIGH[2];
                    }
               // }
                //}
            }

        //}


        if (S_PlayfieldState_Current[column][row].groundHeight == S_PlayfieldState_Pending[column][row].groundHeight)
        {
            S_PlayfieldState_Pending[column][row].updating = false;
            recalcTopology = true;
        }

        /*
        for (int i = 0; i < 8; i++)
        {
            if (i == 0)
                tempColumn = column - 1;
            else if (i == 1)
                tempColumn = column + 1;
            else if (i == 2)
                tempRow = row - 1;
            else if (i == 3)
                tempRow = row + 1;
            else if (i == 4) {
                tempColumn = column - 1;
                tempRow = row - 1;
            }
            else if (i == 5) {
                tempColumn = column + 1;
                tempRow = row - 1;
            }
            else if (i == 6) {
                tempColumn = column - 1;
                tempRow = row + 1;
            }
            else if (i == 7) {
                tempColumn = column + 1;
                tempRow = row + 1;
            }


            if (tempColumn > 6)
                tempColumn = 6;
            else if (tempColumn < 0)
                tempColumn = 0;

            if (tempRow > 15)
                tempRow = 15;
            else if (tempRow < 0)
                tempRow = 0;

            //fprintf(stderr, "\n FIX PLAYFIELD HEIGHT!!!!!!!!\n");
            //fprintf(stderr, "\n FIX PLAYFIELD HEIGHT2!!!!!!!!\n");
            //fprintf(stderr, "\n FIX PLAYFIELD HEIGHT3!!!!!!!!\n");
            //fprintf(stderr, "\n FIX PLAYFIELD HEIGHT4!!!!!!!!\n\n\n");

            
            if (S_PlayfieldState_Current[tempColumn][tempRow].structure.staticModel_LOD[2].glDisplayList) {
                
                //S_PlayfieldState_TEMPSTORAGE[column][row].groundHeight


                fprintf(stderr, "\n FIX PLAYFIELD HEIGHT!!!!!!!!\n");
                fprintf(stderr, "\n FIX PLAYFIELD HEIGHT!!!!!!!!\n");
                fprintf(stderr, "\n FIX PLAYFIELD HEIGHT!!!!!!!!\n");
                fprintf(stderr, "\n FIX PLAYFIELD HEIGHT!!!!!!!!\n\n\n");

                for (int i = 0; i < 4; i++) {

                    fprintf(stderr, "\n FIX PLAYFIELD HEIGHT!!!!!!!!\n");
                    fprintf(stderr, "\n FIX PLAYFIELD HEIGHT!!!!!!!!\n");
                    fprintf(stderr, "\n FIX PLAYFIELD HEIGHT!!!!!!!!\n");
                    fprintf(stderr, "\n FIX PLAYFIELD HEIGHT!!!!!!!!\n\n\n");

                    vert_BeachPlayfield[editableBlocks[tempColumn][tempRow][i]].pos[2] = S_PlayfieldState_TEMPSTORAGE[tempColumn][tempRow].groundHeight;

                    if (S_PlayfieldState_TEMPSTORAGE[tempColumn][tempRow].groundHeight == pos_LOW) {
                        vert_BeachPlayfield[editableBlocks[tempColumn][tempRow][i]].vColor[0] = vColor_LOW[0];
                        vert_BeachPlayfield[editableBlocks[tempColumn][tempRow][i]].vColor[1] = vColor_LOW[1];
                        vert_BeachPlayfield[editableBlocks[tempColumn][tempRow][i]].vColor[2] = vColor_LOW[2];
                    }

                    else if (S_PlayfieldState_TEMPSTORAGE[tempColumn][tempRow].groundHeight == pos_MID) {
                        vert_BeachPlayfield[editableBlocks[tempColumn][tempRow][i]].vColor[0] = vColor_MID[0];
                        vert_BeachPlayfield[editableBlocks[tempColumn][tempRow][i]].vColor[1] = vColor_MID[1];
                        vert_BeachPlayfield[editableBlocks[tempColumn][tempRow][i]].vColor[2] = vColor_MID[2];
                    }

                    else if (S_PlayfieldState_TEMPSTORAGE[tempColumn][tempRow].groundHeight == pos_HIGH) {
                        vert_BeachPlayfield[editableBlocks[tempColumn][tempRow][i]].vColor[0] = vColor_HIGH[0];
                        vert_BeachPlayfield[editableBlocks[tempColumn][tempRow][i]].vColor[1] = vColor_HIGH[1];
                        vert_BeachPlayfield[editableBlocks[tempColumn][tempRow][i]].vColor[2] = vColor_HIGH[2];
                    }

                }

            }
            
                
        }



        */


        for (int column = 0; column < 16; column++)
            for (int row = 0; row < 7; row++) {            
                
                if (S_PlayfieldState_Current[column][row].structure.staticModel_LOD[2].glDisplayList){

                    for (int i = 0; i < 4; i++) {

                        vert_BeachPlayfield[editableBlocks[column][row][i]].pos[2] = S_PlayfieldState_Pending[column][row].structure.obj.pos.z;
                        S_PlayfieldState_Pending[column][row].groundHeight = S_PlayfieldState_Pending[column][row].structure.obj.pos.z;

                        if (vert_BeachPlayfield[editableBlocks[column][row][i]].pos[2] == pos_LOW) {
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[0] = vColor_LOW[0];
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[1] = vColor_LOW[1];
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[2] = vColor_LOW[2];
                        }

                        else if (vert_BeachPlayfield[editableBlocks[column][row][i]].pos[2] == pos_MID) {
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[0] = vColor_MID[0];
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[1] = vColor_MID[1];
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[2] = vColor_MID[2];
                        }

                        else if (vert_BeachPlayfield[editableBlocks[column][row][i]].pos[2] == pos_HIGH) {
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[0] = vColor_HIGH[0];
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[1] = vColor_HIGH[1];
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[2] = vColor_HIGH[2];
                        }

                        else {
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[0] = vColor_MID[0];
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[1] = vColor_MID[1];
                            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[2] = vColor_MID[2];
                        }


                      //  vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[0] = vColor_HIGH[0];
                      //  vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[1] = vColor_HIGH[1];
                      //  vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[2] = vColor_HIGH[2];

                        S_PlayfieldState_Current[column][row].groundHeight = S_PlayfieldState_Pending[column][row].groundHeight;
                        //S_PlayfieldState_Current[column][row].structure = S_PlayfieldState_Pending[column][row].structure;


                    }

                }

                
            
        }


    #ifdef DEBUG_NGIN64_INITFUNC
        fprintf(stderr, "\nUpdated Playfield %i Times!\n\n", updatePlayfield);
    #endif
    }


    else if (editModeState == Building) {

        S_PlayfieldState_Current[column][row].structure = S_PlayfieldState_Pending[column][row].structure;
        S_PlayfieldState_Pending[column][row].groundHeight = S_PlayfieldState_Current[column][row].groundHeight;
        S_PlayfieldState_Pending[column][row].updating = false;
    }



}




void s_playfield_update_OLD(int column, int row) {



    updatePlayfield += 1;


#ifdef DEBUG_NGIN64_INITFUNC
    fprintf(stderr, "\nUpdating Current [%i] to be Pending [%i]\n\n", S_PlayfieldState_Current[column][row].groundHeight, S_PlayfieldState_Pending[column][row].groundHeight);
#endif

    S_PlayfieldState_Current[column][row].groundHeight = S_PlayfieldState_Pending[column][row].groundHeight;

    // for (int i = 0; i < 4; i++){


    for (int i = 0; i < 4; i++) {

        //if(vert_BeachPlayfield[editableBlocks[column][row][i]].pos[2] != S_PlayfieldState_Pending[column][row].groundHeight){

        vert_BeachPlayfield[editableBlocks[column][row][i]].pos[2] = S_PlayfieldState_Pending[column][row].groundHeight;

        if (S_PlayfieldState_Current[column][row].groundHeight == pos_LOW) {
            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[0] = vColor_LOW[0];
            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[1] = vColor_LOW[1];
            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[2] = vColor_LOW[2];
        }

        else if (S_PlayfieldState_Current[column][row].groundHeight == pos_MID) {
            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[0] = vColor_MID[0];
            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[1] = vColor_MID[1];
            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[2] = vColor_MID[2];
        }

        else if (S_PlayfieldState_Current[column][row].groundHeight == pos_HIGH) {
            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[0] = vColor_HIGH[0];
            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[1] = vColor_HIGH[1];
            vert_BeachPlayfield[editableBlocks[column][row][i]].vColor[2] = vColor_HIGH[2];
        }

        //}
    }

    //}

    if (S_PlayfieldState_Current[column][row].groundHeight == S_PlayfieldState_Pending[column][row].groundHeight)
    {
        S_PlayfieldState_Pending[column][row].updating = false;
        recalcTopology = true;
    }

    S_PlayfieldState_Current[column][row].structure = S_PlayfieldState_Pending[column][row].structure;

#ifdef DEBUG_NGIN64_INITFUNC
    fprintf(stderr, "\nUpdated Playfield %i Times!\n\n", updatePlayfield);
#endif

}

void s_playfield_check() {

    //----- Note ------ loop through S_PlayfieldState_Pending to see if any tiles have 'updating' set to 'true'


    updatePlayfield = 0;

    for (int column = 0; column < 16; column++)
        for (int row = 0; row < 7; row++) {
            
            if (S_PlayfieldState_Pending[column][row].updating == true) {


                s_playfield_update(column, row);

                #ifdef DEBUG_NGIN64_INITFUNC
                                fprintf(stderr, "\n Need to update S_PlayfieldState_Pending[%i][%i]!\n\n", column, row);
                #endif
            }

        
        }

}



uint16_t playfieldSize = 0;


bool fireOnce = 0;
GLuint playfield;

void draw_beach_playfield()
{

    if(playfieldSize == 0){
        playfieldSize = get_BeachPlayfield_Size();
    }


    if (recalcTopology) {

        playfield = glGenLists(1);
        glNewList(playfield, GL_COMPILE);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer(3, GL_FLOAT, sizeof(gl_XP64_Vert), (void*)(0 * sizeof(float) + (void*)vert_BeachPlayfield));
        glTexCoordPointer(2, GL_FLOAT, sizeof(gl_XP64_Vert), (void*)(3 * sizeof(float) + (void*)vert_BeachPlayfield));
        glNormalPointer(GL_FLOAT, sizeof(gl_XP64_Vert), (void*)(5 * sizeof(float) + (void*)vert_BeachPlayfield));
        glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(gl_XP64_Vert), (void*)(8 * sizeof(float) + (void*)vert_BeachPlayfield));

        glBindTexture(GL_TEXTURE_2D, textures[7]); //>----- UPDATE ----- rebind with the new material settings
        glDrawElements(GL_TRIANGLES, playfieldSize / sizeof(uint16_t), GL_UNSIGNED_SHORT, poly_BeachPlayfield_Beach);


        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        glEndList();
    
        recalcTopology = false;
    }

    gin64_UpdateTriCounter(320);

}



Vector3 SCGet_Playfield_Tile_Position(int column, int row)
{
    //----- Note ----- Increasing X and Y by 1 to center it in each tile. Increasing Z by .25f so that there is no clipping and Z figthing with the ground plane
    Vector3 bottomLeftTile = { vert_BeachPlayfield[editableBlocks[column][row][0]].pos[0] + 1, vert_BeachPlayfield[editableBlocks[column][row][0]].pos[1] + 1, vert_BeachPlayfield[editableBlocks[column][row][0]].pos[2] + .25f };

    return bottomLeftTile;
}

u8 SC_Set_PlayfieldTile(int column, int row, char update[12])
{

    u8 currentHeight = S_PlayfieldState_Pending[column][row].groundHeight;

    u8 positions[4];

    u8 lowCount = 0;
    u8 midCount = 0;
    u8 highCount = 0;

    if (editModeState == Landscape) {

        for (int i = 0; i < 4; i++) {

            //if(vert_BeachPlayfield[editableBlocks[column][row][i]].pos[2] != S_PlayfieldState_Pending[column][row].groundHeight){

            positions[i] = vert_BeachPlayfield[editableBlocks[column][row][i]].pos[2];

            if (positions[i] == pos_LOW)
                lowCount += 1;
            if (positions[i] == pos_MID)
                midCount += 1;
            if (positions[i] == pos_HIGH)
                highCount += 1;

            //if (!S_PlayfieldState_Current[playfieldCursor.column][playfieldCursor.row].structure.staticModel_LOD[2].glDisplayList) {

            //ert_BeachPlayfield[editableBlocks[column][row][i]].pos[2] = S_PlayfieldState_Pending[column][row].groundHeight;
        }


        u8 sandQty = 0;

        if (strcmp(update, "Dig") == 0) {

            gin64_Audio_SFX_Play("rom:/Dig_silence.wav64");

            if (highCount >= 1)
                currentHeight = pos_HIGH;
            else if (midCount >= 1)
                currentHeight = pos_MID;
            else
                currentHeight = pos_LOW;


            switch (currentHeight) {

            case pos_HIGH:
                S_PlayfieldState_Pending[column][row].updating = true;
                S_PlayfieldState_Pending[column][row].groundHeight = pos_MID;
                return highCount * 2;
            case pos_MID:
                S_PlayfieldState_Pending[column][row].updating = true;
                S_PlayfieldState_Pending[column][row].groundHeight = pos_LOW;
                return midCount * 2;
            case pos_LOW:
                S_PlayfieldState_Pending[column][row].updating = false;
                return 0;
            }

            return 0;
        }

        else if (strcmp(update, "Fill") == 0) {


            gin64_Audio_SFX_Play("rom:/Fill_silence.wav64");
            if (lowCount >= 1)
                currentHeight = pos_LOW;
            else if (midCount >= 1)
                currentHeight = pos_MID;
            else
                currentHeight = pos_HIGH;


            switch (currentHeight) {

            case pos_LOW:
                S_PlayfieldState_Pending[column][row].updating = true;
                S_PlayfieldState_Pending[column][row].groundHeight = pos_MID;
                return lowCount * 2;
            case pos_MID:
                S_PlayfieldState_Pending[column][row].updating = true;
                S_PlayfieldState_Pending[column][row].groundHeight = pos_HIGH;
                return midCount * 2;
            case pos_HIGH:
                S_PlayfieldState_Pending[column][row].updating = false;
                return 0;
            }

            return 0;

        }
    }
    else {

        S_PlayfieldState_Pending[column][row].updating = false;
        return 0;
    }

    return 0;
}