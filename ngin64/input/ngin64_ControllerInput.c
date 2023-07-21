#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../nGin64.h"


/* ----- To Do Notes for Sand City -----
*
*           - Continue setting up custom struct for holding ALL controller data 
*				- This can also be "assigned" to a function for each game with Gin64_GameplayInput 
*				- Begin a method for assigning these buttons and normalizing the input to have a consistent feel for all inputs 
*				- Aka: camera or cursor movement should take the same amount of time with the D-pad as with the analog stick 
* 
*			- Set up key bindings for 'g64_GameplayInput' in the function 'gin64_Controller_Init '
*           
* 
*/

g64_buttons test;

g64_Controller g64_Pad[4];


/*
typedef struct {

	InputVector2 cursor; //D Pad or Analog - selecting which tile to interact with
	InputVector2 camera; //C Buttons - rotate around the currently selected object and select a camera mode (c left and c right rotates, c up changes camera mode, c down zooms into inspect current tile
	InputButton confirm; //A button
	InputButton cancel; //B button

	InputButton speed; //R - toggles simulation speed
	InputButton pause; //START - Open pause menu
	InputButton menu1; //Z - toggles menu to select 
	InputVector2 menuH; //Nav menu horizontal movement
	InputVector2 menuV; //Nav menu vertical movement

}Gin64_GameplayInput;
*/


void gin64_Controller_Init() {


}

