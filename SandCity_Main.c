#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>
#include "ngin64/nGin64.h"
#include "scenes/SC_Scene_Defs.h"
#include "scenes/prefabs/creatures/SC_CreatureTypes.h"




/* ----- To Do Notes for Sand City -----
*
*   07262023
*   - Refine the outer rim of the playfield to reduce the number of polygons needed and import new mesh
*       - NOTE - this has been exported and is commented out in SC_Playfield_Small.c. 
        - It will require adjusting the vertices referenced in ' int editableBlocks[16][7][4] '

*   - Set up a simple text based UI for current object selection (small tower, large tower, watch tower, etc) 
*   
*   - Create a set UI element for placement of extra sand
*   - Have "Ditches" fill with water
*   - Fix the tri counter which is not properly re-setting for each model type
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
extern void gin64_InitDebug();
extern void gin64_UpdateDebug();
u8 debugUpdate;

static uint32_t animation = 3283;
static float distance = -10.0f;
static float cam_rotate = 0.0f;


static const GLfloat environment_color[] = { 0.1f, 0.03f, 0.2f, 0.5f };



GLfloat light_pos[2][4] = {
    { -18, 6, 18, 18 },
    { 18, 0, 0, 0 },

}; 

GLfloat light_diffuse[2][4] = {
    { 0.9f, .9f, 0.75f, 0.75f },
    { 0.55f, 0.5f, 0.45f, 0.3f },

};





u8 textureTotal = 21; //used for loops
GLuint textures[21];
static sprite_t* sprites[21];


static const char *texture_path[21] = {
    "rom:/circle0.sprite",
    "rom:/diamond0.sprite",
    "rom:/pentagon0.sprite",
    "rom:/triangle0.sprite",    
    "rom:/Grass-Texture-1-Dirt.ci4.sprite",
    "rom:/Sand-Texture-4-Hill.ci4.sprite", //5
    "rom:/Grass-Texture-2.ci4.sprite",
    "rom:/Sand-Texture-1.ci4.sprite",
    "rom:/Sand-Texture-2-Wet.ci4.sprite",
    "rom:/Sand-Texture-3-Stones.ci4.sprite",
    "rom:/water_grey1.ci4.sprite", //10
    "rom:/beach_umbrella_tarp.ci4.sprite",
    "rom:/beach_umbrella_pole.ci4.sprite",
    "rom:/Beach_chair_cloth.ci4.sprite",    
    "rom:/beach_chair_legs_light.ci4.sprite",
    "rom:/beach_chair_legs_dark.ci4.sprite", //15
    "rom:/Crab_Shell.ci4.sprite",
    "rom:/Crab_Legs.ci4.sprite",
    "rom:/Crab_Legs_2.ci4.sprite",
    "rom:/Crab_Accessories.ci4.sprite",
    "rom:/Beach_Reflection_Daytime.ci4.sprite",//20
    
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




//g64_TimeEvent TaxEvent;
//g64_GameTimer TaxTimer = { 0, 0, 10.0f };
 

extern void SC_Events_Init();
extern void SC_Events_Update();
void SC_Setup()
{



    //----- Note ------ Change this throughout the game in false,order to adjust what appears on screen
    /**/
    SC_GameState.titleScreen.active = true;
    SC_GameState.playfieldMain.active = false;
    
    
    /*
    SC_GameState.titleScreen.active = false;
    SC_GameState.playfieldMain.active = true;
    */


    //SC_GameState.playfieldMenu.active = true;
    


    //----- Note ------------------------- NGin64 General Setup ------------------------------------
    gin64_ProjSetup(); //Initial NGin64 Project Setup. (Many of these settings can be adjusted at run time if needed)

    gin64_Controller_Init(); // Note - set up controller input

    gin64_InitDebug(); //Note - Set up on screen debug elements

    gin64_CamInit(); //Note - Set up camera functions   


    //Note - Music Init 1:
    //gin64_XMAudio_Init(); //Note - Set up audio functions
    gin64_WAVAudio_Init(); //Note - Set up audio functions
    //----------------------------------------------------------------------------------------------






    //----- Note --------------------------- Sand City Setup ---------------------------------------

    for (uint32_t i = 0; i < textureTotal; i++)
    {
        sprites[i] = sprite_load(texture_path[i]);
    }


    for (uint32_t i = 0; i < waveTextureTotal; i++)
    {
        waveSprites[i] = sprite_load(wave_texture_path[i]);
    }


    uiSprites[0] = sprite_load(ui_texture_path[0]);

    SC_Events_Init(); //----- Note ----- All events need to be initiated before other gameplay scripts so that scripts can subscribe to each event!

    SC_Interface_Init();

   // void SC_Playfield_Structure_Menu_Init()


    if (SC_GameState.titleScreen.active)
    {
        ngin64_UpdateCamFollow(&playfieldCursor.obj);
        SC_Scene_Title_Init();
    }
        

    else if(SC_GameState.playfieldMain.active || SC_GameState.playfieldMenu.active){
        ngin64_UpdateCamFollow(&playfieldCursor.obj);
        beach_scene_init();
    }
    //----------------------------------------------------------------------------------------------





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

