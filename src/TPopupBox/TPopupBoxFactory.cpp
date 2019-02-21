/*
 * TPopupBoxFactory.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: Alex
 */

#include "TPopupBoxFactory.h"

#include "TMenuPopupBox.h"
#include "TExitPopupBox.h"
#include "TGameOverBox.h"
#include "TInfoBox.h"

TPopupBox* TPopupBoxFactory::myPopupBox = nullptr;

TPopupBoxFactory::TPopupBoxFactory() {
	// TODO Auto-generated constructor stub

}

TPopupBoxFactory::~TPopupBoxFactory() {
	// TODO Auto-generated destructor stub
}

void TPopupBoxFactory::DeletePopupBox(){
	if (myPopupBox!=nullptr) {
		delete myPopupBox;
		myPopupBox = nullptr;

	}
}

TPopupBox* TPopupBoxFactory::CreateMenuPopupBox(std::vector<const char*> buttonList) {
	DeletePopupBox();
	myPopupBox =  new TMenuPopupBox(buttonList);
	return myPopupBox;
}

TPopupBox* TPopupBoxFactory::CreateInfoBox(const char* text){
	DeletePopupBox();
	myPopupBox =  new TInfoBox(text);
	return myPopupBox;
}

TPopupBox* TPopupBoxFactory::CreateGameOverBox(){
	DeletePopupBox();
	myPopupBox =  new TGameOverBox();
	return myPopupBox;
}

TPopupBox* TPopupBoxFactory::CreateExitPopupBox(){
	DeletePopupBox();
	myPopupBox =  new TExitPopupBox();
	return myPopupBox;
}

