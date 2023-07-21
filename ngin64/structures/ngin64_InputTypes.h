#ifndef NGIN64_INPUTTYPES_H
#define NGIN64_INPUTTYPES_H

#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../nGin64.h"

typedef struct {

	bool A;
	bool B;
	bool Start;

	bool Z;
	bool L;
	bool R;

	bool C_Up;
	bool C_Down;
	bool C_Left;
	bool C_Right;

	bool D_Up;
	bool D_Down;
	bool D_Left;
	bool D_Right;
	// Assignment?

}g64_buttons;


typedef struct {

	float x;
	float y;

}g64_direction;


typedef struct {

	//float g64_direction[2];
	g64_direction Stick;
	g64_direction Dpad;
	g64_direction Cpad; //Optionally treat c buttons as directional pad
	//u8 Dpad;
	g64_buttons Press;
	g64_buttons Hold;

}g64_Controller;

/*
typedef struct {

	//float g64_direction[2];
	g64_direction Stick;
	g64_direction Dpad;
	g64_direction Cpad; //Optionally treat c buttons as directional pad
	//u8 Dpad;
	g64_buttons Press;
	g64_buttons Hold;

}g64_ControllerTypeB;
*/

//g64_ControllerTypeB testType;
//g64_Controller g64_Pad[4];

#endif