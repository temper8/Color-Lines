/*
 * TCircleInfoBox.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Alex
 */

#include "TCircleInfoBox.h"

#include <efl_extension.h>


static void
_popup_hide_cb(void *data, Evas_Object *obj, void *event_info)
{
	if(!obj) return;
	elm_popup_dismiss(obj);
}

static void
_popup_hide_finished_cb(void *data, Evas_Object *obj, void *event_info)
{
	if(!obj) return;
	evas_object_del(obj);
}

static void _response_cb(void *data, Evas_Object *obj, void *event_info)
{
	if(!data) return;
	elm_popup_dismiss((Evas_Object *)data);
}


TCircleInfoBox::TCircleInfoBox(const char* text) {
	// TODO Auto-generated constructor stub
	Evas_Object *layout;

//	popup = elm_popup_add(ad->win);
	elm_object_style_set(myPopup, "circle");
	evas_object_size_hint_weight_set(myPopup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	eext_object_event_callback_add(myPopup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(myPopup, "dismissed", _popup_hide_finished_cb, NULL);


	layout = elm_layout_add(myPopup);
	elm_layout_theme_set(layout, "layout", "popup", "content/circle");
	elm_object_part_text_set(layout, "elm.text", text);
	elm_object_content_set(myPopup, layout);


	Evas_Object * btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "OK");
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set(myPopup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", _response_cb, myPopup);




	evas_object_show(myPopup);
}

TCircleInfoBox::~TCircleInfoBox() {
	// TODO Auto-generated destructor stub
}
