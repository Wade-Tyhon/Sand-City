
#ifndef NGIN64_H
#define NGIN64_H


#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "structures/ngin64_DataTypes.h"
#include "structures/ngin64_ColTypes.h"
#include "structures/ngin64_ObjTypes.h"
#include "structures/ngin64_InputTypes.h"

#include "events/ngin64_EventTypes.h"

#include "gui/ngin64_GUI_Types.h"

#include "tools/ngin64_Tools.h"

//#include "renderer/ngin64_rendererDataTypes.h"
#include "renderer/ngin64_renderer.h"

#include "NGin64_UserStructs.h"


/*------------------------------NGin64_Debug_Options---------------------------------*/
/* ----- NOTE ----- In order to keep your UNFLoader output clean, enable only the function
                    sets that you want to debug. Comment out the ones that you do not need to debug*/

//#define DEBUG_NGIN64_SYSTEMFUNC

//#define DEBUG_NGIN64_INTERFACE

#define DEBUG_NGIN64_CAMERA

//#define DEBUG_NGIN64_INITFUNC

/*------------------------------NGin64_Control_Defaults---------------------------------*/

//extern g64_ControllerTypeB testType[4];
extern g64_Controller g64_Pad[4];

extern g64_GameplayInput gameInput;
//extern g64_Controller g64_Pad;

/*---------------------------Engine Settings and References------------------------------*/

extern CameraObject mainCamera;
extern ViewSettings viewSettings;

extern g64_GameTimer gin64_GetGameTime();
extern g64_GameTimer gin64_AddGameTimers(g64_GameTimer timeA, g64_GameTimer timeB);
extern g64_GameTimer gin64_CompareGameTimers(g64_GameTimer timeA, g64_GameTimer timeB);
extern g64_GameTimer gin64_SetGameTimer(u8 hours, u8 minutes, float seconds);

extern void gin64_Time();
extern void gin64_fps();
extern float gin64_GetFPS();

extern int g64_TriCounter;
extern void gin64_ResetTriCounter();
extern void gin64_UpdateTriCounter(int newTri);


/*---------------------------GUI Element References------------------------------*/

extern void gin64_GUI_Button_Init();


//----- Note -----  For animations and physics checks, get a frame rate tick for various playback rates
//                  15, 20, 30, 40, 60 are the standard rates
              
int gin64_GetPlaybackTick(int playbackRate); 

/*------------------------------ Game Project Custom User Structures ---------------------------------*/

extern playfieldState S_PlayfieldState_Current[16][7];
extern CursorObject playfieldCursor;

//extern void clearFrame(float cam_dist, float cam_rot);
//extern void camView(float cam_dist, float cam_rot);

#endif