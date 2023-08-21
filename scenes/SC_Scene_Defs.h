#ifndef SC_SCENE_DEFS_H
#define SC_SCENE_DEFS_H


//----- Note ------ Gameplay Scene

//----- Playfield functions -----
extern void s_playfield_init(); //initiate the scene playfield to be its default state
extern void s_playfield_check();
extern GLuint playfield;

//----- Draw / render functions -----
extern void SC_Prefabs_Init();
extern void draw_beach_playfield();
extern void draw_beach_chair();
extern void draw_beach_umbrella();
extern void draw_beach();
extern void draw_waves();
extern void draw_castle_watchtower();

extern void SC_Crab_DL_LOD0();

extern void SC_Prefabs_DrawCastles();


//----- Note ------ Function references for the title screen
extern void SC_Scene_Title_Init();
extern void SC_Scene_Title_Render();


extern void SC_CrabPrefabs_Init();
extern g64_NPCObjectPrefab SC_KingCrab_PF;



//----- Note ------ Title Screen

//static const gl_XP64_Vert vert_TitleScreenBeach[]

extern void SC_TitleBeach_Draw();

extern void SC_TitleWaves_Draw();


#endif