#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../ngin64/nGin64.h"

#include "SC_Scene_Defs.h"
#include "prefabs/creatures/SC_CreatureTypes.h"


GameObject invisiblePoint = {
    {5,0,5},
    {0,0,0},
    {1, 1, 1}
};

g64_NPCObjectPrefab SC_KingCrab_TitleScreen;
//SC_KingCrab_PF kingCrabTitleScreen;


void SC_Scene_Title_Init() {

    s_playfield_init();
    SC_CrabPrefabs_Init();

    SC_KingCrab_TitleScreen = SC_KingCrab_PF;

    ngin64_UpdateCamFollow(&SC_KingCrab_TitleScreen.obj);
    //SC_Prefabs_Init();

}

void SC_Scene_Title_Render() {

    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(1, 1, 1);
    glShadeModel(GL_SMOOTH);
    // Apply to ambient and diffuse material properties
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //draw_beach();
    SC_TitleBeach_Draw();

    glPopMatrix();


   // glPushMatrix();
    //draw_beach_playfield();

    //glCallList(playfield);
   // glPopMatrix();

    glPushMatrix();
    //SC_Prefabs_DrawCastles();
    SC_CrabPrefabs_Draw(&SC_KingCrab_TitleScreen);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0, 7);
    //SC_Crab_DL_LOD0();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -.35f);
    SC_TitleWaves_Draw();
    glPopMatrix();

   glPushMatrix();
   glTranslatef(-25, 21, 8);
   draw_beach_umbrella();
   draw_beach_chair();

   glPopMatrix();



    glDisable(GL_COLOR_MATERIAL);
}
