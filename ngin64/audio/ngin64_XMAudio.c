#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include "../nGin64.h"
#include "ngin64_XMAudio_Defs.h"

#define CHANNEL_SFX1    0
#define CHANNEL_SFX2    1
#define CHANNEL_SFX3    2

#define CHANNEL_JINGLE  3
#define CHANNEL_MUSIC   4
#define CHANNEL_MUSIC2  5



// We need to show lots of internal details of the module which are not
// exposed via public API, so include the internal header file.
#include "../../../libdragon/src/audio/libxm/xm_internal.h"

char g64_AudioBuffer[G64_AUDIO_BUFFER_SIZE];



wav64_t g64_WAVSFX[3];
wav64_t g64_WAVSong[2];
wav64_t g64_WAVFile;

char *g64_XMFile = NULL; //cur_rom
bool g64_XMMute[32] = { 0 }; //mute
int g64_XMChannel = 0; //chselect
static char* g64_XMFiles[4096]; //songfiles
static int g64_XMFilesQty; //num_songs
int music_frequency;
int64_t g64_XMTime, g64_XMCPU, g64_XMRSP, g64_XMDMA; //tot_time = 0, tot_cpu = 0, tot_rsp = 0, tot_dma = 0

xm64player_t g64_XMPlayer; //xm


void gin64_WAVAudio_Init() {
	audio_init(G64_AUDIO_QUALITY, 4);
	mixer_init(G64_AUDIO_MIXER_DEF);

	mixer_ch_set_limits(CHANNEL_MUSIC, 0, 128000, 0);


	wav64_open(&g64_WAVSong[0], "rom:/PauseLoop.wav64");
	wav64_set_loop(&g64_WAVSong[0], true);
	int music_frequency = g64_WAVSong[0].wave.frequency;


	music_frequency = g64_WAVSong[0].wave.frequency;
	wav64_play(&g64_WAVSong[0], CHANNEL_MUSIC);
	mixer_ch_set_freq(CHANNEL_MUSIC, music_frequency);

	//g64_XMFile = "rom:/lizardking_-_claustrophobia.xm64";
	//g64_XMFile = "rom:/beat_test.xm64";

	//debugf("Loading %s\n", g64_XMFile);

//	xm64player_open(&g64_XMPlayer, g64_XMFile);
//	xm64player_play(&g64_XMPlayer, 0);


	//wav64_open(g64_XMFile, g64_XMFile);
	//wav64_set_loop(g64_XMFile, true);

	//music_frequency = sfx_monosample.wave.frequency;
}

void gin64_WAVAudio_Song() {
	/*
	int g64_Music_Frequency = G64_AUDIO_QUALITY;

	if (g64_Music_Frequency >= 8000 && g64_Pad[0].Hold.C_Left) {
		g64_Music_Frequency /= 1.1;
		mixer_ch_set_freq(CHANNEL_MUSIC, g64_Music_Frequency);
	}
	if (g64_Music_Frequency * 1.1 <= 128000 && g64_Pad[0].Hold.C_Right) {
		g64_Music_Frequency *= 1.1;
		mixer_ch_set_freq(CHANNEL_MUSIC, g64_Music_Frequency);
	}
	*/
	//	g64_Pad[0].Hold.C_Up = hold.c[0].C_up;
	//	g64_Pad[0].Hold.C_Down = hold.c[0].C_down;
	//	g64_Pad[0].Hold.C_Left = hold.c[0].C_left;
	//	g64_Pad[0].Hold.C_Right = hold.c[0].C_right;
	

	if (audio_can_write()) {
		short* buf = audio_write_begin();
		mixer_poll(buf, audio_get_buffer_length());
		audio_write_end();
	}

	return;

	//wav64_play(&sfx_cannon, CHANNEL_SFX1);

}


u8 cycleSongChannel = 0;



void gin64_Audio_Jingle_Play(char* fileLocation) {

	mixer_ch_stop(CHANNEL_JINGLE);

	wav64_open(&g64_WAVSong[1], fileLocation);
	wav64_set_loop(&g64_WAVSong[1], false);
	int music_frequency = g64_WAVSong[1].wave.frequency;


	music_frequency = g64_WAVSong[1].wave.frequency;
	wav64_play(&g64_WAVSong[1], CHANNEL_JINGLE);
	mixer_ch_set_freq(CHANNEL_JINGLE, music_frequency);


}

