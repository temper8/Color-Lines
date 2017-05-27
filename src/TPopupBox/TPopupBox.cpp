/*
 * TPopup.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#include "TPopupBox.h"

TPopupBox::TPopupBox(TView *view):myPopup(NULL), myView(view), result(nullptr) {
	// TODO Auto-generated constructor stub

}

TPopupBox::~TPopupBox() {
	// TODO Auto-generated destructor stub
	close();
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

void TPopupBox::sendResult(int r){
	if (result!=nullptr) result(myView, r);
}
