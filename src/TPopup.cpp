/*
 * TPopup.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#include "TPopup.h"

TPopup::TPopup(Evas_Object *win):myPopup(NULL), myWin(win), result(nullptr) {
	// TODO Auto-generated constructor stub

}

TPopup::~TPopup() {
	// TODO Auto-generated destructor stub
}

void TPopup::close() {
	evas_object_del(myPopup);
	myPopup = NULL;
}


void TPopup::show() {
if (myPopup != NULL) {
	evas_object_show(myPopup);
}
}