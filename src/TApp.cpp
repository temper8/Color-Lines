/*
 * TApp.cpp
 *
 *  Created on: Dec 18, 2018
 *      Author: Alex
 */

#include "TApp.h"


TApp::TApp() {
	// TODO Auto-generated constructor stub
	myView = new TBoardView();
	myView->OnAppCreate();
}

TApp::~TApp() {
	// TODO Auto-generated destructor stub
}

