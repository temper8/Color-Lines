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

    //dlog_print(DLOG_DEBUG, LOG_TAG, "> _mouse_cb() x:%d y:%d", move->x, move->y);

	v->OnClick(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}



Evas_Event_Flags line_start(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

    dlog_print(DLOG_DEBUG, LOG_TAG, "line_start x:%d y:%d", tap_info->x, tap_info->y);

	//v->OnClick(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}
Evas_Event_Flags line_move(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

    dlog_print(DLOG_DEBUG, LOG_TAG, "line_move x:%d y:%d", tap_info->x, tap_info->y);

	//v->OnClick(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}
Evas_Event_Flags line_end(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

    dlog_print(DLOG_DEBUG, LOG_TAG, "line_end x:%d y:%d", tap_info->x, tap_info->y);

	//v->OnClick(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags line_abort(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

    dlog_print(DLOG_DEBUG, LOG_TAG, "line_abort x:%d y:%d", tap_info->x, tap_info->y);

	//v->OnClick(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}

void TDrawingView::CreateContent(){

	/* Create image */
	image = evas_object_image_filled_add(evas_object_evas_get(conform));
	evas_object_show(image);

	graphics.setParentImage(image);

    // Add gesture layer

    Evas_Object *gesture_layer = elm_gesture_layer_add(conform);
    elm_gesture_layer_attach(gesture_layer, image);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_TAPS, ELM_GESTURE_STATE_END, mouse_cb, this);

    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_START, line_start, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_MOVE, line_move, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_END, line_end, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_ABORT, line_abort, this);
}


void TDrawingView::Resize(int width, int height) {
	myWidth = width;
	myHeight = height;

	graphics.Initialize(width, height);

	CairoDrawing();

}


void TDrawingView::CairoDrawing(){


}
