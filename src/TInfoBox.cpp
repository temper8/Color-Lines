/*
 * TInfoBox.cpp
 *
 *  Created on: May 27, 2017
 *      Author: Alex
 */

#include "TInfoBox.h"

#include "TView.h"

TInfoBox::TInfoBox(TView *view):TPopupBox(view) {
	// TODO Auto-generated constructor stub
	Evas_Object *btn;
	/* popup */
	myPopup = elm_popup_add(myView->win);
	elm_popup_align_set(myPopup, ELM_NOTIFY_ALIGN_FILL, 0.5);
//	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(myPopup, EVAS_HINT_EXPAND, 0.5);
	elm_object_text_set(myPopup, "helpText.c_str()");

	//evas_object_smart_callback_add(popup, "block,clicked", popup_block_clicked_cb, NULL);

	/* ok button */
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "New Game");
	elm_object_part_content_set(myPopup, "button1", btn);
//	evas_object_smart_callback_add(btn, "clicked", popup_new_game_btn_clicked_cb, this);

	/* cancel button */
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "Exit");
	elm_object_part_content_set(myPopup, "button2", btn);
//	evas_object_smart_callback_add(btn, "clicked", popup_exit_btn_clicked_cb, popup);

}

TInfoBox::~TInfoBox() {
	// TODO Auto-generated destructor stub
}

