/*
 * TInfoBox.cpp
 *
 *  Created on: May 27, 2017
 *      Author: Alex
 */

#include "TInfoBox.h"

#include "..\TView.h"

void popup_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	TPopupBox *pp = (TPopupBox*)data;
	pp->btnClick(1);
}


TInfoBox::TInfoBox(TView *view, const char* text):TPopupBox(view) {
	// TODO Auto-generated constructor stub
	Evas_Object *btn;
	/* popup */
	myPopup = elm_popup_add(myView->win);
	elm_popup_align_set(myPopup, 0.5, 0.5);
	eext_object_event_callback_add(myPopup, EEXT_CALLBACK_BACK, popup_btn_clicked_cb, this);
	evas_object_size_hint_weight_set(myPopup, EVAS_HINT_EXPAND, 0.5);
	elm_object_text_set(myPopup, text);

	evas_object_smart_callback_add(myPopup, "block,clicked", popup_btn_clicked_cb, this);

	/* ok button */
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "default");
	elm_object_text_set(btn, "Continue");
	elm_object_part_content_set(myPopup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", popup_btn_clicked_cb, this);

}

TInfoBox::~TInfoBox() {
	// TODO Auto-generated destructor stub
}

