/*
 * TPopup.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#include "TPopupBox.h"

#include "..\TView.h"
#include "..\TApplication.h"

void popup_close_cb(void *data, Evas_Object *obj, void *event_info)
{
	TPopupBox *pp = (TPopupBox*)data;
	pp->btnClick(1);
}

TPopupBox::TPopupBox():myPopup(NULL), OnBtnClick(nullptr) {
	myPopup = elm_popup_add(TApplication::instance()->view()->win);
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

void TPopupBox::btnClick(int tag){
	if (OnBtnClick!=nullptr) OnBtnClick(tag);
}

void TPopupBox::btnClick(Evas_Object *btn){
	int tag = buttons[btn];
	btnClick(tag);
}

Evas_Object * TPopupBox::elmButtonAdd(const char* title, const char* style, int tag){
	Evas_Object *btn = elm_button_add(myPopup);
	elm_object_style_set(btn, style);
	elm_object_text_set(btn, title);
	evas_object_smart_callback_add(btn, "clicked",  [](void *data, Evas_Object *obj, void *event_info){((TPopupBox*)data)->btnClick(obj); }, this);
	buttons.insert(std::make_pair(btn, tag));
	return btn;
}
