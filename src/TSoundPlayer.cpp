/*
 * TSoundPlayer.cpp
 *
 *  Created on: Mar 21, 2019
 *      Author: Alex
 */

#include "TSoundPlayer.h"




TSoundPlayer::TSoundPlayer() {
	// TODO Auto-generated constructor stub
	  sound_manager_create_stream_information(SOUND_STREAM_TYPE_NOTIFICATION, NULL, NULL, &stream_info);
}

TSoundPlayer::~TSoundPlayer() {
	// TODO Auto-generated destructor stub
}

void TSoundPlayer::PlayTone(tone_type_e tone){
	 tone_player_start_new(tone, stream_info, 500, &tone_player_id);
}
