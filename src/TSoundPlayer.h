/*
 * TSoundPlayer.h
 *
 *  Created on: Mar 21, 2019
 *      Author: Alex
 */

#ifndef TSOUNDPLAYER_H_
#define TSOUNDPLAYER_H_

#include <sound_manager.h>
#include <tone_player.h>
#include <wav_player.h>

class TSoundPlayer {
public:
	TSoundPlayer();
	virtual ~TSoundPlayer();

	void PlayFocus();
	void PlayJump();
	void PlayMove();
	void PlayDestroy();

private:
	void SetWavPath(char *sound);
	void PlayWav();
	void PlayTone(tone_type_e tone);
    int tone_type = 0;
	int tone_player_id = 0;
	int wav_player_id = 0;
#if TIZEN_API == 3
    sound_stream_info_h stream_info;
#endif

    char wav_path[1024];
};

#endif /* TSOUNDPLAYER_H_ */
