/*
 * TApp.cpp
 *
 *  Created on: Dec 18, 2018
 *      Author: Alex
 */

#include "TApp.h"


TApp::TApp() {
	// TODO Auto-generated constructor stub
	OnApplicationCreate();
}

TApp::~TApp() {
	// TODO Auto-generated destructor stub
}

void TApp::OnApplicationCreate(){
	myView = new TBoardView();
	myView->OnAppCreate();
}
