#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../nGin64.h"





extern long long timer_ticks();


float lerp(float val_1, float val_2, float time)
{
    return (1 - time) * val_1 + time * val_2;
}


float lerpInt(int val_1, int val_2, float time)
{

    int newInt = (1 - time) * val_1 + time * val_2;

    if (newInt == val_1) {
        if (val_2 < val_1) 
            newInt--;
        
        else if (val_2 > val_1)
            newInt++;
    }

    return newInt;

}

double deltatime = 0.0;
double elapsedtime = 0.0;
double prev_frame = 0.0f;
double this_frame = 0.0f;
double overflow = 0.0f;
bool init_timer = false;

int g64_TriCounter = 0;

void gin64_InitTimers() {

    timer_init();
}




/*--------------------------------------------------------------------------*/
/*------------------------------ Playback Rate -----------------------------*/
/*--------------------------------------------------------------------------*/
double FPS_10 = 0; // ~ 0.1000ms
double FPS_15 = 0; // ~ 0.0666ms
double FPS_20 = 0; // ~ 0.0495ms
double FPS_30 = 0.0; // ~ 0.0333ms
double FPS_40 = 0; // ~ 0.025ms
double FPS_60 = 0.0; // ~ 0.0167ms


double playbackElapsedTime = 0.0;
int previousElapsedTime = 0.0;

int playbackElapsedFrames = 0;
int previousElapsedPeriod = 0;

int gin64_PlaybackTickUpdate() {



    if (playbackElapsedTime < 1.0) {

        playbackElapsedTime += deltatime;
        playbackElapsedFrames += 1;

    }

    else {
        previousElapsedPeriod = playbackElapsedFrames;
        playbackElapsedFrames = 0;
        playbackElapsedTime = (playbackElapsedTime + deltatime) - 1;
    }


    //if(playbackElapsedTime - previousElapsedTime >= 0.0332)
    FPS_10 += deltatime * 10; //Approximate an animation or physics tick for 15 fps
    FPS_15 += deltatime * 15; //Approximate an animation or physics tick for 15 fps
    FPS_20 += deltatime * 20; //Approximate an animation or physics tick for 20 fps
    FPS_30 += deltatime * 30; //Approximate an animation or physics tick for 30 fps
    FPS_40 += deltatime * 40; //Approximate an animation or physics tick for 40 fps
    FPS_60 += deltatime * 60; //Approximate an animation or physics tick for 60 fps

    //previousElapsedTime = playbackElapsedTime;



#ifdef DEBUG_NGIN64_SYSTEMFUNC    
    fprintf(stderr, "\n playbackElapsedTime: %.6f  |  playbackElapsedFrames: %i  |  previousElapsedPeriod: %i\n", playbackElapsedTime, playbackElapsedFrames, previousElapsedPeriod);
    fprintf(stderr, "\n 60 FPS: %i  |  FPS_40: %i  |  FPS_30: %i \n", (int)FPS_60, (int)FPS_40, (int)FPS_30);

    // fprintf(stderr, "Previous Frame: %.2f  |  Broken Frame: %.2f \n", prev_frame, overflow);
#endif

    //FPS_15 = 

    return (int)FPS_30;
}

int gin64_GetPlaybackTick(int playbackRate) {

    switch (playbackRate) {
    case 10:
        return FPS_10;
    case 15:
        return FPS_15;
    case 20:
        return FPS_20;
    case 30:
        return FPS_30;
    case 40:
        return FPS_40;
    case 60:
        return FPS_60;
    default: //Default to 30 fps if 
        return FPS_30;
    }

}



void gin64_SetDeltaTime() {
        
/*gin64_SetDeltaTime -  Calculates deltatime using clock ticks. This is used primarily for smooth physics lerps
*                       The ticks will reset approximately every 91 seconds. 
                        The line "if (this_frame > prev_frame)" is used to catch this overflow.
                            
                        The "overflow" variable is used to temporarily store this and then is re-set once
                        "this_frame" has again surpassed "prev_frame".

                        During this brief period, deltatime retains it's previous value.
*/

    this_frame = TICKS_READ();
    
    if (this_frame > prev_frame) {
        deltatime = TICKS_DISTANCE(prev_frame, this_frame) / (float)TICKS_PER_SECOND;
        prev_frame = TICKS_READ();
        overflow = 0.0f;
    }
    else if(overflow == 0.0f){
        overflow = this_frame;
        prev_frame = this_frame;
    }
    


#ifdef DEBUG_NGIN64_SYSTEMFUNC    
    fprintf(stderr, "Deltatime: %.6f  |  Ticks: %.2f  |  Timer: %.2f\n", deltatime, this_frame, (float)TICKS_PER_SECOND);
    fprintf(stderr, "Previous Frame: %.2f  |  Broken Frame: %.2f \n", prev_frame, overflow);
#endif


    gin64_PlaybackTickUpdate();
}

float gin64_GetDeltaTime() {

    return deltatime;
}





/*--------------------------------------------------------------------------*/
/*-----------------------------FPS and DeltaTime----------------------------*/
/*--------------------------------------------------------------------------*/

/*
s32 cpuCount = 0;
u32 microsec = 0;
int sec = 0;
float secf = 0;
int FPS_6 = 0;
int FPS_12 = 0;
int FPS_24 = 0;
int FPS_20 = 0;
int FPS_30 = 0;
int FPS_40 = 0;
int FPS_60 = 0;

int lastSec = 0;
int min = 0;
int frames = 0;
int lastFPS = 0;

f32	PreviousTime;		// The time in previous frame time 
f32	DeltaTime;		// The time passed since last frame time 
float inverseDeltaTime;
*/

float gFPS;

void g64_fps() {
    //NOTE: FPS calculation for libdragon swiped from Fazana

    static unsigned int curFrameTimeIndex = 0;
    static unsigned int frameTimes[30];
    unsigned int newTime = timer_ticks();
    unsigned int  oldTime = frameTimes[curFrameTimeIndex];
    frameTimes[curFrameTimeIndex] = newTime;

    curFrameTimeIndex++;
    if (curFrameTimeIndex >= 30) {
        curFrameTimeIndex = 0;
    }
    gFPS = (30 * 1000000.0f) / TIMER_MICROS(newTime - oldTime);
}

float g64_GetFPS() {

    return gFPS;
}



rdpq_font_t* debugFont;

char debugStringA[16];
char debugStringB[16];

void g64_InitDebug() {

    debug_init_isviewer();
    debug_init_usblog();

    dfs_init(DFS_DEFAULT_LOCATION);
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    rdpq_init();
    rdpq_debug_start();

    debugFont = rdpq_font_load("rom:/Pacifico.font64");
}

extern surface_t* disp;

void gin64_UpdateTriCounter(int newTri) {

    g64_TriCounter += newTri;
}

void gin64_ResetTriCounter() {

    g64_TriCounter = 0;
}

void g64_UpdateDebug() {

    rdpq_font_begin(RGBA32(58, 138, 127, 255));
    rdpq_font_position(20, 50);

    sprintf(debugStringA, "%i", (int)gFPS);
    

    rdpq_font_print(debugFont, debugStringA);


    rdpq_font_position(40, 50);
    sprintf(debugStringB, "%i", g64_TriCounter);
    rdpq_font_print(debugFont, debugStringB);


    rdpq_font_end();

}


/*
void g64_FrameCount()
{
    frames += 1;
}

void g64_FPSCalc()
{
    lastFPS = frames;
    frames = 0;
}

int g64_GetFPS()
{
    return lastFPS;
}
*/