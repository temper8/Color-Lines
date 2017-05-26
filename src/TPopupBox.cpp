/*
 * TPopup.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#include "TPopupBox.h"

TPopupBox::TPopupBox(Evas_Object *win):myPopup(NULL), myWin(win), result(nullptr) {
	// TODO Auto-generated constructor stub

}

TPopupBox::~TPopupBox() {
	// TODO Auto-generated destructor stub
}

void TPopupBox::close() {
	evas_object_del(myPopup);
	myPopup = NULL;
}


void TPopupBox::show() {
if (myPopup != NULL) {
	evas_object_show(myPopup);
}
}