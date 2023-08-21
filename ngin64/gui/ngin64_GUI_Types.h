#ifndef NGIN64_GUI_TYPES_H
#define NGIN64_GUI_TYPES_H


#include "../events/ngin64_EventTypes.h"


#include "../nGin64.h"

//----- Note ----- GUI Structs

typedef struct {
	bool active;
	char name[16];
	void (*handlerFunc)(char* keyWord);
	//g64_Event* menuEvent; //holds arguments, handler and 
}g64_Menu_Item;

typedef struct {
	Coords2 pos;
	g64_Menu_Item* item[10];
	u8 selectedItem;
	Coords2 padding;
	RGB baseColor;
	RGB selectColor;
	
}g64_Menu_Collections;


#define gin64_ForEachItem(g64_Menu_Item, g64_Menu_Collections) \
    for(int keep = 1, count = 0, size = sizeof(g64_Menu_Collections) / sizeof(g64_Menu_Collections[0]); \
    keep && count != size; \
    keep = !keep, count++) \
    for(g64_Menu_Item = g64_Menu_Collections[count]; keep; keep = !keep)

/*
typedef struct {
	Coords2 pos;
	g64_Menu_Item* items[10];
	Coords2 pos;
}g64_Menu_Collections;
*/




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
	bool active;
	Coords2 pos;
	Coords2 size;
	RGBA color;
	//-----------
	bool reveal;
	Coords2 startPos;
	Coords2 startSize;
	u8 animateSpeed;

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

void gin64_GUI_Screen_Fade(RGBA fadeColor);

extern void gin64_GUI_Element_Draw(g64_GUI_Text* dynamicText);
extern void gin64_GUI_Text_Draw(g64_GUI_Text* dynamicText);
extern void gin64_GUI_Paragraph_Draw(char* tempParagraph);
extern void gin64_GUI_Sprite_Draw(g64_GUI_Sprite* tempSprite);
extern void gin64_GUI_BlitImage_Draw();
extern void gin64_GUI_Window_Draw(g64_GUI_Window* tempWindow);
extern void gin64_GUI_TexWindow_Draw(g64_GUI_TexWindow* tempWindow);

extern void gin64_GUI_Menu_Draw(g64_Menu_Collections* menuCollection);

#endif