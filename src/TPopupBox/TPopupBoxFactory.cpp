/*
 * TPopupBoxFactory.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: Alex
 */

#include "TPopupBoxFactory.h"

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
