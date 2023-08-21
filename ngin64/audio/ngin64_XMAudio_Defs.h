#ifndef NGIN64_XMAUDIO_DEFS_H
#define NGIN64_XMAUDIO_DEFS_H

//----- Note ----- Settings 
#define G64_AUDIO_QUALITY 44100
#define G64_AUDIO_MIXER_DEF 32
#define G64_AUDIO_BUFFER_SIZE 8192

#define G64_MenuSFX_Qty 6
static wav64_t SC_MenuSFX_Files[G64_MenuSFX_Qty];
static const char* SC_Menu_SFX[G64_MenuSFX_Qty] = {
	"rom:/Start.wav64", //0
	"rom:/Pause.wav64",
	"rom:/MenuOpen1.wav64",
	"rom:/MenuClose1.wav64",
	"rom:/MenuNav2.wav64",
	"rom:/MenuNav3.wav64", //5
};


#define G64_GameMusic_Qty 3
static const char* SC_Music_Songs[G64_GameMusic_Qty] = {
	"rom:/PauseLoop.wav64", //0
	"rom:/island_82_bpm.wav64",
	"rom:/Island_next_full.wav64",
};



#define G64_KingCrabSFX_Qty 7
static wav64_t SC_KingCrabSFX_Files[G64_KingCrabSFX_Qty];
static const char* SC_KingCrab_SFX[G64_KingCrabSFX_Qty] = {
	"rom:/CrabClaw1.wav64", //0
	"rom:/CrabClaw2.wav64",
	"rom:/CrabClaw3.wav64",
	"rom:/CrabWoodBlock1.wav64",
	"rom:/CrabWoodBlock2.wav64",
	"rom:/CrabHappy.wav64", //5
	"rom:/CrabSad.wav64",
};

#define G64_PlayfieldSFX_Qty 3
static wav64_t SC_PlayfieldSFX_Files[G64_PlayfieldSFX_Qty];
static const char* SC_Playfield_SFX[G64_PlayfieldSFX_Qty] = {
	"rom:/Place3.wav64", //0
	"rom:/Dig.wav64",
	"rom:/Fill.wav64",
};


/*
u8 SC_MenuSFX_Qty = 6;
wav64_t SC_MenuSFX_Files[6];
static const char* SC_Menu_SFX[6] = {


	u8 SC_KingCrabSFX_Qty = 7;
wav64_t SC_KingCrabSFX_Files[7];
static const char* SC_KingCrab_SFX[7];

	u8 SC_PlayfieldSFX_Qty = 3;
wav64_t SC_PlayfieldSFX_Files[3];
static const char* SC_Playfield_SFX[3];

*/

//----- Note ----- Sound Effect Function calls
extern void gin64_Audio_SFX_Init();
//extern void gin64_Audio_SFX_Play();
extern void gin64_Audio_SFX_Play(char* fileLocation);
extern void gin64_Audio_Music_Play(char* fileLocation);
void gin64_Audio_Jingle_Play(char* fileLocation);

//----- Note ----- Variables 
extern char g64_AudioBuffer[G64_AUDIO_BUFFER_SIZE];


//----- Note ----- XM Audio Function calls
extern void gin64_XMAudio_Init();

extern void gin64_XMAudio_File();

extern void gin64_XMAudio_Song();

//----- Note ----- WAV Audio Function calls
//----- Note ----- XM Audio Function calls
extern void gin64_WAVAudio_Init();

extern void gin64_WAVAudio_File();

extern void gin64_WAVAudio_Song();

#endif

