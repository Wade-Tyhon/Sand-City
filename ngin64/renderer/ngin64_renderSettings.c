#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../nGin64.h"



/* ----- To Do Notes -----
*
*           - Begin integration of camera controls with ngin64_ControllerInput
*				- Set up camera controls to instead take input that is stored in the ngin64_ControllerInput
*               - This will allow for players to choose their button combination and allow me to normalize the input before sending it to camera controller
*               - Adjust all distances so that "float adjustScale = 0.03f;" will no longer be needed.
*/



extern CursorObject playfieldCursor;


surface_t zbuffer;
surface_t* disp;

float aspect_ratio;
float near_plane;
float far_plane;

void gin64_DisplaySetup() {

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE);

    zbuffer = surface_alloc(FMT_RGBA16, display_get_width(), display_get_height());

    aspect_ratio = (float)display_get_width() / (float)display_get_height();


    near_plane = viewSettings.nearPlane;
    far_plane = viewSettings.farPlane;
    

}

void gin64_ProjSetup() {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);

    //----- Note ----- Projection
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-near_plane * aspect_ratio, near_plane * aspect_ratio, -near_plane, near_plane, near_plane, far_plane);
    
}



/*------------------------------NGin64 Frame Update Defaults---------------------------------*/
void gin64_BeginFrame() {

    float fps;

    surface_t* disp = display_get();
    rdpq_attach(disp, &zbuffer);

    gin64_fps(); //calculate current frame rate
    fps = gin64_GetFPS(); //get current frame rate

#ifdef DEBUG_NGIN64_CAMERA
    fprintf(stderr, " -FPS: %i   ", (int)fps);
#endif

    gl_context_begin();

   // Set up 
    glClearColor(viewSettings.backgroundColor.r, viewSettings.backgroundColor.g, viewSettings.backgroundColor.b, viewSettings.backgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}



//if (SC_GameState.titleScreen.active) {
  //  if (SC_GameState.playfieldMain.active) {






void gin64_EndFrame() {

    gl_context_end();

}

void gin64_LightingUpdate() {
    
    float tempFog[] = {
        viewSettings.fogColor.r,
        viewSettings.fogColor.g,
        viewSettings.fogColor.b,
        viewSettings.fogColor.a
    };
    
    
    
    glFogf(GL_FOG_START, viewSettings.fogNear);
    glFogf(GL_FOG_END, viewSettings.fogFar);
    glFogfv(GL_FOG_COLOR, tempFog);

    glDisable(GL_LIGHTING);
}
