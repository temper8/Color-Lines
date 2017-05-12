/*
 * TPreferenceInt.cpp
 *
 *  Created on: May 12, 2017
 *      Author: Alex
 */

#include "TPreferenceInt.h"

#include <app_preference.h>

#include <dlog.h>

#define LOG_TAG "Color Lines"

TPreferenceInt::TPreferenceInt(const char *key): myKey(key), value(0) {
	// TODO Auto-generated constructor stub
	bool existing;
	int ret = preference_is_existing(key, &existing);
	if (ret != PREFERENCE_ERROR_NONE) {
		//dlog_print(DLOG_ERROR, LOG_TAG, "%s() failed. Err = %d.", func_name, ret);
		return ;
	}

	if (existing) {
		int i_value;
		ret = preference_get_int(key, &i_value);
		if (ret == PREFERENCE_ERROR_NONE) {
			value = i_value;
			dlog_print(DLOG_DEBUG, LOG_TAG, "get key %s value = %d.", myKey, value);
		}
	}
	else {
		preference_set_int(key, value);
		dlog_print(DLOG_DEBUG, LOG_TAG, "set key %s value = %d.", myKey, value);
	}

}

TPreferenceInt::~TPreferenceInt() {
	// TODO Auto-generated destructor stub
}

TPreferenceInt& operator+=(TPreferenceInt& left, const int& right) {
    left.value += right;
    left.update();
    return left;
}

void TPreferenceInt::update(){
	preference_set_int(myKey, value);
	dlog_print(DLOG_DEBUG, LOG_TAG, "update key %s value = %d.", myKey, value);
}
