/*
 * TGameOverBox.cpp
 *
 *  Created on: May 29, 2017
 *      Author: Alex
 */

#include "TGameOverBox.h"

#include "..\TView.h"

TGameOverBox::TGameOverBox(TView *view):TPopupBox(view) {

	elm_popup_align_set(myPopup, 0.5, 0.5);
	evas_object_size_hint_weight_set(myPopup, EVAS_HINT_EXPAND, 0.5);

	elm_object_part_text_set(myPopup, "title,text", "Game over");

//	eext_object_event_callback_add(myPopup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
//	evas_object_smart_callback_add(myPopup, "block,clicked", popup_block_clicked_cb, NULL);

	Evas_Object *btn;

	btn = elmButtonAdd("New game","popup", 2);
	elm_object_part_content_set(myPopup, "button1", btn);

	btn = elmButtonAdd("Exit","popup", 1);
	elm_object_part_content_set(myPopup, "button2", btn);

}

TGameOverBox::~TGameOverBox() {
	// TODO Auto-generated destructor stub
}

