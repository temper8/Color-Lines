/*
 * TApplication.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#include "TApplication.h"

TApplication *TApplication::Instance = 0;

TApplication::TApplication() {
	// TODO Auto-generated constructor stub
	Instance = this;
}

TApplication::~TApplication() {
	// TODO Auto-generated destructor stub
}

void TApplication::Initialize() {
	 new TApplication();
}
