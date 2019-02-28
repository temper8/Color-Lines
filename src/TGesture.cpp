/*
 * TGesture.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: Alex
 */

#include "TGesture.h"
#include "logger.h"

TGesture::TGesture(Evas_Object *obj) {
	// TODO Auto-generated constructor stub
	gesture_layer = elm_gesture_layer_add(obj);
}

TGesture::~TGesture() {
	// TODO Auto-generated destructor stub
}

void TGesture::Create(Evas_Object *obj){
	gesture_layer = elm_gesture_layer_add(obj);
}



Evas_Event_Flags mouse_cb(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

    DBG( " OnClick() x:%d y:%d", tap_info->x, tap_info->y);

	//v->OnClick(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}
Evas_Event_Flags move_cb(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

    DBG( "move_cb() x:%d y:%d", tap_info->x, tap_info->y);

	//v->OnClick(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags momentum_start(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
	Elm_Gesture_Momentum_Info *momentum_info = (Elm_Gesture_Momentum_Info *) event;

	DBG( "momentum_start x:%d y:%d", momentum_info->mx, momentum_info->my);

	 if (v->MomentumStartEventHolder ==nullptr) return EVAS_EVENT_FLAG_ON_HOLD;
	if (momentum_info->n == 1)
		v->MomentumStartEventHolder(momentum_info->x1,momentum_info->y1);

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags momentum_move(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
	Elm_Gesture_Momentum_Info *momentum_info = (Elm_Gesture_Momentum_Info *) event;

	DBG( "momentum_move x:%d y:%d", momentum_info->x2, momentum_info->y2);

	if (v->MomentumMoveEventHolder ==nullptr) return EVAS_EVENT_FLAG_ON_HOLD;

	if (momentum_info->n == 1)
		v->MomentumMoveEventHolder(momentum_info->x2,momentum_info->y2);

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags momentum_end(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
	Elm_Gesture_Momentum_Info *momentum_info = (Elm_Gesture_Momentum_Info *) event;

	DBG( "momentum_end x:%d y:%d", momentum_info->x2, momentum_info->y2);

	if (v->MomentumEndEventHolder ==nullptr) return EVAS_EVENT_FLAG_ON_HOLD;

	if (momentum_info->n == 1)
		v->MomentumEndEventHolder(momentum_info->x2,momentum_info->y2);

	return EVAS_EVENT_FLAG_ON_HOLD;
}
Evas_Event_Flags momentum_abort(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
	Elm_Gesture_Momentum_Info *momentum_info = (Elm_Gesture_Momentum_Info *) event;

	if (v->MomentumEndEventHolder ==nullptr) return EVAS_EVENT_FLAG_ON_HOLD;

	DBG("momentum_abort x:%d y:%d", momentum_info->x2, momentum_info->y2);
	if (momentum_info->n == 1)
		v->MomentumEndEventHolder(momentum_info->x2,momentum_info->y2);

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


Evas_Event_Flags zoom_start(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
	Elm_Gesture_Zoom_Info *tap_info = (Elm_Gesture_Zoom_Info *) event;

   DBG("zoom_start z:%f", tap_info->zoom);

//	v->OnZoomStart();

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags zoom_move(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

	Elm_Gesture_Zoom_Info *line_info = (Elm_Gesture_Zoom_Info *) event;

   DBG( "zoom_move z:%f", line_info->zoom);
 //   v->OnZoomMove(line_info->zoom);
	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags zoom_end(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
	Elm_Gesture_Zoom_Info *tap_info = (Elm_Gesture_Zoom_Info *) event;


	DBG("zoom_end z:%f ", tap_info->zoom);

//	v->OnZoomEnd();

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags zoom_abort(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
	Elm_Gesture_Zoom_Info *tap_info = (Elm_Gesture_Zoom_Info *) event;

	DBG("line_abort z:%f", tap_info->zoom);

//	v->OnZoomAbort();

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags n_finger_tap_start(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

 //   dlog_print(DLOG_DEBUG, LOG_TAG, " OnClick() x:%d y:%d", tap_info->x, tap_info->y);

//	v->OnFingerTap(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}


Evas_Event_Flags n_finger_tap_end(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

 //   dlog_print(DLOG_DEBUG, LOG_TAG, " OnClick() x:%d y:%d", tap_info->x, tap_info->y);

    if (v->FingerTapEvent !=nullptr)
    	v->FingerTapEvent(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}

Evas_Event_Flags n_finger_tap_abort(void *data, void *event)
{
	TGesture *v = (TGesture *) data;

    // Get structure describing mouse event
    Elm_Gesture_Taps_Info *tap_info = (Elm_Gesture_Taps_Info *) event;

 //   dlog_print(DLOG_DEBUG, LOG_TAG, " OnClick() x:%d y:%d", tap_info->x, tap_info->y);

//	v->OnFingerTap(tap_info->x,tap_info->y);

	return EVAS_EVENT_FLAG_ON_HOLD;
}



void TGesture::Attach(Evas_Object *obj){
    elm_gesture_layer_attach(gesture_layer, obj);

    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_TAPS, ELM_GESTURE_STATE_START, n_finger_tap_start, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_TAPS, ELM_GESTURE_STATE_END, n_finger_tap_end, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_TAPS, ELM_GESTURE_STATE_ABORT, n_finger_tap_abort, this);

    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_MOMENTUM, ELM_GESTURE_STATE_MOVE, momentum_move, this);

    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_MOMENTUM, ELM_GESTURE_STATE_START, momentum_start, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_MOMENTUM, ELM_GESTURE_STATE_END, momentum_end, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_MOMENTUM, ELM_GESTURE_STATE_ABORT, momentum_abort, this);

/*    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_START, line_start, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_MOVE, line_move, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_END, line_end, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_LINES, ELM_GESTURE_STATE_ABORT, line_abort, this);
    */

    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_ZOOM, ELM_GESTURE_STATE_START, zoom_start, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_ZOOM, ELM_GESTURE_STATE_END, zoom_end, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_ZOOM, ELM_GESTURE_STATE_ABORT, zoom_abort, this);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_ZOOM, ELM_GESTURE_STATE_MOVE, zoom_move, this);
}
