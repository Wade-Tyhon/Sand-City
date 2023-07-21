#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>
#include "ngin64/nGin64.h"





/* ----- To Do Notes for Sand City -----
*
*
*
*/


//Swap between different models with the C buttons
int modelSwitcher = 0;
int maxModel = 3.0f;

float scaleModel = 1.0f;
float maxScale = 10.0f;
float minScale = 0.25f;

extern void beach_scene_init();
extern void render_beach_scene();

//----- Note ----- Controller 
extern void gin64_Controller_Init();
extern void gin64_Controller_Update();

//----- Note ----- Player Interface / UI
extern void SC_Interface_Init();
extern void SC_Interface_Update();
extern void SC_Interface_Draw();


float deltaTime = 0.0f;

// Set this to 1 to enable rdpq debug output.
// The demo will only run for a single frame and stop.
#define DEBUG_RDP 0

//Setup on screen debug 
extern void g64_InitDebug();
extern void g64_UpdateDebug();
u8 debugUpdate;

static uint32_t animation = 3283;
static float distance = -10.0f;
static float cam_rotate = 0.0f;


static const GLfloat environment_color[] = { 0.1f, 0.03f, 0.2f, 0.5f };



GLfloat light_pos[2][4] = {
    { -18, 6, 18, 18 },
    { 18, 0, 0, 0 },
    //{ 0, 0, 1, 0 },
    //{ 0, 0, -1, 0 },
   // { 8, 3, 0, 1 },
   // { -8, 3, 0, 1 },
   // { 0, 3, 8, 1 },
   // { 0, 3, -8, 1 },
}; 

GLfloat light_diffuse[2][4] = {
    { 0.9f, .9f, 0.75f, 0.75f },
    { 0.55f, 0.5f, 0.45f, 0.3f },
    //{ 0.0f, 0.0f, 1.0f, 0.75f },
   // { 1.0f, 1.0f, 0.0f, 0.75f },
   // { 1.0f, 0.0f, 1.0f, 0.75f },
   // { 0.0f, 1.0f, 1.0f, 0.75f },
   // { 1.0f, 1.0f, 1.0f, 0.75f },
   // { 1.0f, 1.0f, 1.0f, 0.75f },
};





u8 textureTotal = 16; //used for loops
GLuint textures[16];
static sprite_t* sprites[16];


static const char *texture_path[16] = {
    "rom:/circle0.sprite",
    "rom:/diamond0.sprite",
    "rom:/pentagon0.sprite",
    "rom:/triangle0.sprite",    
    "rom:/Grass-Texture-1-Dirt.ci4.sprite",
    "rom:/Sand-Texture-4-Hill.ci4.sprite",
    "rom:/Grass-Texture-2.ci4.sprite",
    "rom:/Sand-Texture-1.ci4.sprite",
    "rom:/Sand-Texture-2-Wet.ci4.sprite",
    "rom:/Sand-Texture-3-Stones.ci4.sprite",
    "rom:/water_grey1.ci4.sprite",
    "rom:/beach_umbrella_tarp.ci4.sprite",
    "rom:/beach_umbrella_pole.ci4.sprite",
    "rom:/Beach_chair_cloth.ci4.sprite",    
    "rom:/beach_chair_legs_light.ci4.sprite",
    "rom:/beach_chair_legs_dark.ci4.sprite",
};




GLuint uiTextures[1];
static sprite_t* uiSprites[1];

static const char *ui_texture_path[1] = {

    "rom:/font_numbers.i4.sprite",
};


u8 waveTextureTotal = 52; //used for loops
GLuint waveTextures[52];
static sprite_t* waveSprites[52];

static const char* wave_texture_path[52] = {

    "rom:/beach_waves_sequence00.sprite",
    "rom:/beach_waves_sequence01.sprite",
    "rom:/beach_waves_sequence02.sprite",
    "rom:/beach_waves_sequence03.sprite",
    "rom:/beach_waves_sequence04.sprite",
    "rom:/beach_waves_sequence05.sprite",
    "rom:/beach_waves_sequence06.sprite",
    "rom:/beach_waves_sequence07.sprite",
    "rom:/beach_waves_sequence08.sprite",
    "rom:/beach_waves_sequence09.sprite",
    "rom:/beach_waves_sequence10.sprite",
    "rom:/beach_waves_sequence11.sprite",
    "rom:/beach_waves_sequence12.sprite",
    "rom:/beach_waves_sequence13.sprite",
    "rom:/beach_waves_sequence14.sprite",
    "rom:/beach_waves_sequence15.sprite",
    "rom:/beach_waves_sequence16.sprite",
    "rom:/beach_waves_sequence17.sprite",
    "rom:/beach_waves_sequence18.sprite",
    "rom:/beach_waves_sequence19.sprite",
    "rom:/beach_waves_sequence20.sprite",
    "rom:/beach_waves_sequence21.sprite",
    "rom:/beach_waves_sequence22.sprite",
    "rom:/beach_waves_sequence23.sprite",
    "rom:/beach_waves_sequence24.sprite",
    "rom:/beach_waves_sequence25.sprite",
    "rom:/beach_waves_sequence26.sprite",
    "rom:/beach_waves_sequence27.sprite",
    "rom:/beach_waves_sequence28.sprite",
    "rom:/beach_waves_sequence29.sprite",
    "rom:/beach_waves_sequence30.sprite",
    "rom:/beach_waves_sequence31.sprite",
    "rom:/beach_waves_sequence32.sprite",
    "rom:/beach_waves_sequence33.sprite",
    "rom:/beach_waves_sequence34.sprite",
    "rom:/beach_waves_sequence35.sprite",
    "rom:/beach_waves_sequence36.sprite",
    "rom:/beach_waves_sequence37.sprite",
    "rom:/beach_waves_sequence38.sprite",
    "rom:/beach_waves_sequence39.sprite",
    "rom:/beach_waves_sequence40.sprite",
    "rom:/beach_waves_sequence41.sprite",
    "rom:/beach_waves_sequence42.sprite",
    "rom:/beach_waves_sequence43.sprite",
    "rom:/beach_waves_sequence44.sprite",
    "rom:/beach_waves_sequence45.sprite",
    "rom:/beach_waves_sequence46.sprite",
    "rom:/beach_waves_sequence47.sprite",
    "rom:/beach_waves_sequence48.sprite",
    "rom:/beach_waves_sequence49.sprite",
    "rom:/beach_waves_sequence50.sprite",
    "rom:/beach_waves_sequence51.sprite",


};






