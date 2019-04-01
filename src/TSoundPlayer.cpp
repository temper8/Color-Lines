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


TSoundPlayer::TSoundPlayer() {

	// TODO Auto-generated constructor stub
#if TIZEN_API == 3
	  sound_manager_create_stream_information(SOUND_STREAM_TYPE_NOTIFICATION  , NULL, NULL, &stream_info);
#endif
	  SetWavPath("focus.wav");
}

TSoundPlayer::~TSoundPlayer() {
	// TODO Auto-generated destructor stub
}

void TSoundPlayer::PlayTone(tone_type_e tone){
#if TIZEN_API == 3
	 tone_player_start_new(tone, stream_info, 500, &tone_player_id);
#endif
}

void TSoundPlayer::SetWavPath(char *sound){
	 snprintf(wav_path, sizeof(wav_path), "%s/sound/%s", app_get_resource_path(), sound);
}

void TSoundPlayer::PlayWav(){
	 int ret;
#if TIZEN_API == 3
	 ret = wav_player_start_new(wav_path, stream_info, nullptr, (void*)wav_path, &wav_player_id);
#else
	 ret = wav_player_start(wav_path,  SOUND_TYPE_MEDIA, nullptr, (void*)wav_path, &wav_player_id);
#endif
}

void TSoundPlayer::PlayFocus(){
	SetWavPath("ping.wav");
	PlayWav();
}


void TSoundPlayer::PlayJump(){
	SetWavPath("j1.wav");
	PlayWav();
}

void TSoundPlayer::PlayMove(){
	SetWavPath("move3.wav");
	PlayWav();
}
void TSoundPlayer::PlayDestroy(){
	SetWavPath("d3.wav");
	PlayWav();
}