void gin64_Controller_Update() {

	controller_scan();
	struct controller_data hold = get_keys_pressed();
	struct controller_data press = get_keys_down();

	//g64_Controller g64_Pad_Last = g64_Pad;



	//----- Note ----- Analog stick 
	g64_Pad[0].Stick.x = hold.c[0].x;
	g64_Pad[0].Stick.y = hold.c[0].y;




	//----- Note ----- Directional Pad
	if(hold.c[0].up >= 1)
		g64_Pad[0].Dpad.y = hold.c[0].up;
	else if (hold.c[0].down >= 1)
		g64_Pad[0].Dpad.y = -hold.c[0].down;
	else
		g64_Pad[0].Dpad.y = 0;


	if (hold.c[0].right >= 1)
		g64_Pad[0].Dpad.x = hold.c[0].right;
	else if (hold.c[0].left >= 1)
		g64_Pad[0].Dpad.x = -hold.c[0].left;
	else
		g64_Pad[0].Dpad.x = 0;



	//----- Note -----	Alternatively use C Buttons as directional input (referred to as Cpad)
	//					This one needs extra checks to avoid inputting both a positive and negative directional input for x or y
	//					Next State = check the next state such as:					c[0].C_up,		 c[0].C_right, etc...
	//					Previous State = compare to the previous state such as		g64_Pad[0].Cpad.y,		g64_Pad[0].Cpad.x etc...
	
	
	
	//----- Note -----	Check next state. Ideally, only either up or down will be selected

	if (hold.c[0].C_up == 0 && hold.c[0].C_down == 0) // No +1 or -1 input... store 0
		g64_Pad[0].Cpad.y = 0;

		else if (hold.c[0].C_up >= 1 && hold.c[0].C_down == 0) // Receiving only +1 inputs
			g64_Pad[0].Cpad.y = hold.c[0].C_up;

		else if (hold.c[0].C_down >= 1 && hold.c[0].C_up == 0)
			g64_Pad[0].Cpad.y = -hold.c[0].C_down;


		//----- Note -----	If both buttons are held down, see if either button was held down in the previous frame. 
		//					If so, continue the previous button input and ignore the newest input 

		else if (hold.c[0].C_up >= 1 && hold.c[0].C_down >= 1) {// Receiving both +1 and -1 inputs

			if (g64_Pad[0].Cpad.y == 1) // Note - previous input was +1, but getting both +1 and -1 inputs now
				g64_Pad[0].Cpad.y = hold.c[0].C_up; // Note - keeps at +1, ignores the newest input'

			else if (g64_Pad[0].Cpad.y == -1) // Note - previous input was -1, but getting both +1 and -1 inputs now
				g64_Pad[0].Cpad.y = -hold.c[0].C_down; // Note - keeps at -1, ignores the newest input

			else // Note - there was no input the previous frame
				g64_Pad[0].Cpad.y = hold.c[0].C_up; // Note - prioritizes the positive movement
		}

	
	//----- Note -----	Check next state. Ideally, only either up or down will be selected

	if (hold.c[0].C_right == 0 && hold.c[0].C_left == 0) // No +1 or -1 input... store 0
		g64_Pad[0].Cpad.x = 0;

		else if (hold.c[0].C_right >= 1 && hold.c[0].C_left == 0) // Receiving only +1 inputs
			g64_Pad[0].Cpad.x = hold.c[0].C_right;

		else if (hold.c[0].C_left >= 1 && hold.c[0].C_right == 0)
			g64_Pad[0].Cpad.x = -hold.c[0].C_left;


		//----- Note -----	If both buttons are held down, see if either button was held down in the previous frame. 
		//					If so, continue the previous button input and ignore the newest input 

		else if (hold.c[0].C_right >= 1 && hold.c[0].C_left >= 1) {// Receiving both +1 and -1 inputs

			if (g64_Pad[0].Cpad.x == 1) // Note - previous input was +1, but getting both +1 and -1 inputs now
				g64_Pad[0].Cpad.x = hold.c[0].C_right; // Note - keeps at +1, ignores the newest input'

			else if (g64_Pad[0].Cpad.x == -1) // Note - previous input was -1, but getting both +1 and -1 inputs now
				g64_Pad[0].Cpad.x = -hold.c[0].C_left; // Note - keeps at -1, ignores the newest input

			else // Note - there was no input the previous frame
				g64_Pad[0].Cpad.x = hold.c[0].C_right; // Note - prioritizes the positive movement
		}





	//----- Note ----- Face buttons (tap)
	g64_Pad[0].Hold.A = hold.c[0].A;
	g64_Pad[0].Hold.B = hold.c[0].B;
	g64_Pad[0].Hold.Start = hold.c[0].start;

	//----- Note ----- Triggers (tap)
	g64_Pad[0].Hold.Z = hold.c[0].Z;
	g64_Pad[0].Hold.L = hold.c[0].L;
	g64_Pad[0].Hold.R = hold.c[0].R;

	//----- Note ----- C Buttons (tap)
	g64_Pad[0].Hold.C_Up = hold.c[0].C_up;
	g64_Pad[0].Hold.C_Down = hold.c[0].C_down;
	g64_Pad[0].Hold.C_Left = hold.c[0].C_left;
	g64_Pad[0].Hold.C_Right = hold.c[0].C_right;




	//----- Note ----- Face buttons (tap)
	g64_Pad[0].Press.A = press.c[0].A;
	g64_Pad[0].Press.B = press.c[0].B;
	g64_Pad[0].Press.Start = press.c[0].start;

	//----- Note ----- Triggers (tap)
	g64_Pad[0].Press.Z = press.c[0].Z;
	g64_Pad[0].Press.L = press.c[0].L;
	g64_Pad[0].Press.R = press.c[0].R;

	//----- Note ----- C Buttons (tap)
	g64_Pad[0].Press.C_Up = press.c[0].C_up;
	g64_Pad[0].Press.C_Down = press.c[0].C_down;
	g64_Pad[0].Press.C_Left = press.c[0].C_left;
	g64_Pad[0].Press.C_Right = press.c[0].C_right;

	//----- Note ----- C Buttons (tap)
	g64_Pad[0].Press.D_Up = press.c[0].up;
	g64_Pad[0].Press.D_Down = press.c[0].down;
	g64_Pad[0].Press.D_Left = press.c[0].left;
	g64_Pad[0].Press.D_Right = press.c[0].right;

	

#ifdef DEBUG_NGIN64_SYSTEMFUNC
	//fprintf(stderr, "\nTesting Input | A %i | B %i", g64_Pad[0].hold.A, g64_Pad[0].hold.B);
	fprintf(stderr, "\nTesting Button Input | A %i | B %i | Start %i", g64_Pad[0].Hold.A, g64_Pad[0].Hold.B, g64_Pad[0].Hold.Start);
	fprintf(stderr, "\nTesting Trigger Input | Z %i | L %i | R %i", g64_Pad[0].Hold.Z, g64_Pad[0].Hold.L, g64_Pad[0].Hold.R);
	fprintf(stderr, "\nTesting C Button Input | C Up %i | C Down %i | C Left %i | C Right %i | \n", g64_Pad[0].Hold.C_Up, g64_Pad[0].Hold.C_Down, g64_Pad[0].Hold.C_Left, g64_Pad[0].Hold.C_Right );
	fprintf(stderr, "\nTesting D Pad Input | X %.2f | Y %.2f", g64_Pad[0].Dpad.x, g64_Pad[0].Dpad.y);
	fprintf(stderr, "\nTesting C Pad Input | X %.2f | Y %.2f", g64_Pad[0].Cpad.x, g64_Pad[0].Cpad.y);
	fprintf(stderr, "\nTesting Analog Input | X %.2f | Y %.2f \n", g64_Pad[0].Stick.x, g64_Pad[0].Stick.y);
#endif

	//gin64_SetCursor();
	
	//Get input

	//gameInput.camera.x += .5f;

	//lerp(Gin64_GameplayInput.camera.x, 5.0f, (cameraSensitivity) * (float)gin64_GetDeltaTime());

}

void gin64_SetCursor()
{


}

void g64_ControllerDefaults() {



}