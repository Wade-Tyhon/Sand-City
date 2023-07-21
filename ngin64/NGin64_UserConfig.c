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
    {{0,-10,100}, {0,0,0}, {1,1,1}},//mainCamera.obj ( {pos}, {rot}, {scl})
    NULL, //mainCamera.camLook
    {0,0,400}, //mainCamera.camLookPoint
    {0,45,600}, //mainCamera.cameraOffset
    {0,0,0}, //mainCamera.camLookPoint
    0.0f, //mainCamera.cameraOrbit
    0.0f, //mainCamera.audioOrbit
    -5.0f, //mainCamera.distance
    0.0f, //mainCamera.adjDistance
    0.0f, //mainCamera.nearPosition
    0 //mainCamera.againstWall
};


