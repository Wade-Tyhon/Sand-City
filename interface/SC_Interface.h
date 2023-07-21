#ifndef SC_INTERFACE_H
#define SC_INTERFACE_H

#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../ngin64/nGin64.h"



//----- Note ----- Controller Inputs
extern g64_Controller g64_Pad[4];


//----- Note ------ Assets
extern GLuint textures[16];

//----- Note ----- Interface Updates
extern void SC_Interface_Init();
extern void SC_Interface_Update();


//----- Note ----- Playfield Control References


//----- Note ----- Menu Control Updates


//----- Note ----- Playfield Control Updates
extern void SC_Playfield_Control_Init();
extern void SC_Playfield_Control_Update();
extern void SC_Playfield_Control_Draw();




#endif