/*
 * TInfoBox.cpp
 *
 *  Created on: May 27, 2017
 *      Author: Alex
 */

#include "TInfoBox.h"

#include <efl_extension.h>


void popup_close_cb(void *data, Evas_Object *obj, void *event_info);

TInfoBox::TInfoBox(const char* text):TPopupBox() {

	elm_popup_align_set(myPopup, 0.5, 0.5);
	evas_object_size_hint_weight_set(myPopup, EVAS_HINT_EXPAND, 0.5);

	eext_object_event_callback_add(myPopup, EEXT_CALLBACK_BACK, popup_close_cb, this);
	evas_object_smart_callback_add(myPopup, "block,clicked", popup_close_cb, this);

	elm_object_text_set(myPopup, text);

/*	Evas_Object* textBlock = evas_object_textblock_add((Evas*)myPopup);
	evas_object_size_hint_weight_set(textBlock, 0.5, EVAS_HINT_EXPAND);
	evas_object_size_hint_min_set(textBlock, 300, 450);
	evas_object_size_hint_align_set(textBlock, 0.5, 0.5);
	evas_object_show(textBlock);
	 Evas_Textblock_Style *st = evas_textblock_style_new();
	evas_textblock_style_set(st, "DEFAULT='font=Sans font_size=22 color=#114 wrap=word'");
	evas_object_textblock_style_set(textBlock, st);
	elm_object_content_set(myPopup, textBlock);
	evas_object_textblock_text_markup_set(textBlock, text);
*/

	/* Continue button */
	Evas_Object *btn = elmButtonAdd("Continue","default", 1);
	elm_object_part_content_set(myPopup, "button1", btn);
}

TInfoBox::~TInfoBox() {
	// TODO Auto-generated destructor stub
}

