/*
 * TArray2D.cpp
 *
 *  Created on: May 15, 2017
 *      Author: Alex
 */

#include "TArray2D.h"

#include <app_preference.h>

#define LOG_TAG "Color Lines"

#include <dlog.h>


static const char *key = "Array2D";

TArray2D::TArray2D() {
	// TODO Auto-generated constructor stub

}

TArray2D::~TArray2D() {
	// TODO Auto-generated destructor stub
}

void TArray2D::clear(){
	   for(auto &i: array) for(auto &k: i) k = 0;
}

void TArray2D::save(){
	std::string out_str;
	for(auto &i: array) for(auto &k: i) out_str = out_str + std::to_string(k);
	preference_set_string(key, out_str.c_str());
	dlog_print(DLOG_DEBUG, LOG_TAG, "out key %s out_str = %s.", key, out_str.c_str());
}

void TArray2D::load(){
	bool existing;
	int ret = preference_is_existing(key, &existing);
	if (ret != PREFERENCE_ERROR_NONE) {
		//dlog_print(DLOG_ERROR, LOG_TAG, "%s() failed. Err = %d.", func_name, ret);
		clear();
		return ;
	}

	if (existing) {
		char** s_value;
		ret = preference_get_string(key, s_value);
		if (ret == PREFERENCE_ERROR_NONE) {
			//value = i_value;
			dlog_print(DLOG_DEBUG, LOG_TAG, "get key %s value = %s.", key, *s_value);
			int ii = 0;
			char *str = *s_value;
			for(auto &i: array) for(auto &k: i) k = (int)str[ii++] - 48;
		}
	}
}