void gin64_Audio_Music_Play(char* fileLocation) {


	//wav64_stop(&g64_WAVSong[0], CHANNEL_MUSIC);
	//wav64_close(&g64_WAVSong[0]);
	//wav64_close(&g64_WAVSong[0]);

	mixer_ch_stop(CHANNEL_MUSIC);

	wav64_open(&g64_WAVSong[0], fileLocation);
	wav64_set_loop(&g64_WAVSong[0], true);
	int music_frequency = g64_WAVSong[0].wave.frequency;


	music_frequency = g64_WAVSong[0].wave.frequency;
	wav64_play(&g64_WAVSong[0], CHANNEL_MUSIC);
	mixer_ch_set_freq(CHANNEL_MUSIC, music_frequency);


	//----- Note ----- Cycle each sound effect so that they are less likely to interrupt each other
	if (cycleSongChannel < 4) {
		cycleSongChannel += 1;
	}

	else
		cycleSongChannel = 0;

	/*
	wav64_open(&g64_WAVSFX[0], SC_Menu_SFX[0]);
	wav64_set_loop(&g64_WAVSFX[0], false);
	int music_frequency = g64_WAVSFX[0].wave.frequency;


	music_frequency = g64_WAVSFX[0].wave.frequency;
	wav64_play(&g64_WAVSFX[0], CHANNEL_MUSIC);
	mixer_ch_set_freq(CHANNEL_MUSIC, music_frequency);

	*/
}


u8 cycleSFXChannel = 0;

void gin64_Audio_SFX_Play(char* fileLocation) {
	

	mixer_ch_stop(cycleSFXChannel);

	wav64_open(&g64_WAVSFX[cycleSFXChannel], fileLocation);
	wav64_set_loop(&g64_WAVSFX[cycleSFXChannel], false);
	int music_frequency = g64_WAVSFX[0].wave.frequency;


	music_frequency = g64_WAVSFX[cycleSFXChannel].wave.frequency;
	wav64_play(&g64_WAVSFX[cycleSFXChannel], cycleSFXChannel);
	mixer_ch_set_freq(cycleSFXChannel, music_frequency);



	//----- Note ----- Cycle each sound effect so that they are less likely to interrupt each other
	if (cycleSFXChannel < 2) {
		cycleSFXChannel += 1;
	}

	else
		cycleSFXChannel = 0;

	/*
	wav64_open(&g64_WAVSFX[0], SC_Menu_SFX[0]);
	wav64_set_loop(&g64_WAVSFX[0], false);
	int music_frequency = g64_WAVSFX[0].wave.frequency;


	music_frequency = g64_WAVSFX[0].wave.frequency;
	wav64_play(&g64_WAVSFX[0], CHANNEL_MUSIC);
	mixer_ch_set_freq(CHANNEL_MUSIC, music_frequency);

	*/
}






























void gin64_XMAudio_Init() {
	audio_init(G64_AUDIO_QUALITY, 4);
	mixer_init(G64_AUDIO_MIXER_DEF);

	mixer_ch_set_limits(CHANNEL_MUSIC, 0, 128000, 0);

	//g64_XMFile = "rom:/lizardking_-_claustrophobia.xm64";
	g64_XMFile = "rom:/beat_test.xm64";

	debugf("Loading %s\n", g64_XMFile);

	xm64player_open(&g64_XMPlayer, g64_XMFile);
	xm64player_play(&g64_XMPlayer, 0);


	//wav64_open(g64_XMFile, g64_XMFile);
	//wav64_set_loop(g64_XMFile, true);

	//music_frequency = sfx_monosample.wave.frequency;
}

void gin64_XMAudio_Update() {
	//	wav64_play(g64_XMFile, CHANNEL_MUSIC);
}


void gin64_XMAudio_Song() {

	int g64_Music_Frequency = G64_AUDIO_QUALITY;

	if (g64_Music_Frequency >= 8000 && g64_Pad[0].Hold.C_Left) {
		g64_Music_Frequency /= 1.1;
		mixer_ch_set_freq(CHANNEL_MUSIC, g64_Music_Frequency);
	}
	if (g64_Music_Frequency * 1.1 <= 128000 && g64_Pad[0].Hold.C_Right) {
		g64_Music_Frequency *= 1.1;
		mixer_ch_set_freq(CHANNEL_MUSIC, g64_Music_Frequency);
	}

	if (audio_can_write()) {
		short* buf = audio_write_begin();
		mixer_poll(buf, audio_get_buffer_length());
		audio_write_end();
	}

	return;

	//wav64_play(&sfx_cannon, CHANNEL_SFX1);

}


void gin64_XMAudio_File() {

}

void gin64_Audio_SFX_Init() {


}