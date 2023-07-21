#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../nGin64.h"

surface_t zbuffer;



/* ----- To Do Notes -----
*
*           - Begin integration of camera controls with ngin64_ControllerInput
*				- Set up camera controls to instead take input that is stored in the ngin64_ControllerInput
*               - This will allow for players to choose their button combination and allow me to normalize the input before sending it to camera controller
*               - Adjust all distances so that "float adjustScale = 0.03f;" will no longer be needed.
* 
*
*
*/



extern CursorObject playfieldCursor;

//static const GLfloat clear_frame_color[] = { 0.1f, 0.03f, 0.2f, 1.f };
//static const GLfloat environment_color2[] = { 0.1f, 0.03f, 0.2f, 0.5f };
/*------------------------------NGin64 Project Defaults---------------------------------*/
void gin64_ProjSetup() {

    zbuffer = surface_alloc(FMT_RGBA16, display_get_width(), display_get_height());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    //rdpq_mode_alphacompare(1);
    //gl_rendermode_init();

    float aspect_ratio = (float)display_get_width() / (float)display_get_height();
    //float near_plane = 1.0f;
    //float far_plane = 500.0f;

    float near_plane = viewSettings.nearPlane;
    float far_plane = viewSettings.farPlane;

    //----- Note ----- Orthographic Version
    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-near_plane * aspect_ratio, near_plane * aspect_ratio, -near_plane, near_plane, near_plane, far_plane);
    */

    //----- Note ----- Projection
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-near_plane * aspect_ratio, near_plane * aspect_ratio, -near_plane, near_plane, near_plane, far_plane);
    
}



surface_t* disp;


