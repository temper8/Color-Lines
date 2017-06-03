/*
 * TArray2D.cpp
 *
 *  Created on: May 15, 2017
 *      Author: Alex
 */

#include "TBoard.h"

#include <string>
#include <app_preference.h>

#define LOG_TAG "Color Lines"

#include <dlog.h>


static const char *key = "Board";

TBoard::TBoard() {
	// TODO Auto-generated constructor stub

}

TBoard::~TBoard() {
	// TODO Auto-generated destructor stub
}

void TBoard::clear(){
	   for(auto &i: array) for(auto &k: i) k = 0;
}

void TBoard::save(){
	std::string out_str;
	for(auto &i: array) for(auto &k: i) out_str = out_str + std::to_string(k);
	preference_set_string(key, out_str.c_str());
	dlog_print(DLOG_DEBUG, LOG_TAG, "out key %s out_str = %s.", key, out_str.c_str());
}

void TBoard::load(){
	bool existing;
	int ret = preference_is_existing(key, &existing);
	if (ret != PREFERENCE_ERROR_NONE) {
		//dlog_print(DLOG_ERROR, LOG_TAG, "%s() failed. Err = %d.", func_name, ret);
		clear();
		return ;
	}

	if (existing) {
		char *str;
		ret = preference_get_string(key, &str);
		if (ret == PREFERENCE_ERROR_NONE) {
			dlog_print(DLOG_DEBUG, LOG_TAG, "get key %s value = %s.", key, str);
			int i = 0;
			for(auto &row: array) for(auto &k: row) k = (int)str[i++] - 48;
		}
	}
}
