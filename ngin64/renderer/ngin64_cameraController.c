#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../nGin64.h"





float tempCameraOrbit;
float tempAudioOrbit = 270.0f;
Vector3 tempCameraOffset;
float userInput_X = 0.1f;
float userInput_Y = 0.1f;
float cameraSensitivity = 3.0f;
float adjustCamRate = 1.0f;


void gin64_CamInit() {



}


void ngin64_UpdateCamFollow(GameObject* lookObject) {

    mainCamera.camFollow = lookObject;
    tempCameraOrbit = 0;


}

void gin64_CamView(float cam_dist, float cam_rot) {




    /*  glLoadIdentity: The current matrix is set to the identity matrix. The transformation commands
                        multiply the current matrix by the specified matrix and then set the result to
                        be the current matrix.
    */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    /* gluLookAt:       Where the camera is placed, where it is aimed, and which way is up.
                        The arguments used here place the camera at (0, 0, 5), aim the camera lens
                        towards (0, 0, 0), and specify the up-vector as (0, 1, 0). The up-vector
                        defines a unique orientation for the camera.
    */

    float adjustScale = 1.0f;



    if (SC_GameState.titleScreen.active)
    {
        gluLookAt(
            (mainCamera.obj.pos.x + .01f) * adjustScale, (mainCamera.obj.pos.y + .01f) * adjustScale, (mainCamera.obj.pos.z + .01f) * adjustScale,
            mainCamera.camFollow->pos.x, mainCamera.camFollow->pos.y, mainCamera.camFollow->pos.z + 2.0f,
            0, 0, 1);
    }


    else if (SC_GameState.playfieldMain.active)
    {
        gluLookAt(
            (mainCamera.obj.pos.x + .01f) * adjustScale, (mainCamera.obj.pos.y + .01f) * adjustScale, (mainCamera.obj.pos.z + .01f) * adjustScale,
            mainCamera.obj.pos.x, mainCamera.obj.pos.y + 16.0f, -5.0f,
            //mainCamera.camFollow->pos.x, mainCamera.camFollow->pos.y, mainCamera.camFollow->pos.z + 2.0f,
            0, 0, 1);
    }




}



Vector3 cameraPosition = { 0.0f, -50.0f,  50.0f };
Vector3 camUpdatedPosition = { 0.0f, -20.0f,  100.0f };
//Vector3 camLook = { 0.0f, 0.0f, 0.0f };
Vector3 cameraOffset = { 0.0f, -50.0f,  50.0f };
float cameraOrbit = 0.0f; //Rotation around player from a set distance
//float audioOrbit = 0.0f; //Rirection of right audio channel
Vector3 playerPos = { 0.0f, 0.0f, 0.0f };

u8 camCollidedWithObject = 0;
u8 camIsAgainstWall;

float distance = -750.0f;
float adjDistance = -750.0f;
//float nearPosition = 200;
float nearPosition = 125;

float lookZMin = 100; //for looking down
float lookZMax = 150; //for looking up
float lookZ = 85; //for looking up

/*--------------------------------------------------------------------------*/
/*-------------------------------Camera Setup-------------------------------*/
/*--------------------------------------------------------------------------*/

u8 wideScreen = 0; //set to widescreen by default

Vector3 MenuCamera = { 0,0,0 };
Vector3 MenuCameraLookPoint = { 0,10,0 };

//#define cameraSmoothSpeed 4 //value to lerp camera position

bool cameraStatic = false;

