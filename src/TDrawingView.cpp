/*
 * TDrawingView.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#include "TDrawingView.h"

TDrawingView::TDrawingView() {
	// TODO Auto-generated constructor stub

}

TDrawingView::~TDrawingView() {
	// TODO Auto-generated destructor stub
}

Evas_Event_Flags mouse_cb(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

 //   dlog_print(DLOG_DEBUG, LOG_TAG, " OnClick() x:%d y:%d", tap_info->x, tap_info->y);

	v->OnClick(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}
Evas_Event_Flags move_cb(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

//    dlog_print(DLOG_DEBUG, LOG_TAG, "move_cb() x:%d y:%d", tap_info->x, tap_info->y);

	//v->OnClick(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags momentum_start(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
	Elm_Gesture_Momentum_Info *momentum_info = (Elm_Gesture_Momentum_Info *) event;

//    dlog_print(DLOG_DEBUG, LOG_TAG, "momentum_start x:%d y:%d", momentum_info->mx, momentum_info->my);

	v->OnMomentumStart(momentum_info->x1,momentum_info->y1);

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags momentum_move(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
	Elm_Gesture_Momentum_Info *momentum_info = (Elm_Gesture_Momentum_Info *) event;

 //   dlog_print(DLOG_DEBUG, LOG_TAG, "momentum_move x:%d y:%d", momentum_info->x2, momentum_info->y2);

	v->OnMomentumMove(momentum_info->x2,momentum_info->y2);

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags momentum_end(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
	Elm_Gesture_Momentum_Info *momentum_info = (Elm_Gesture_Momentum_Info *) event;

  //  dlog_print(DLOG_DEBUG, LOG_TAG, "momentum_end x:%d y:%d", momentum_info->x2, momentum_info->y2);

	v->OnMomentumEnd(momentum_info->x2,momentum_info->y2);

	return EVAS_EVENT_FLAG_ON_HOLD;
}
Evas_Event_Flags momentum_abort(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
	Elm_Gesture_Momentum_Info *momentum_info = (Elm_Gesture_Momentum_Info *) event;

  //  dlog_print(DLOG_DEBUG, LOG_TAG, "momentum_abort x:%d y:%d", momentum_info->x2, momentum_info->y2);

	v->OnMomentumEnd(momentum_info->x2,momentum_info->y2);

	return EVAS_EVENT_FLAG_ON_HOLD;
}
/*
Evas_Event_Flags line_start(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

    dlog_print(DLOG_DEBUG, LOG_TAG, "line_start x:%d y:%d", tap_info->x, tap_info->y);

	v->OnLineStart(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}
Evas_Event_Flags line_move(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    Elm_Gesture_Line_Info *line_info = (Elm_Gesture_Line_Info *) event;

    dlog_print(DLOG_DEBUG, LOG_TAG, "momentum y1:%d y2:%d", line_info->momentum.y1, line_info->momentum.y2);

	v->OnLineMove(line_info->momentum.x1, line_info->momentum.y1, line_info->momentum.x2, line_info->momentum.y2);

	return EVAS_EVENT_FLAG_ON_HOLD;
}
Evas_Event_Flags line_end(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;


    dlog_print(DLOG_DEBUG, LOG_TAG, "line_end x:%d y:%d", tap_info->x, tap_info->y);

	v->OnLineEnd(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags line_abort(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

    dlog_print(DLOG_DEBUG, LOG_TAG, "line_abort x:%d y:%d", tap_info->x, tap_info->y);

	v->OnLineAbort(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}
*/

void win_resize_cb2(void *data, Evas *e , Evas_Object *obj , void *event_info)
{
	// window resize event
	Evas_Coord width;
	Evas_Coord height;
	/* Get screen size */
	evas_object_geometry_get(obj, NULL, NULL, &width, &height);

	TView *view = (TView *)data;
	view->OnResize(width,height);
}

void TDrawingView::bottom_btn_create()
{

	/* Base Layout */
	layout = elm_layout_add(conform);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	//elm_layout_theme_set(layout, "layout", "application", "default");
	elm_layout_theme_set(layout, "layout", "bottom_button", "default");
	evas_object_show(layout);

	elm_object_content_set(conform, layout);

	Evas_Object *btn, *ly;

	btn = elm_button_add(conform);
	elm_object_style_set(btn, "bottom");
	elm_object_text_set(btn, "Undo (3)");
	elm_object_part_content_set(layout, "elm.swallow.button", btn);
	//evas_object_smart_callback_add(btn, "clicked", btn_clicked_cb, NULL);
	evas_object_show(btn);

	//elm_naviframe_item_push(nf, "Bottom", NULL, NULL, ly, NULL);
}

void TDrawingView::CreateContent(){
	  bottom_btn_create();
	/* Create image */
	image = evas_object_image_filled_add(evas_object_evas_get(conform));

	elm_object_part_content_set(layout, "elm.swallow.content", image);
	//evas_object_event_callback_add(image, EVAS_CALLBACK_RESIZE, win_resize_cb2, this);
	evas_object_show(image);

	graphics.setParentImage(image);

    // Add gesture layer

    Evas_Object *gesture_layer = elm_gesture_layer_add(conform);
    elm_gesture_layer_attach(gesture_layer, image);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_TAPS, ELM_GESTURE_STATE_END, mouse_cb, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_TAPS, ELM_GESTURE_STATE_MOVE, move_cb, this);

    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_MOMENTUM, ELM_GESTURE_STATE_MOVE, momentum_move, this);

    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_MOMENTUM, ELM_GESTURE_STATE_START, momentum_start, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_MOMENTUM, ELM_GESTURE_STATE_END, momentum_end, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_MOMENTUM, ELM_GESTURE_STATE_ABORT, momentum_abort, this);

/*    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_START, line_start, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_MOVE, line_move, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_END, line_end, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_ABORT, line_abort, this);
    */



    /*
    Evas_Object *button;
    // Create a button
    button = elm_button_add(conform);
    elm_object_text_set(button, "Click me!");
    evas_object_show(button);
    */
}


void TDrawingView::OnResize(int width, int height) {
	myWidth = width;
	myHeight = height;

	graphics.Initialize(width, height);

	CairoDrawing();

}


void TDrawingView::CairoDrawing(){


}
