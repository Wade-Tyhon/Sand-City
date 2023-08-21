#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>
#include "nGin64.h"



/*
typedef struct {

    InputVector3 movement; //binding, vector3, name
    InputVector2 camera; //binding, vector2, name
    InputButton jump;
    InputButton attack;
    InputButton spellCast;
    InputButton lockon;
    InputButton pause; //Open pause menu
    InputVector2 menuH; //Nav menu horizontal movement
    InputVector2 menuV; //Nav menu vertical movement

}Gin64_GameplayInput;*/


g64_GameplayInput gameInput;
g64_MenuInput menuInput;


g64_GameState SC_GameState;

g64_GameFlags SC_GameFlags = {
    false,
    false,
    false,
    false,
    false
};




/*------------------------------NGin64_Camera_Defaults---------------------------------*/


ViewSettings viewSettings =
{
    {0.70f,0.85f,1.0f,1.0f},      //viewSettings.backgroundColor
    {0.70f,0.85f,1.0f,1.0f},      //viewSettings.fogColor
    40,                        //viewSettings.fogNear
    125,                       //viewSettings.fogFar
    2,                         //viewSettings.nearPlane
    500                       //viewSettings.farPlane
};

CameraObject mainCamera =
{
    {{0,-75,50}, {0,0,0}, {1,1,1}},//mainCamera.obj ( {pos}, {rot}, {scl})
    //{{0,-35,20}, {0,0,0}, {1,1,1}},//mainCamera.obj ( {pos}, {rot}, {scl})
    NULL, //mainCamera.camLook
    {0,0,0}, //mainCamera.camLookPoint
    {0,-6,5}, //mainCamera.cameraOffset
    //{0,-3,0}, //mainCamera.cameraOffset
    {0,0,0}, //mainCamera.camLookPoint
    0.0f, //mainCamera.cameraOrbit
    0.0f, //mainCamera.audioOrbit
    -5.0f, //mainCamera.distance
    //-2.0f, //mainCamera.distance
    0.0f, //mainCamera.adjDistance
    0.0f, //mainCamera.nearPosition
    0 //mainCamera.againstWall
};

/*
typedef struct {

    u8 mat_sand;
    u8 mat_shells;

}playerState;
*/

playerState player =
{
    20, // mat_sand
    20 // mat_shells
};

/*
typedef struct {

    int propertyTax;
    int salesTax;
    int residents;
    u8 mood;

}cityState;
*/


cityState SC_CityStats =
{
    0,
    0, //propertyTax
    0, //salesTax
    0, //residents
    0, //mood
    0,


    0, //.expenses

    20, //mat_sand
    22 //mat_shells
};