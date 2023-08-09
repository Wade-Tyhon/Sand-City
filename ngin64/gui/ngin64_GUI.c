#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "../nGin64.h"



//Font Options

/*Dynamic Text GUI Element
*	- Font Selection
*	- Font Color
*	- GUI Position
*	- Pointer to String
	
*/

//Static Text GUI Element

//Sprite GUI Element
//Vector GUI Element

//static const char* texture_path[19]
/**/


char tempFontName[32];
rdpq_font_t* tempFont;
rdpq_font_t* defaultFont;


const int defaultSpritesTotal = 4;
sprite_t* defaultSprites[4];

rdpq_tile_t* defaultTiles[4];
static const char* defaultSprites_path[4] = {
    "rom:/circle0.sprite",
    "rom:/diamond0.sprite",
    "rom:/pentagon0.sprite",
    "rom:/triangle0.sprite",
};



//rdpq_texture_rectangle

extern playerState player;
/*
char debugStringA[16];
char debugStringB[16];
char debugStringC[16];
char debugStringD[16];
char debugStringE[16];
*/
void gin64_GUI_Init() {

	defaultFont = rdpq_font_load("rom:/BRLNSDB.font64");

    for (uint32_t i = 0; i < defaultSpritesTotal; i++)
    {
        defaultSprites[i] = sprite_load(defaultSprites_path[i]);
    }
    surface_t tex = surface_alloc(FMT_CI4, 32, 32);
    //rdpq_tex_upload(TILE0, &tex, NULL);


}

void gin64_GUIElement_Init(g64_GUI_Text* dynamicText) {


}

char tempText[16];
void gin64_GUI_Element_Draw(g64_GUI_Text* dynamicText) {

	rdpq_font_begin(RGBA32(dynamicText->color.r, dynamicText->color.g, dynamicText->color.b, 255));	
	rdpq_font_position(dynamicText->pos.x, dynamicText->pos.y);
	rdpq_font_print(defaultFont, dynamicText->write);
	rdpq_font_end();

}

void gin64_GUI_Text_Draw(g64_GUI_Text* dynamicText) {

    rdpq_font_begin(RGBA32(dynamicText->color.r, dynamicText->color.g, dynamicText->color.b, 255));
    rdpq_font_position(dynamicText->pos.x, dynamicText->pos.y);
    rdpq_font_print(defaultFont, dynamicText->write);
    rdpq_font_end();
}

void gin64_GUI_Window_Draw(g64_GUI_Window* tempWindow) {

    rdpq_set_prim_color(RGBA32(tempWindow->color.r, tempWindow->color.g, tempWindow->color.b, tempWindow->color.a));
    rdpq_set_mode_standard();
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_fill_rectangle(tempWindow->pos.x, tempWindow->pos.y, tempWindow->pos.x + tempWindow->size.x, tempWindow->pos.y + tempWindow->size.y);
}


static sprite_t* tiles_sprite;
static rspq_block_t* tiles_block;

bool runOnce = false;

void gin64_GUI_TexWindow_Draw(g64_GUI_TexWindow* tempWindow) {

    
    if(runOnce == false){
        bool tlut = false;

        surface_t tiles_surf = sprite_get_pixels(defaultSprites[1]);

        rspq_block_begin();
        rdpq_set_prim_color(RGBA32(tempWindow->color.r, tempWindow->color.g, tempWindow->color.b, tempWindow->color.a));
        rdpq_set_mode_standard();
        //rdpq_set_mode_copy(false);
        rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);

        //rdpq_mode_combiner(RDPQ_COMBINER_TEX);
        rdpq_mode_combiner(RDPQ_COMBINER_TEX_FLAT);
        tex_format_t tiles_format = sprite_get_format(defaultSprites[1]);

        if (tiles_format == FMT_CI4 || tiles_format == FMT_CI8) {
            rdpq_mode_push();
            rdpq_mode_tlut(TLUT_RGBA16);
            rdpq_tex_upload_tlut(sprite_get_palette(defaultSprites[1]), 0, 16);
            tlut = true;
        }

        uint32_t tile_width = defaultSprites[1]->width;
        uint32_t tile_height = defaultSprites[1]->height;

        rdpq_tex_upload_sub(TILE0, &tiles_surf, NULL, 0, 0, 32, 32);
        rdpq_texture_rectangle_scaled(TILE0, tempWindow->pos.x, tempWindow->pos.y, tempWindow->pos.x + tempWindow->size.x, tempWindow->pos.y + tempWindow->size.y, 0, 0, 32, 32);

        if (tlut) rdpq_mode_pop();
        tiles_block = rspq_block_end();

        runOnce = true;

    }

    rspq_block_run(tiles_block);

    
}

void gin64_GUI_Sprite_Draw(g64_GUI_Sprite* tempSprite) {

    rdpq_debug_log_msg("sprites");
    rdpq_set_mode_standard();
    rdpq_mode_filter(FILTER_BILINEAR);
    rdpq_mode_alphacompare(1);                
    
    rdpq_sprite_blit(tempSprite->sprite, tempSprite->coords.x, tempSprite->coords.y, &(rdpq_blitparms_t){
        .scale_x = tempSprite->scl.x, .scale_y = tempSprite->scl.y,
    });

    /*
    rdpq_sprite_blit(guiSprites[1], 30, 30, &(rdpq_blitparms_t){
        .scale_x = .5, .scale_y = .5,
    });
    */
}