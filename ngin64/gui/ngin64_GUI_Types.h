#ifndef NGIN64_GUI_TYPES_H
#define NGIN64_GUI_TYPES_H

#include "../nGin64.h"

//----- Note ----- GUI Structs
typedef struct {
	char fontName[16];	
	Coords2 pos;
	RGB color;
	char write[16];
}g64_GUI_Text;

typedef struct {
	sprite_t* sprite;
	int spriteID;
	Coords2 coords;	
	Vector2 scl;
	RGB color;
	bool alpha;
	u8 transparency;
}g64_GUI_Sprite;

typedef struct {
	Coords2 pos;
	g64_GUI_Sprite icon;
	g64_GUI_Text text;
}g64_GUI_Element;

typedef struct {

	Coords2 pos;
	Coords2 size;
	RGBA color;

}g64_GUI_Window;

typedef struct {

	sprite_t* sprite;
	int spriteID;
	Coords2 pos;
	Coords2 size;
	RGBA color;

}g64_GUI_TexWindow;


//texture_path[1]


//----- Note ----- GUI Function References 
extern void gin64_GUI_Init();

extern void gin64_GUIElement_Init(g64_GUI_Text* dynamicText);

extern void gin64_GUI_Element_Draw(g64_GUI_Text* dynamicText);
extern void gin64_GUI_Text_Draw(g64_GUI_Text* dynamicText);
extern void gin64_GUI_Sprite_Draw(g64_GUI_Sprite* tempSprite);
extern void gin64_GUI_Window_Draw(g64_GUI_Window* tempWindow);
extern void gin64_GUI_TexWindow_Draw(g64_GUI_TexWindow* tempWindow);

#endif