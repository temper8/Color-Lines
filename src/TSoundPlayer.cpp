/*
 * TSoundPlayer.cpp
 *
 *  Created on: Mar 21, 2019
 *      Author: Alex
 */

#include "TSoundPlayer.h"

#include <app.h>
#include <system_settings.h>
#include <efl_extension.h>

TSoundPlayer::TSoundPlayer() {
	// TODO Auto-generated constructor stub
	  sound_manager_create_stream_information(SOUND_STREAM_TYPE_NOTIFICATION, NULL, NULL, &stream_info);
	  snprintf(wav_path, sizeof(wav_path), "%s/%s", app_get_resource_path(), "focus.wav");
}

TSoundPlayer::~TSoundPlayer() {
	// TODO Auto-generated destructor stub
}

void TSoundPlayer::PlayTone(tone_type_e tone){
	 tone_player_start_new(tone, stream_info, 500, &tone_player_id);
}

void TSoundPlayer::PlayWav(){
	 int ret;

	 ret = wav_player_start_new(wav_path, stream_info, nullptr, (void*)wav_path, &wav_player_id);
}
