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
	create_win(PACKAGE);

	create_conform();





	/*
	 * Eext circle
	 * Create Eext circle surface for circular genlist and datetime object
	 * This make this app can show circular layout.
	 */
	//circle_surface = eext_circle_surface_naviframe_add(nf);

	/* Base Layout */
		layout = elm_layout_add(conform);
		evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		//elm_layout_theme_set(layout, "layout", "application", "default");
		elm_layout_theme_set(layout, "layout", "drawer", "panel");
		evas_object_show(layout);

		elm_object_content_set(conform, layout);

//	create_naviframe();
	//#ifdef Wearable

//	evas_object_show(more_option);
	//#endif /* __EFL_EXTENSION_MORE_OPTION_H__ */

	//elm_naviframe_item_push(nf, "More Option Demo", NULL, NULL, more_option, "empty");
//	CreateContent();

	/* Show window after base gui is set up */
	evas_object_show(win);
}

TView::~TView() {
	// TODO Auto-generated destructor stub
}

static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

/*
void callback_back(void *data, Evas_Object *obj, void *event_info)
{
	TView *view = (TView *)data;
	view->OnBackKeyClick();

}
*/

void TView::CreateContent(){
	/* Label */
	/* Create an actual view of the base gui.
	   Modify this part to change the view. */
	Evas_Object *label = elm_label_add(conform);
	elm_object_text_set(label, "<align=center>Hello Basic View</align>");
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(conform, label);

}

void win_resize_cb(void *data, Evas *e , Evas_Object *obj , void *event_info)
{
	// window resize event
	Evas_Coord width;
	Evas_Coord height;
	/* Get screen size */
	evas_object_geometry_get(obj, NULL, NULL, &width, &height);

	TView *view = (TView *)data;
	view->OnResize(width,height);
}

void TView::create_win(const char *pkg_name){
	/* Window */
	/* Create and initialize elm_win.
	   elm_win is mandatory to manipulate window. */
	win = elm_win_util_standard_add(pkg_name, pkg_name);
	elm_win_autodel_set(win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(win)) {
		//int rots[4] = { 0, 90, 180, 270 };
		int rots[1] = { 0 };
		elm_win_wm_rotation_available_rotations_set(win, (const int *)(&rots), 1);
	}

	evas_object_smart_callback_add(win, "delete,request", win_delete_request_cb, NULL);
//	eext_object_event_callback_add(win, EEXT_CALLBACK_BACK, callback_back, this);
//	eext_object_event_callback_add(win, EEXT_CALLBACK_MORE, callback_more, this);

	evas_object_event_callback_add(win, EVAS_CALLBACK_RESIZE, win_resize_cb, this);


}
void TView::create_conform(){
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

	eext_object_event_callback_add(conform, EEXT_CALLBACK_BACK, [](void *data, Evas_Object *obj, void *event_info){ui_app_exit();}, this);
	eext_object_event_callback_add(conform, EEXT_CALLBACK_MORE, [](void *data, Evas_Object *obj, void *event_info){((TView*)data)->OnMenuKeyClick();}, this);

}
void TView::create_naviframe(){
	/* Naviframe */
	nf = elm_naviframe_add(layout);
	//create_list_view(ad);
	elm_object_part_content_set(layout, "elm.swallow.content", nf);
	//eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_BACK, eext_naviframe_back_cb, NULL);
	//eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_MORE, eext_naviframe_more_cb, NULL);


	if (nf == nullptr) {
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to create a naviframe.");
		evas_object_del(win);
		return;
	}
}
void TView::Create_Base_GUI_Mobile(const char *pkg_name){
	/* Window */
	/* Create and initialize elm_win.
	   elm_win is mandatory to manipulate window. */
	win = elm_win_util_standard_add(pkg_name, pkg_name);
	elm_win_autodel_set(win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(win)) {
		//int rots[4] = { 0, 90, 180, 270 };
		int rots[1] = { 0 };
		elm_win_wm_rotation_available_rotations_set(win, (const int *)(&rots), 1);
	}

	evas_object_smart_callback_add(win, "delete,request", win_delete_request_cb, NULL);
//	eext_object_event_callback_add(win, EEXT_CALLBACK_BACK, callback_back, this);
//	eext_object_event_callback_add(win, EEXT_CALLBACK_MORE, callback_more, this);

	evas_object_event_callback_add(win, EVAS_CALLBACK_RESIZE, win_resize_cb, this);



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

	eext_object_event_callback_add(conform, EEXT_CALLBACK_BACK, [](void *data, Evas_Object *obj, void *event_info){((TView*)data)->OnBackKeyClick();}, this);
	eext_object_event_callback_add(conform, EEXT_CALLBACK_MORE, [](void *data, Evas_Object *obj, void *event_info){((TView*)data)->OnMenuKeyClick();}, this);


	// window resize event
//	Evas_Coord width;
//	Evas_Coord height;
	/* Get screen size */
//	evas_object_geometry_get(win, NULL, NULL, &width, &height);
//	dlog_print(DLOG_DEBUG, LOG_TAG, " geometry_get x:%d y:%d", width, height);
//	OnResize(width,height);

}
void TView::Create_Base_GUI_Wearable(const char *pkg_name){

}