void render() 
{
    if (SC_GameState.titleScreen.active) {

        gin64_BeginFrame(); //NGin64 Function - Clearing the frame buffer, the zbuffer, setting up the scene 
        gin64_LightingUpdate(); //NOTE ----- Set up lights and fog
        gin64_CamView(distance, cam_rotate); //NGin64 Function - Setting up the camera and matrix for the current scene
        gin64_ResetTriCounter();
        SC_Scene_Title_Render();


        SC_Interface_Draw();


        //gin64_UpdateDebug();
        gin64_EndFrame(); //Perform any final funtions and gl_context_end

        rdpq_detach_show();
    }

    if (SC_GameState.playfieldMain.active) {

        gin64_BeginFrame(); //NGin64 Function - Clearing the frame buffer, the zbuffer, setting up the scene 
        gin64_LightingUpdate(); //NOTE ----- Set up lights and fog
        gin64_CamView(distance, cam_rotate); //NGin64 Function - Setting up the camera and matrix for the current scene

        //----- Note ----- reset rendered tri counter: 
        gin64_ResetTriCounter();

        render_beach_scene();



        SC_Interface_Draw();


        gin64_UpdateDebug();
        gin64_EndFrame(); //Perform any final funtions and gl_context_end

        rdpq_detach_show();

    }
}


extern void SC_Events_Update();



int mainTickRate = 30;
int prevTickRate = 20;
double previousTick = 0;
double currentTick = 0;
int checkFPS = 30;
int fpsCheckCounter = 0;


int main()
{

    gin64_DisplaySetup();

    gl_init();

    SC_Setup();

#if DEBUG_RDP
    rdpq_debug_start();
    rdpq_debug_log(true);
#endif

    
    gin64_InitTimers();
    controller_init();

    bool testOnce = true;

#if !DEBUG_RDP
    while (1)
#endif
    {
        gin64_SetDeltaTime();
        gin64_Time();
        

    //Note - Music Poll 1:
        //gin64_XMAudio_Song();
        gin64_WAVAudio_Song();

        gin64_Controller_Update();


        //if(SC_GameState.pauseScreen.active)

        if (SC_GameState.titleScreen.active){
            
            gin64_Events_Update();

            ngin64_UpdateCameraPosition();
            render();
            gin64_WAVAudio_Song();
            SC_Interface_Update();


            if (SC_GameState.playfieldMain.active) { //Note - if you switch to the playfield, run setup again...
                ngin64_UpdateCamFollow(&playfieldCursor.obj);
                beach_scene_init();
                //SC_Setup();
            }
        }

        else if (SC_GameState.playfieldMain.active) {

            gin64_Events_Update();

            ngin64_UpdateCameraPosition();

            int tempFPSCheck = gin64_GetFPS();

            if (tempFPSCheck <= checkFPS && fpsCheckCounter < 10) {

                fpsCheckCounter += 1;
            }

            else if (fpsCheckCounter >= 10) {
                checkFPS = tempFPSCheck;
                fpsCheckCounter = 0;
            }



            //Note - Music Poll 2:
                //gin64_XMAudio_Song();
            gin64_WAVAudio_Song();

            render();

            //Note - Music Poll 3:
               //gin64_XMAudio_Song();
            gin64_WAVAudio_Song();

            SC_Interface_Update();
        }

           if (DEBUG_RDP)
               rspq_wait();


        
    }
    

}
