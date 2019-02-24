/*
 * TCircleGameOverBox.cpp
 *
 *  Created on: Feb 25, 2019
 *      Author: Alex
 */

#include "TCircleGameOverBox.h"

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
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




TCircleGameOverBox::TCircleGameOverBox() {
	// TODO Auto-generated constructor stub

	char buf[1024];
	//popup = elm_popup_add(ad->win);

	elm_object_style_set(myPopup, "circle");
	evas_object_size_hint_weight_set(myPopup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	eext_object_event_callback_add(myPopup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(myPopup, "dismissed", _popup_hide_finished_cb, NULL);

	Evas_Object *layout = elm_layout_add(myPopup);
	elm_layout_theme_set(layout, "layout", "popup", "content/circle/buttons2");
	elm_object_part_text_set(layout, "elm.text.title", "Game over");

	elm_object_part_text_set(layout, "elm.text", "Play new game?");
	elm_object_content_set(myPopup, layout);

	//Evas_Object *btn = elm_button_add(myPopup);
	//elm_object_style_set(btn, "popup/circle/left");
	Evas_Object *btn = elmButtonAdd(nullptr,"popup/circle/left", 1);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set(myPopup, "button1", btn);
	//evas_object_smart_callback_add(btn, "clicked", _response_cb, myPopup);

	Evas_Object *icon = elm_image_add(btn);
	snprintf(buf, sizeof(buf), "%s/%s", app_get_resource_path(), "tw_ic_popup_btn_delete.png");
	elm_image_file_set(icon, buf, NULL);
	evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set(btn, "elm.swallow.content", icon);
	evas_object_show(icon);

	btn = elmButtonAdd(nullptr,"popup/circle/right", 2);//elm_button_add(myPopup);
	//elm_object_style_set(btn, "popup/circle/right");
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set(myPopup, "button2", btn);
	//evas_object_smart_callback_add(btn, "clicked", _response_cb, myPopup);

	icon = elm_image_add(btn);
	snprintf(buf, sizeof(buf), "%s/%s", app_get_resource_path(), "tw_ic_popup_btn_check.png");
	elm_image_file_set(icon, buf, NULL);
	evas_object_size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set(btn, "elm.swallow.content", icon);
	evas_object_show(icon);

	evas_object_show(myPopup);
}

TCircleGameOverBox::~TCircleGameOverBox() {
	// TODO Auto-generated destructor stub
}

