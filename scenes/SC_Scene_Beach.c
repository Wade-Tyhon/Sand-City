#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../ngin64/nGin64.h"

//extern draw_beach_items();




/* ----- To Do Notes -----
*
*           - Set up smooth lerp for each increase raising or lowering of the sand level
*           - Make the sand look more three dimensional by either:
                - Or adjust the vertex color of vertexes next to raised vertexes to make it look like a shadow is being cast.
            - Create a screen cursor to indicate where to adjust topogrophy
            - Button controls for scooping or pouring sand



            - Found a good way to separate mesh files and controller files!
                -   Create a  variable to hold the "sizeOf()' in each mesh .c file
                -   See "uint16_t get_BeachPlayfield_Size()" in playfield_small.c for an example

            - Figured out why I am not unable to re-update [12][5]
                -   The following if statement:
                    "if (S_PlayfieldState_Current[column][row].groundHeight != S_PlayfieldState_Pending[column][row].groundHeight)"
                    if seeing that they're the "same" even though the actual vertices are half correct and half not correct
                 -  Instead, compare each vertex height to make sure that ALL vertices are adjusted to the new height. 
                    Such as looping over each index [i]:
                    "if (vert_BeachPlayfield[editableBlocks[column][row][i]].pos[2] != S_PlayfieldState_Pending[column][row].groundHeight)"




*/






//----- Init functions -----
extern void s_playfield_init(); //initiate the scene playfield to be its default state
extern void s_playfield_check();

//----- Draw / render functions -----
extern void SC_Prefabs_Init();
extern void draw_beach_playfield();
extern void draw_beach_chair();
extern void draw_beach_umbrella();
extern void draw_beach();
extern void draw_waves();
extern void draw_castle_watchtower();

extern void SC_Crab_DL_LOD0();

//----- Prefab Names -----
void SC_Prefabs_DrawCastles();

void beach_scene_init() {

    s_playfield_init();
    SC_Prefabs_Init();
}

void update_beach_scene() {

    s_playfield_check();

}

extern GLuint playfield;

void render_beach_scene() {


    update_beach_scene();


    glPushMatrix();
        glTranslatef(0, 0, 0);
        glScalef(1, 1, 1);
        glShadeModel(GL_SMOOTH);
        // Apply to ambient and diffuse material properties
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        draw_beach();
    glPopMatrix();


    glPushMatrix();
        draw_beach_playfield();
    
        glCallList(playfield);
    glPopMatrix();

    glPushMatrix();
        SC_Prefabs_DrawCastles();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0, 7);
    //SC_Crab_DL_LOD0();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 0);
    draw_waves();
    glPopMatrix();
    
    //glPushMatrix();
   // glTranslatef(-15, 17, 10);
   // draw_beach_umbrella();
   // draw_beach_chair();
   // glPopMatrix();

    

    glDisable(GL_COLOR_MATERIAL);
}
