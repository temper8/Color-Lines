/*
 * TSoundPlayer.cpp
 *
 *  Created on: Mar 21, 2019
 *      Author: Alex
 */

#include <colorlines.h>
#include "TSoundPlayer.h"

#include <app.h>
#include <system_settings.h>
#include <efl_extension.h>

#if TIZEN_API == 3

const char *test_str = PLATFORM_VER;

#else

const char *test_str = "none";

#endif



TSoundPlayer::TSoundPlayer() {

	// TODO Auto-generated constructor stub
	  sound_manager_create_stream_information(SOUND_STREAM_TYPE_NOTIFICATION  , NULL, NULL, &stream_info);
	  SetWavPath("focus.wav");
}

TSoundPlayer::~TSoundPlayer() {
	// TODO Auto-generated destructor stub
}

void TSoundPlayer::PlayTone(tone_type_e tone){
	 tone_player_start_new(tone, stream_info, 500, &tone_player_id);
}

void TSoundPlayer::SetWavPath(char *sound){
	 snprintf(wav_path, sizeof(wav_path), "%s/sound/%s", app_get_resource_path(), sound);
}

void TSoundPlayer::PlayWav(){
	 int ret;

	 ret = wav_player_start_new(wav_path, stream_info, nullptr, (void*)wav_path, &wav_player_id);
}

void TSoundPlayer::PlayFocus(){
	SetWavPath("focus.wav");
	PlayWav();
}


void TSoundPlayer::PlayJump(){
	SetWavPath("jump.wav");
	PlayWav();
}

void TSoundPlayer::PlayMove(){
	SetWavPath("move.wav");
	PlayWav();
}
void TSoundPlayer::PlayDestroy(){
	SetWavPath("destroy.wav");
	PlayWav();
}
