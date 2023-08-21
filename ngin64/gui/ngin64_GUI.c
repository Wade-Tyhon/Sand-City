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
rdpq_font_t* pacificoFont;


const int defaultSpritesTotal = 4;
sprite_t* defaultSprites[4];


sprite_t* bkg;
surface_t bkgsurf;


rdpq_tile_t* defaultTiles[4];
static const char* defaultSprites_path[4] = {
    "rom:/circle0.sprite",
    "rom:/diamond0.sprite",
    "rom:/pentagon0.sprite",
    "rom:/triangle0.sprite",
};


extern playerState player;



rdpq_paragraph_t* partext = NULL;


void gin64_GUI_Init() {


    bkg = sprite_load("rom:/rgba/SandCityLogo.sprite");
    bkgsurf = sprite_get_pixels(bkg);

    //rdpq_font_t* fnt1 = rdpq_font_load("rom:/Pacifico.font64");
    //defaultFont = rdpq_font_load("rom:/BRLNSDB.font64");


    defaultFont = rdpq_font_load("rom:/BRLNSDB.font64");
    pacificoFont = rdpq_font_load("rom:/Pacifico.font64");


    rdpq_text_register_font(1, defaultFont);
    rdpq_text_register_font(2, pacificoFont);

    for (uint32_t i = 0; i < defaultSpritesTotal; i++)
    {
        defaultSprites[i] = sprite_load(defaultSprites_path[i]);
    }
    surface_t tex = surface_alloc(FMT_CI4, 32, 32);


    ////rdpq_tex_upload(TILE0, &tex, NULL);




    partext = NULL;
}

void gin64_GUIElement_Init(g64_GUI_Text* dynamicText) {


}

char tempText[16];
void gin64_GUI_Element_Draw(g64_GUI_Text* dynamicText) {

}

/*
typedef struct {
    char fontName[16];
    Coords2 pos;
    RGB color;
    char write[16];
}g64_GUI_Text;

*/


void gin64_GUI_Text_Draw(g64_GUI_Text* dynamicText) {

    int len = strlen(dynamicText->write);
    int sizes[7] = { 4, 8, 16, 32, 64, 128, len };
    int nchar = sizes[0];

    rdpq_font_style(defaultFont, 0, &(rdpq_fontstyle_t){
        .color = RGBA32(dynamicText->color.r, dynamicText->color.g, dynamicText->color.b, 255),
    });


    rdpq_text_print(&(rdpq_textparms_t) {
        // .line_spacing = -3,
            .align = ALIGN_LEFT,
            .valign = VALIGN_CENTER,
            .width = 100,
            .height = 0,
            .wrap = WRAP_WORD,
    }, 1, dynamicText->pos.x, dynamicText->pos.y, dynamicText->write);

   // rdpq_paragraph_render(partext, 60, 60);
}




void gin64_GUI_Paragraph_Draw(char* tempParagraph) {

    //{200, 160}, //.size
    /*
    const char* gameInstructions =
        "Two households, both alike in dignity,\n"
        "In fair Verona, where we lay our scene,\n"
        "From ancient grudge break to new mutiny,\n"
        "Where civil blood makes civil hands unclean.\n"
        "From forth the fatal loins of these two foes\n"
        "A pair of star-cross'd lovers take their life;\n";*/

    int len = strlen(tempParagraph);
    int sizes[7] = { 4, 8, 16, 32, 64, 128, len };
    rdpq_paragraph_t* partext = NULL;
    int box_width = 190;
    int box_height = 130;

    int drawn_chars = 0;
    int total_chars = strlen(tempParagraph);
    int frame = 0;

    int nbytes = rdpq_text_print(&(rdpq_textparms_t) {
        // .line_spacing = -3,
        .align = ALIGN_LEFT,
            .valign = VALIGN_CENTER,
            .width = box_width,
            .height = box_height,
            .wrap = WRAP_WORD,
    }, 1, (320 - box_width) / 2, (240 - box_height) / 2, tempParagraph);
    // rdpq_paragraph_render(partext, (320-box_width)/2, (240-box_height)/2);
    //uint32_t t1 = get_ticks();
    //enable_interrupts();
    //debugf("rdpq_text_print: %d us (%dx%d) - %d bytes\n", TIMER_MICROS(t1 - t0), box_width, box_height, nbytes);


}

void gin64_GUI_Window_Draw(g64_GUI_Window* tempWindow) {

    if (tempWindow->reveal == true) {
        // animate opening window

    }

    rdpq_set_prim_color(RGBA32(tempWindow->color.r, tempWindow->color.g, tempWindow->color.b, tempWindow->color.a));
    rdpq_set_mode_standard();
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_fill_rectangle(tempWindow->pos.x, tempWindow->pos.y, tempWindow->pos.x + tempWindow->size.x, tempWindow->pos.y + tempWindow->size.y);
}


void gin64_GUI_Screen_Fade(RGBA fadeColor) {


    /*
    rdpq_set_prim_color(RGBA32(tempWindow->color.r, tempWindow->color.g, tempWindow->color.b, tempWindow->color.a));
    rdpq_set_mode_standard();
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_fill_rectangle(tempWindow->pos.x, tempWindow->pos.y, tempWindow->pos.x + tempWindow->size.x, tempWindow->pos.y + tempWindow->size.y);
    */
}


void gin64_GUI_Window_Draw_OLD(g64_GUI_Window* tempWindow) {

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


    if (runOnce == false) {
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


void gin64_GUI_BlitImage_Draw() {



    //rdpq_debug_log_msg("sprites");
    rdpq_set_mode_standard();
    rdpq_mode_filter(FILTER_BILINEAR);
    rdpq_mode_alphacompare(1);

    /*
    rdpq_sprite_blit(&bkgsurf, 50, 10, &(rdpq_blitparms_t){
        .scale_x = 1, .scale_y = 1,
    });
    */
    rdpq_set_mode_copy(true);
   rdpq_tex_blit(&bkgsurf, 80, 15, NULL);
}


void gin64_GUI_Sprite_Draw(g64_GUI_Sprite* tempSprite) {

   // rdpq_debug_log_msg("sprites");
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


void gin64_GUI_Menu_Draw(g64_Menu_Collections* menuCollection) {

    Coords2 tempPos;

    char buttonName[16];

    tempPos.x = menuCollection->pos.x + menuCollection->padding.x;
    tempPos.y = menuCollection->pos.y + menuCollection->padding.y;
    
    for (int i = 0; i < 10; i++) {

       // fprintf(stderr, "\n > RUN gin64_GUI_Menu_Draw()\n");
        if (menuCollection->item[i] != NULL) {

            if (i == menuCollection->selectedItem) {
                rdpq_font_style(defaultFont, 0, &(rdpq_fontstyle_t){
                    .color = RGBA32(menuCollection->selectColor.r, menuCollection->selectColor.g, menuCollection->selectColor.b, 255),
                });
            }

            else{
                rdpq_font_style(defaultFont, 0, &(rdpq_fontstyle_t){
                    .color = RGBA32(menuCollection->baseColor.r, menuCollection->baseColor.g, menuCollection->baseColor.b, 255),
                });
            }
            rdpq_text_print(&(rdpq_textparms_t) {
                // .line_spacing = -3,
                    .align = ALIGN_LEFT,
                    .valign = VALIGN_CENTER,
                    .width = 100,
                    .height = 20,
                    .wrap = WRAP_WORD,
            }, 1, tempPos.x, tempPos.y, menuCollection->item[i]->name);
        }

        tempPos.y += 10 + menuCollection->padding.y;

    }
    
};

