/*
 * TPopupBoxFactory.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: Alex
 */

#include "TPopupBoxFactory.h"

TPopupBoxFactory::TPopupBoxFactory() {
	// TODO Auto-generated constructor stub

}

TPopupBoxFactory::~TPopupBoxFactory() {
	// TODO Auto-generated destructor stub
}

TMenuPopupBox* TPopupBoxFactory::CreateMenuPopupBox(std::vector<const char*> buttonList) {
	TMenuPopupBox* p =  new TMenuPopupBox(buttonList);
	return p;
}
