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


void TDrawingView::callbackMore(){
	ShowPopup();
}
void TDrawingView::callbackBack(){
	ShowPopup();
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

}


void TDrawingView::Resize(int width, int height) {
	myWidth = width;
	myHeight = height;

	graphics.Initialize(width, height);

	CairoDrawing();

}


void TDrawingView::CairoDrawing(){


}