int cameraSmoothSpeed = 4;
void ngin64_CameraControl_C() {

    struct controller_data pressed = get_keys_pressed();
    //struct controller_data down = get_keys_down();



     //NOTE: Get L and R C-button input for horizontal/orbital movement around player character			
    if (pressed.c[0].C_right)
        //userInput_X = lerp(userInput_X, 3.0f, 0.01f);		
        userInput_X = lerp(userInput_X, 5.0f * adjustCamRate, (cameraSensitivity)*gin64_GetDeltaTime());
    //NOTE: Only allow user to press one of the L or R buttons	
    else if (pressed.c[0].C_left)
        //userInput_X = lerp(userInput_X, -3.0f, 0.01f);
        userInput_X = lerp(userInput_X, -5.0f * adjustCamRate, (cameraSensitivity)*gin64_GetDeltaTime());
    //NOTE: When user depresses the C button, quickly lerp down camera movement
    else if (userInput_X >= 0.2f || userInput_X <= -0.2f)
        //userInput_X = lerp(userInput_X, 0.0f, 0.2f);	
        userInput_X = lerp(userInput_X, 0.0f, (cameraSensitivity * 4) * gin64_GetDeltaTime());
    //NOTE: Once userInput_Y movement speed is below |.2f|, set it to 0.0f to avoid drift
    else
        userInput_X = 0.0f;



    //NOTE: Apply userInput_X to tempCamera Orbit and keep it in the 0-360 degree range			
    tempCameraOrbit += userInput_X;
    if (tempCameraOrbit >= 360.0f)
        tempCameraOrbit -= 360.0f;
    else if (tempCameraOrbit < 0.0f)
        tempCameraOrbit += 360.0f;

    //NOTE: Testing quick process for         
    tempAudioOrbit += userInput_X;
    if (tempAudioOrbit >= 360.0f)
        tempAudioOrbit -= 360.0f;
    else if (tempAudioOrbit < 0.0f)
        tempAudioOrbit += 360.0f;



    //NOTE: Get U and D C button input for vertical/distance from player character		
    userInput_Y = 0.0f;

    //if (ContTriger[0].button & U_CBUTTONS)
    if (pressed.c[0].C_up)
        userInput_Y += ((cameraSensitivity * 150) * adjustCamRate) * gin64_GetDeltaTime();

    else if (pressed.c[0].C_down)
        userInput_Y -= ((cameraSensitivity * 150) * adjustCamRate) * gin64_GetDeltaTime();

    //NOTE: Adjust distance of camera from player
    if (userInput_Y > 0.1f && tempCameraOffset.y <= -250.0f)
        tempCameraOffset.y = lerp(tempCameraOffset.y, -250.0f, userInput_Y * 0.01f);

    else if (userInput_Y > 0.1f && tempCameraOffset.y > -250.0f)
        tempCameraOffset.y = -250.0f;


    if (userInput_Y < 0.0f && tempCameraOffset.y >= -900.0f)
        tempCameraOffset.y = lerp(tempCameraOffset.y, -900.0f, userInput_Y * -0.01f);

    else if (userInput_Y < 0.0f && tempCameraOffset.y < -900.0f)
        tempCameraOffset.y = -900.0f;




    //NOTE: Adjust camera vertical position
    if (userInput_Y < 0.1f && tempCameraOffset.z <= 300.0f)
        tempCameraOffset.z = lerp(tempCameraOffset.z, 300, userInput_Y * -0.01f);

    else if (userInput_Y < 0.1f && tempCameraOffset.z > 300.0f)
        tempCameraOffset.z = 300.0f;

    if (userInput_Y > 0.0f && tempCameraOffset.z >= 100.0f)
        tempCameraOffset.z = lerp(tempCameraOffset.z, 150.0f, userInput_Y * 0.01f);

    else if (userInput_Y > 0.0f && tempCameraOffset.z <= 150.0f)
        tempCameraOffset.z = 150.0f;

    //----- Note ----- for orthographic:
    //tempCameraOffset.z += 800.0f;
}

/*--------------------------------------------------------------------------*/
/*-------------------Calculate Camera Position and Orbit--------------------*/
/*--------------------------------------------------------------------------*/
u8 cameraInitalPosed = 0;


void ngin64_RotateAroundSelected() {


    userInput_X = 0.25f;
    userInput_X = lerp(userInput_X, 5.0f * adjustCamRate, (cameraSensitivity)*gin64_GetDeltaTime());



    //NOTE: Apply userInput_X to tempCamera Orbit and keep it in the 0-360 degree range			
    tempCameraOrbit += userInput_X;
    if (tempCameraOrbit >= 360.0f)
        tempCameraOrbit -= 360.0f;
    else if (tempCameraOrbit < 0.0f)
        tempCameraOrbit += 360.0f;

    /*
    //NOTE: Get U and D C button input for vertical/distance from player character		
    userInput_Y = 0.0f;

    //if (ContTriger[0].button & U_CBUTTONS)
    if (pressed.c[0].C_up)
        userInput_Y += ((cameraSensitivity * 150) * adjustCamRate) * gin64_GetDeltaTime();

    else if (pressed.c[0].C_down)
        userInput_Y -= ((cameraSensitivity * 150) * adjustCamRate) * gin64_GetDeltaTime();

    //NOTE: Adjust distance of camera from player
    if (userInput_Y > 0.1f && tempCameraOffset.y <= -250.0f)
        tempCameraOffset.y = lerp(tempCameraOffset.y, -250.0f, userInput_Y * 0.01f);

    else if (userInput_Y > 0.1f && tempCameraOffset.y > -250.0f)
        tempCameraOffset.y = -250.0f;


    if (userInput_Y < 0.0f && tempCameraOffset.y >= -900.0f)
        tempCameraOffset.y = lerp(tempCameraOffset.y, -900.0f, userInput_Y * -0.01f);

    else if (userInput_Y < 0.0f && tempCameraOffset.y < -900.0f)
        tempCameraOffset.y = -900.0f;
        */
}


