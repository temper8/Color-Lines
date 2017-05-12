/*
 * TPreferenceInt.cpp
 *
 *  Created on: May 12, 2017
 *      Author: Alex
 */

#include "TPreferenceInt.h"

TPreferenceInt::TPreferenceInt(const char *key): myKey(key), value(0) {
	// TODO Auto-generated constructor stub
}

TPreferenceInt::~TPreferenceInt() {
	// TODO Auto-generated destructor stub
}



TPreferenceInt& operator+=(TPreferenceInt& left, const int& right) {
    left.value += right;
    return left;
}
