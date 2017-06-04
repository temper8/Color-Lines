/*
 * TMenuPopupBox.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#include "TMenuPopupBox.h"

#include "..\TView.h"

void popup_btn1_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	TPopupBox *pp = (TPopupBox*)data;
//	pp->close();
	pp->btnClick(1);
}

void popup_btn2_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	TPopupBox *pp = (TPopupBox*)data;
//	pp->close();
	pp->btnClick(2);
}

void popup_btn3_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	TPopupBox *pp = (TPopupBox*)data;
//	pp->close();
	pp->btnClick(3);
}

void popup_btn4_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	TPopupBox *pp = (TPopupBox*)data;
//	pp->close();
	pp->btnClick(4);
}

TMenuPopupBox::TMenuPopupBox(TView *view):TPopupBox(view) {
	// TODO Auto-generated constructor stub
	Evas_Object *btn;
	Evas_Object *box;
	/* popup */
	myPopup = elm_popup_add(myView->win);
	elm_popup_align_set(myPopup,ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(myPopup, EEXT_CALLBACK_BACK, popup_btn1_clicked_cb, this);
	eext_object_event_callback_add(myPopup, EEXT_CALLBACK_MORE, popup_btn1_clicked_cb, this);
	evas_object_size_hint_weight_set(myPopup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
//	elm_object_text_set(myPopup, helpText.c_str());

	evas_object_smart_callback_add(myPopup, "block,clicked", popup_btn1_clicked_cb, this);

	/* box */
	box = elm_box_add(myPopup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_box_padding_set(box, 16, 16);

	Evas_Object *rect_1 = evas_object_rectangle_add((Evas *)myPopup);
	evas_object_color_set(rect_1, 200, 0, 0, 255);
	evas_object_size_hint_weight_set(rect_1, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(rect_1, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(rect_1);
	elm_box_pack_end(box, rect_1);


	/* ok button */
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "default");
	elm_object_text_set(btn, "Continue");
	evas_object_smart_callback_add(btn, "clicked", popup_btn1_clicked_cb, this);
	evas_object_size_hint_weight_set(btn, 0.5, EVAS_HINT_EXPAND);
	evas_object_size_hint_min_set(btn, 300, 80);
	evas_object_size_hint_align_set(btn, 0.5, 0.5);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	/* ok button */
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "default");
	elm_object_text_set(btn, "New Game");
	evas_object_smart_callback_add(btn, "clicked", popup_btn2_clicked_cb, this);
	evas_object_size_hint_weight_set(btn, 0.5, EVAS_HINT_EXPAND);
	evas_object_size_hint_min_set(btn, 300, 80);
	evas_object_size_hint_align_set(btn,  0.5, 0.5);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);

	btn = buttonAdd("Game Rules", 3);
	elm_box_pack_end(box, btn);
	btn = buttonAdd("Exit", 4);
	elm_box_pack_end(box, btn);
	/* ok button */
	/*
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "default");
	elm_object_text_set(btn, "Game Rules");
	evas_object_smart_callback_add(btn, "clicked", popup_btn3_clicked_cb, this);
	evas_object_size_hint_weight_set(btn, 0.5, EVAS_HINT_EXPAND);
	evas_object_size_hint_min_set(btn, 300, 80);
	evas_object_size_hint_align_set(btn,  0.5, 0.5);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);



	/* cancel button */
	/*
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "default");
	elm_object_text_set(btn, "Exit");
	evas_object_smart_callback_add(btn, "clicked", popup_btn4_clicked_cb, this);
	evas_object_size_hint_weight_set(btn, 0.5, EVAS_HINT_EXPAND);
	evas_object_size_hint_min_set(btn, 300, 80);
	evas_object_size_hint_align_set(btn, 0.5, 0.5);
	evas_object_show(btn);
	elm_box_pack_end(box, btn);
*/
	Evas_Object *rect_2 = evas_object_rectangle_add((Evas *)myPopup);
	evas_object_color_set(rect_2, 200, 0, 0, 255);
	evas_object_size_hint_weight_set(rect_2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(rect_2, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(rect_2);
	elm_box_pack_end(box, rect_2);

	evas_object_size_hint_min_set(box, 350, 192);
	//elm_object_part_content_set(myPopup, "elm.swallow.content", box);
	elm_object_content_set(myPopup, box);

}

TMenuPopupBox::~TMenuPopupBox() {
	// TODO Auto-generated destructor stub
}

Evas_Object * TMenuPopupBox::buttonAdd(const char* title, int tag){
	/* cancel button */
	int _tag = tag;
	Evas_Object *btn;
	btn = elm_button_add(myPopup);
	elm_object_style_set(btn, "default");
	elm_object_text_set(btn, title);
	evas_object_smart_callback_add(btn, "clicked", [](void *data, Evas_Object *obj, void *event_info){TPopupBox *pp = (TPopupBox*)data; pp->btnClick(3); }, this);
	evas_object_size_hint_weight_set(btn, 0.5, EVAS_HINT_EXPAND);
	evas_object_size_hint_min_set(btn, 300, 80);
	evas_object_size_hint_align_set(btn, 0.5, 0.5);
	evas_object_show(btn);
	return btn;
}

void popup_btn5_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	TPopupBox *pp = (TPopupBox*)data;
//	pp->close();
	pp->btnClick(4);
}
