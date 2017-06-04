/*
 * TMenuPopupBox.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#include "TMenuPopupBox.h"

#include "..\TView.h"


void popup_close_cb(void *data, Evas_Object *obj, void *event_info);


TMenuPopupBox::TMenuPopupBox(TView *view,  std::vector<const char*> buttonList):TPopupBox(view) {
	Evas_Object *btn;
	Evas_Object *box;

	myPopup = elm_popup_add(myView->win);
	elm_popup_align_set(myPopup,ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(myPopup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	eext_object_event_callback_add(myPopup, EEXT_CALLBACK_BACK, popup_close_cb, this);
	eext_object_event_callback_add(myPopup, EEXT_CALLBACK_MORE, popup_close_cb, this);
	evas_object_smart_callback_add(myPopup, "block,clicked", popup_close_cb, this);

	/* box */
	box = elm_box_add(myPopup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_box_padding_set(box, 16, 16);

	elm_box_pack_end(box, evasRectangleAdd());

	int tag = 1;
	for (const char* title : buttonList) {
		btn = elmButtonAdd(title, "default", tag++);
		evas_object_size_hint_weight_set(btn, 0.5, EVAS_HINT_EXPAND);
		evas_object_size_hint_min_set(btn, 300, 80);
		evas_object_size_hint_align_set(btn, 0.5, 0.5);
		evas_object_show(btn);
		elm_box_pack_end(box, btn);
	 }

	elm_box_pack_end(box, evasRectangleAdd());

	evas_object_size_hint_min_set(box, 350, 192);
	elm_object_content_set(myPopup, box);

}

TMenuPopupBox::~TMenuPopupBox() {
	// TODO Auto-generated destructor stub
}

Evas_Object * TMenuPopupBox::evasRectangleAdd(){
	Evas_Object *rect = evas_object_rectangle_add((Evas *)myPopup);
	evas_object_color_set(rect, 200, 0, 0, 255);
	evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(rect);
	return rect;
}