void ngin64_UpdateCameraPosition()
{


    /*------------------------Calculate Rotating Camera-------------------------*/
    //GameObject* lookObject = mainCamera.camLook;


    /*-----NOTE----- Temporarily removing smoothing until the player avatar has been set up.*/
    float smoothLookX;
    float smoothLookY;
    float smoothLookZ;

    float jumpingLookZ;
    float cameraHeight = 21.1f;

    cameraSmoothSpeed = 10;


    if (SC_GameState.titleScreen.active)
    {
        smoothLookX = lerp(mainCamera.camLookPoint.x, mainCamera.camFollow->pos.x + 0.5f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.2f));
        smoothLookY = lerp(mainCamera.camLookPoint.y, ((mainCamera.camFollow->pos.y * 0.35f) -1.0f), gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.5f));
        smoothLookZ = lerp(mainCamera.camLookPoint.z, mainCamera.camFollow->pos.z + 16.0f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.15f));
        SetVector3(&mainCamera.camLookPoint, smoothLookX, smoothLookY, smoothLookZ); //Note: distance to offset from "camLook"
       tempCameraOffset.x = 4.75f;
       tempCameraOffset.y = 4.75f;
      //  tempCameraOffset.z = 10.0f;
        tempCameraOffset.z = 10.2f;
        cameraHeight = 10.2f;
    }


    else if (SC_GameState.playfieldMain.active)
    {
        smoothLookX = lerp(mainCamera.camLookPoint.x, mainCamera.camFollow->pos.x + 0.5f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.2f));
        smoothLookY = lerp(mainCamera.camLookPoint.y, ((mainCamera.camFollow->pos.y * 0.35f) - 5.0f), gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.5f));
        smoothLookZ = lerp(mainCamera.camLookPoint.z, mainCamera.camFollow->pos.z + 80.0f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.15f));
        SetVector3(&mainCamera.camLookPoint, smoothLookX, smoothLookY, smoothLookZ); //Note: distance to offset from "camLook"
        
       // tempCameraOffset.x = 4.75f;
        tempCameraOffset.x = 1.5f;
        tempCameraOffset.y = -4.0f;
        tempCameraOffset.z = 300.0f;
        cameraHeight = 21.1f;
    }


    
    //tempCameraOffset.z = 300.0f;



    //NOTE ----- put camera static check to run only when camera input has stopped

    /*END-------------------------Depth/Horizontal Distance------------------------*/
    cameraStatic = 0; // reset before calculating again


    cameraStatic = positionCompare(mainCamera.obj.pos, camUpdatedPosition, 0.01f); //vector 1, vector 2, comparison precision



    if (cameraStatic == false)
    {
#ifdef DEBUG_NGIN64_SYSTEMFUNC
        fprintf(stderr, "Updating Camera position!");
#endif



        if (SC_GameState.titleScreen.active){
         ngin64_RotateAroundSelected();
        }




        camUpdatedPosition = RotateCameraAround(vectorAdd_R(mainCamera.camLookPoint, tempCameraOffset), mainCamera.camLookPoint, tempCameraOrbit);
        //camUpdatedPosition = RotateCameraAround(mainCamera.obj.pos, mainCamera.camLookPoint, tempCameraOrbit);


        mainCamera.cameraOrbit = tempCameraOrbit;
        mainCamera.audioOrbit = tempAudioOrbit;
        mainCamera.cameraOffset = tempCameraOffset;

        //lerp the canera quickly into position to soften sudden changes and jitters
        if (cameraInitalPosed == 1)
        {


#ifdef DEBUG_NGIN64_CAMERA
            fprintf(stderr, "CamInput: %.6f CamStatic: %i TempOrbit: (%.4f) Position: (%.4f,%.4f,%.4f)]\n\n", userInput_X, cameraStatic, tempCameraOrbit, mainCamera.obj.pos.x, mainCamera.obj.pos.y, mainCamera.obj.pos.z);
            fprintf(stderr, "CameraStatic = %i  CamUpdatedPosition: (%.4f,%.4f,%.4f)]\n\n", cameraStatic, camUpdatedPosition.x, camUpdatedPosition.y, camUpdatedPosition.z);
            fprintf(stderr, "CamLookPoint: (%.4f,%.4f,%.4f)]\n\n", mainCamera.camLookPoint.x, mainCamera.camLookPoint.y, mainCamera.camLookPoint.z);


#endif


            cameraSmoothSpeed = 8;
            mainCamera.obj.pos.x = lerp(mainCamera.obj.pos.x, camUpdatedPosition.x, gin64_GetDeltaTime() * cameraSmoothSpeed);
            mainCamera.obj.pos.y = lerp(mainCamera.obj.pos.y, camUpdatedPosition.y, gin64_GetDeltaTime() * cameraSmoothSpeed);
            mainCamera.obj.pos.z = lerp(mainCamera.obj.pos.z, cameraHeight, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.5f));
        }
        else
        {
            mainCamera.obj.pos = mainCamera.obj.pos;

            cameraInitalPosed = 1;
        }

    }




}






























