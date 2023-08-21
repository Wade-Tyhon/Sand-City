#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../ngin64/nGin64.h"
#include "SC_Interface.h"

g64_PlayfieldEvent StartGameMenuEvent;
g64_PlayfieldEvent InstructionsMenuEvent;
g64_GameTimer LoadDelay = { 0, 0, 4.0f };