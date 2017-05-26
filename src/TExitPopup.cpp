/*
 * TExitPopup.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#include "TExitPopup.h"


void popup_new_yes_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	TPopupBox *pp = (TPopupBox*)data;
	pp->close();

	if (pp->result!=nullptr) pp->result(1);
}

void popup_new_game_cancel_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	TPopupBox *pp = (TPopupBox*)data;
	pp->close();

	if (pp->result!=nullptr) pp->result(2);
}

TExitPopup::TExitPopup(Evas_Object *win):TPopupBox(win) {
	// TODO Auto-generated constructor stub
	/* popup */
	myPopup = elm_popup_add(myWin);
	elm_popup_align_set(myPopup, 0.6, 0.5);
//	eext_object_event_callback_add(myPopup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(myPopup, EVAS_HINT_EXPAND, 0.5);
	elm_object_part_text_set(myPopup, "title,text", "Are you sure you want exit?");
	//elm_object_text_set(myPopup, "Are you sure you want exit");

//	evas_object_smart_callback_add(myPopup, "block,clicked", popup_block_clicked_cb, NULL);

	Evas_Object *btn;

	/* ok button */
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "Yes");
	elm_object_part_content_set(myPopup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", popup_new_yes_btn_clicked_cb, this);

	/* cancel button */
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "Cancel");
	elm_object_part_content_set(myPopup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", popup_new_game_cancel_clicked_cb, this);

}

TExitPopup::~TExitPopup() {
	// TODO Auto-generated destructor stub
}

