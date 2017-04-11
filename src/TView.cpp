/*
 * TView.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#include "TView.h"


#include "TApplication.h"

TView::TView() {
	// TODO Auto-generated constructor stub
	win = 0;
	conform = 0;
	label= 0;
}

TView::~TView() {
	// TODO Auto-generated destructor stub
}

static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	TView *view = (TView *)data;
	/* Let window go to hide state. */
	elm_win_lower(view->win);
}

void TView::Create(){

	CreateWin(PACKAGE);

	CreateContent();

	/* Show window after base gui is set up */
	evas_object_show(win);
}

void TView::CreateContent(){
	/* Label */
	/* Create an actual view of the base gui.
	   Modify this part to change the view. */
	label = elm_label_add(conform);
	elm_object_text_set(label, "<align=center>Hello Basic View</align>");
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(conform, label);

}

void win_resize_cb(void *data, Evas *e , Evas_Object *obj , void *event_info)
{
	// window resize event
	TView *view = (TView *)data;
	view->Resize();
}

void TView::CreateWin(const char *pkg_name){
	/* Window */
	/* Create and initialize elm_win.
	   elm_win is mandatory to manipulate window. */
	win = elm_win_util_standard_add(pkg_name, pkg_name);
	elm_win_autodel_set(win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(win, EEXT_CALLBACK_BACK, win_back_cb, this);
	evas_object_event_callback_add(win, EVAS_CALLBACK_RESIZE, win_resize_cb, NULL);

	/* Conformant */
	/* Create and initialize elm_conformant.
	   elm_conformant is mandatory for base gui to have proper size
	   when indicator or virtual keypad is visible. */
	conform = elm_conformant_add(win);
	elm_win_indicator_mode_set(win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(win, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win, conform);
	evas_object_show(conform);

}
