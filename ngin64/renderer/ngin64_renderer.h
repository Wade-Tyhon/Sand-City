#ifndef NGIN64_RENDERER_H
#define NGIN64_RENDERER_H

extern surface_t zbuffer;

extern void gin64_ProjSetup(); //Visual settings, only run when changes need to be made
extern void gin64_BeginFrame();
extern void gin64_EndFrame();

extern void gin64_CamView(float cam_dist, float cam_rot);
extern void gin64_CamInit();
extern void ngin64_CameraControl_C();
extern void ngin64_UpdateCameraPosition();

extern Vector3 GetCameraPosition();
extern u8 wideScreen;

extern void gin64_LightingUpdate();


#endif