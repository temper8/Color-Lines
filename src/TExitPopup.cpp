/*
 * TExitPopup.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#include "TExitPopup.h"

TExitPopup::TExitPopup(Evas_Object *win):TPopup(win) {
	// TODO Auto-generated constructor stub
	/* popup */
	myPopup = elm_popup_add(myWin);
	elm_popup_align_set(myPopup, ELM_NOTIFY_ALIGN_FILL, 0.5);
//	eext_object_event_callback_add(myPopup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(myPopup, EVAS_HINT_EXPAND, 0.5);
//	elm_object_text_set(myPopup, helpText.c_str());

//	evas_object_smart_callback_add(myPopup, "block,clicked", popup_block_clicked_cb, NULL);

	Evas_Object *btn;

	/* ok button */
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "Yes");
	elm_object_part_content_set(myPopup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", NULL, this);

	/* cancel button */
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(myPopup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", NULL, myPopup);

}

TExitPopup::~TExitPopup() {
	// TODO Auto-generated destructor stub
}