/*------------------------------NGin64 Frame Update Defaults---------------------------------*/
void gin64_BeginFrame() {

    float fps;

    surface_t* disp = display_get();
    rdpq_attach(disp, &zbuffer);



    g64_fps(); //calculate current frame rate
    fps = g64_GetFPS(); //get current frame rate

#ifdef DEBUG_NGIN64_CAMERA
    fprintf(stderr, " -FPS: %i   ", (int)fps);
#endif

    gl_context_begin();

   // Set up 
    glClearColor(viewSettings.backgroundColor.r, viewSettings.backgroundColor.g, viewSettings.backgroundColor.b, viewSettings.backgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

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


float tempCameraOrbit;
float tempAudioOrbit = 270.0f;
Vector3 tempCameraOffset;
float userInput_X = 0.1f;
float userInput_Y = 0.1f;
float cameraSensitivity = 3.0f;
float adjustCamRate = 1.0f;


void gin64_CamInit() {

    //-----TO DO NOTE -----
    //Set up camera movement script

    tempCameraOffset.y = -175.0f;

    //----- Note ----- Projection:
    tempCameraOffset.z = 250.0f;

    //----- Note ----- Ortho:
    //tempCameraOffset.z = 600.0f;


    mainCamera.cameraOffset = tempCameraOffset;



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
 
    float adjustScale = 0.03f;
    
    gluLookAt(
        (mainCamera.obj.pos.x + .01f) * adjustScale, (mainCamera.obj.pos.y+.01f)* adjustScale, (mainCamera.obj.pos.z+.01f)* adjustScale,
        0, 0, 0,
        0, 0, 1);
        
}



Vector3 cameraPosition = { 0.0f, -50.0f,  50.0f };
Vector3 camUpdatedPosition = { 0.0f, -20.0f,  100.0f };
Vector3 camLook = { 0.0f, 0.0f, 0.0f };
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
        userInput_X = lerp(userInput_X, 5.0f * adjustCamRate, (cameraSensitivity) * gin64_GetDeltaTime());
    //NOTE: Only allow user to press one of the L or R buttons	
    else if (pressed.c[0].C_left)
        //userInput_X = lerp(userInput_X, -3.0f, 0.01f);
        userInput_X = lerp(userInput_X, -5.0f * adjustCamRate, (cameraSensitivity) * gin64_GetDeltaTime());
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
void ngin64_UpdateCameraPosition()
{
    
    
    /*------------------------Calculate Rotating Camera-------------------------*/
    //GameObject* lookObject = mainCamera.camLook;


    /*-----NOTE----- Temporarily removing smoothing until the player avatar has been set up.*/
    float smoothLookX;
    float smoothLookY;
    float smoothLookZ;

    float jumpingLookZ;
    //  float testnumber;




    //* 
    //* 
  // ----- NOTE ----- Adjust the camera smoothing speed based on the player movement speed so that it is not possible to run out of view
    /*
    if (playerAvatar.rigidBody.speed >= 400)
        cameraSmoothSpeed = 10;

    if (playerAvatar.rigidBody.speed >= 300)
        cameraSmoothSpeed = 8;

    else if (playerAvatar.rigidBody.speed >= 250)
        cameraSmoothSpeed = 5;

    else if (playerAvatar.rigidBody.speed < 250)
        cameraSmoothSpeed = 4;
*/

    cameraSmoothSpeed = 20;
    //if (playerAvatar.state.movement != 5)
    //{
        /*
        if (playerAvatar.state.jumping >= 1) //jumping or falling
        {
            jumpingLookZ = lerp(playerAvatar.shadowPosition.z, playerAvatar.obj.pos.z + 5.0f, 0.35f);
            smoothLookX = lerp(mainCamera.camLookPoint.x, playfieldCursor.obj.pos.x + 0.5f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.9f));
            smoothLookY = lerp(mainCamera.camLookPoint.y, playfieldCursor.obj.pos.y + 0.5f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.9f));
            smoothLookZ = lerp(mainCamera.camLookPoint.z, jumpingLookZ, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.45f));
        }

        else //grounded
        {*/
            
       // }

    /*
        smoothLookX = lerp(mainCamera.camLookPoint.x, playfieldCursor.pos.x + 0.5f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.9f));
        smoothLookY = lerp(mainCamera.camLookPoint.y, playfieldCursor.pos.y + 0.5f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.9f));
        smoothLookZ = lerp(mainCamera.camLookPoint.z, playfieldCursor.pos.z + 30.0f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.75f));
        SetVector3(&mainCamera.camLookPoint, smoothLookX, smoothLookY, smoothLookZ); //Note: distance to offset from "camLook"
        */


        

        tempCameraOffset = mainCamera.cameraOffset;

        //ngin64_CameraControl_C();

        /*-------------------------Depth/Horizontal Distance------------------------*/
        if (userInput_Y >= 1.0f || userInput_Y <= -1.0f || cameraInitalPosed == 1)
        {
            if (camIsAgainstWall == 0)
            {
                if (distance >= 600)
                    nearPosition = 450;


                else if (distance <= 600 && distance >= 500)
                    nearPosition = 400;

                else if (distance < 500)

                    nearPosition = 50;

            }
            else
            {
                if (adjDistance >= 600)
                    nearPosition = 450;
                else if (adjDistance <= 600 && adjDistance >= 500)
                    nearPosition = 400;
                else if (adjDistance < 500)

                    nearPosition = 50;


            }
        }

        //NOTE ----- put camera static check to run only when camera input has stopped

        /*END-------------------------Depth/Horizontal Distance------------------------*/
        cameraStatic = 0; // reset before calculating again
        

        if (userInput_Y < 0.01f && userInput_Y > -0.01f && userInput_X < 0.01f && userInput_X > -0.01f) {
            cameraStatic = positionCompare(mainCamera.obj.pos, camUpdatedPosition, 0.01f); //vector 1, vector 2, comparison precision
            //Take a break! You've earned it. The camera is 
        }

        if (cameraStatic == false)
        {
            #ifdef DEBUG_NGIN64_SYSTEMFUNC
                   fprintf(stderr, "Updating Camera position!");
            #endif

            camUpdatedPosition = RotateCameraAround(vectorAdd_R(mainCamera.camLookPoint, tempCameraOffset), mainCamera.camLookPoint, tempCameraOrbit);

            mainCamera.cameraOrbit = tempCameraOrbit;
            mainCamera.audioOrbit = tempAudioOrbit;
            mainCamera.cameraOffset = tempCameraOffset;

            //lerp the canera quickly into position to soften sudden changes and jitters
            if (cameraInitalPosed == 1)
            {
                mainCamera.obj.pos.x = lerp(mainCamera.obj.pos.x, camUpdatedPosition.x, gin64_GetDeltaTime() * cameraSmoothSpeed);
                mainCamera.obj.pos.y = lerp(mainCamera.obj.pos.y, camUpdatedPosition.y, gin64_GetDeltaTime() * cameraSmoothSpeed);
                mainCamera.obj.pos.z = lerp(mainCamera.obj.pos.z, camUpdatedPosition.z, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.5f));
            }
            else
            {
                mainCamera.obj.pos = mainCamera.obj.pos;
                //mainCamera.obj.pos.x = 10.0f;
                //mainCamera.obj.pos.y = 10.0f;
                //mainCamera.obj.pos.z = 20.0f;
                cameraInitalPosed = 1;
            }

        }


#ifdef DEBUG_NGIN64_CAMERA
        fprintf(stderr, "CamInput: %.6f CamStatic: %i TempOrbit: (%.4f) Position: (%.4f,%.4f,%.4f)]\n\n", userInput_X, cameraStatic, tempCameraOrbit, mainCamera.obj.pos.x, mainCamera.obj.pos.y, mainCamera.obj.pos.z);
#endif
        // testnumber  = mainCamera.camLookPoint.x + playerAvatar.obj.pos.x+0.5f;
        // Debug_MiscVar[0].x = testnumber;

    //}
        /*
    else if (playerAvatar.state.movement == 5)
    {

        smoothLookX = lerp(mainCamera.camLookPoint.x, playerAvatar.obj.pos.x + 0.5f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.9f));
        smoothLookY = lerp(mainCamera.camLookPoint.y, playerAvatar.obj.pos.y + 0.5f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.9f));
        smoothLookZ = lerp(mainCamera.camLookPoint.z, playerAvatar.obj.pos.z + 5.0f, gin64_GetDeltaTime() * (cameraSmoothSpeed * 0.75f));


        // Debug_MiscVar[0].y = basePosition.y - centerPoint.y;
         //Debug_MiscVar[0].z = rotation;



        SetVector3(&mainCamera.camLookPoint, smoothLookX, smoothLookY, smoothLookZ); //Note: distance to offset from "camLook"

        mainCamera.obj.pos.x = -2185;
        mainCamera.obj.pos.y = -2907;
        mainCamera.obj.pos.z = 315;
    }
    */


}
