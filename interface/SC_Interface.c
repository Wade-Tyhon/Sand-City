#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../ngin64/nGin64.h"

#include "SC_Interface.h"

//extern void g64_ControllerInput();
//Gin64_GameplayInput
/*
extern gl_XP64_Vert vert_SelectStructureUI[];
extern uint16_t poly_SelectStructureUI[];
extern uint16_t SCGet_poly_SelectStructureUI_Size();

extern gl_XP64_Vert vert_SelectGroundUI[];
extern uint16_t poly_SelectGroundUI_Beach[];
extern uint16_t SCGet_poly_SelectGroundUI_Beach_Size();
*/

void SC_Interface_Init() {
#ifdef DEBUG_NGIN64_INTERFACE
	//fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
	fprintf(stderr, "\n > RUN SC_Interface_Init!\n");
#endif


	SC_Playfield_Control_Init();

}

void SC_Interface_Update() {

#ifdef DEBUG_NGIN64_INTERFACE
	//fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
	fprintf(stderr, "\n > RUN SC_Interface_Update!\n");
#endif

	SC_Playfield_Control_Update();

}

void SC_Interface_Draw() {

	SC_Playfield_Control_Draw();
}