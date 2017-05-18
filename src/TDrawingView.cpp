/*
 * TDrawingView.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#include "TDrawingView.h"

TDrawingView::TDrawingView():surface(NULL) {
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

static void back_cb(void *data, Evas_Object *obj, void *event_info) {
 // DBG("naviframe_back_cb");
  TDrawingView* dv = (TDrawingView*)data;
  dv->ShowPopup();
}

void TDrawingView::CreateContent(){


	eext_object_event_callback_add(win, EEXT_CALLBACK_BACK, back_cb, this);
	eext_object_event_callback_add(win, EEXT_CALLBACK_MORE, back_cb, this);

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

	cairo_set_source_rgb(cairo, 0.5, 0.5, 1.0);
	cairo_paint(cairo);

	cairo_set_line_width (cairo, 0.1);
	cairo_set_source_rgb (cairo, 0, 0, 0);
	cairo_rectangle (cairo, 50,50, 100, 100);
	cairo_stroke (cairo);

	cairo_set_source_rgb (cairo, 0, 0, 0);
	cairo_rectangle (cairo, 25, 25, 50, 50);
	cairo_fill (cairo);

	 /* Set blue color with opacity 0.3 value */
	 cairo_set_source_rgba(cairo, 0.2, 0.2, 1.0, 0.3);

	/* Draw a circle radius 10 on center point (x,y)
	   this circle displays the text start point */
	cairo_arc(cairo, 150, 150, 60.0, 0, 2*M_PI);

	/* Fill a circle with configured color before (blue) */
	cairo_fill(cairo);



	/* Render stacked cairo APIs on cairo context's surface */
	cairo_surface_flush(surface);

	/* Display cairo drawing on screen */
	evas_object_image_data_update_add(image, 0, 0, myWidth, myHeight);

}