void setup()
{
    
    for (uint32_t i = 0; i < textureTotal; i++)
    {
        sprites[i] = sprite_load(texture_path[i]);        
    }


    for (uint32_t i = 0; i < waveTextureTotal; i++)
    {
        waveSprites[i] = sprite_load(wave_texture_path[i]);
    }




    uiSprites[0] = sprite_load(ui_texture_path[0]);
    
    gin64_ProjSetup(); //Initial NGin64 Project Setup. (Many of these settings can be adjusted at run time if needed)

    gin64_Controller_Init(); 
    SC_Interface_Init();

    gin64_CamInit();
    g64_InitDebug(); //Set up on screen debug elements
    beach_scene_init();

    gin64_LightingUpdate(); //NOTE ----- Set up lights and fog

    glGenTextures(textureTotal, textures);

    #if 0
    GLenum min_filter = GL_LINEAR_MIPMAP_LINEAR;
    #else
    GLenum min_filter = GL_LINEAR;
    #endif

    for (uint32_t i = 0; i < textureTotal-1; i++)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

        glSpriteTextureN64(GL_TEXTURE_2D, sprites[i], &(rdpq_texparms_t) {.tmem_addr = 0, .palette = 0, .s.repeats = REPEAT_INFINITE, .t.repeats = REPEAT_INFINITE});

    }


    glGenTextures(waveTextureTotal, waveTextures);

    for (uint32_t i = 0; i < waveTextureTotal; i++)
    {
        glBindTexture(GL_TEXTURE_2D, waveTextures[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

        glSpriteTextureN64(GL_TEXTURE_2D, waveSprites[i], &(rdpq_texparms_t) {.tmem_addr = 0, .palette = 0, .s.repeats = REPEAT_INFINITE, .t.repeats = REPEAT_INFINITE});

    }


    glGenTextures(1, uiTextures);
    glBindTexture(GL_TEXTURE_2D, uiTextures[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

    glSpriteTextureN64(GL_TEXTURE_2D, uiSprites[0], &(rdpq_texparms_t) {.tmem_addr = 0, .palette = 0,});
    
}

void draw_quad()
{
    glBegin(GL_TRIANGLE_STRIP);
        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(-0.5f, 0, -0.5f);
        glTexCoord2f(0, 1);
        glVertex3f(-0.5f, 0, 0.5f);
        glTexCoord2f(1, 0);
        glVertex3f(0.5f, 0, -0.5f);
        glTexCoord2f(1, 1);
        glVertex3f(0.5f, 0, 0.5f);
    glEnd();
}

void render() 
{

    gin64_LightingUpdate(); //NOTE ----- Set up lights and fog

    gin64_BeginFrame(); //NGin64 Function - Clearing the frame buffer, the zbuffer, setting up the scene 

    gin64_CamView(distance, cam_rotate); //NGin64 Function - Setting up the camera and matrix for the current scene

    //----- Note ----- reset rendered tri counter: 
    gin64_ResetTriCounter();

    render_beach_scene();

    g64_UpdateDebug();

    SC_Interface_Draw();

    gin64_EndFrame(); //Perform any final funtions and gl_context_end

    rdpq_detach_show();
}




int main()
{
    debug_init_isviewer();
    debug_init_usblog();

    dfs_init(DFS_DEFAULT_LOCATION);

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE_FETCH_ALWAYS);

    rdpq_init();
    gl_init();

#if DEBUG_RDP
    rdpq_debug_start();
    rdpq_debug_log(true);
#endif

    

    setup();
    gin64_InitTimers();
    controller_init();

#if !DEBUG_RDP
    while (1)
#endif
    {

        gin64_SetDeltaTime();

        //controller_scan();
        //int dPadInput = get_dpad_direction(0);
        //struct controller_data pressed = get_keys_pressed();

        gin64_Controller_Update();

        /*
        if (dPadInput == 2) {
            if (scaleModel <= maxScale)
                scaleModel += .02f;
            else
                scaleModel = maxScale;
        }
        else if (dPadInput == 6) {
            if (scaleModel >= minScale)
                scaleModel -= .02f;
            else
                scaleModel = minScale;
        }
        */
        ngin64_UpdateCameraPosition();

        /*
        float camInputY = pressed.c[0].y / 128.f;
        float canInputX = pressed.c[0].x / 128.f;
        float mag = canInputX * canInputX + camInputY * camInputY;

        if (fabsf(mag) > 0.01f) {
            mainCamera.distance += camInputY * 0.2f;
        }
        */

        render();
        
        SC_Interface_Update();

            if (DEBUG_RDP)
                rspq_wait();


        
    }
    

}
