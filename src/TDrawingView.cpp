/*
 * TDrawingView.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#include "TDrawingView.h"

TDrawingView::TDrawingView() {
	// TODO Auto-generated constructor stub
	surface = NULL;
}

TDrawingView::~TDrawingView() {
	// TODO Auto-generated destructor stub
}

Evas_Event_Flags _mouse_cb(void *data, void *event)
{
	TDrawingView *v = (TDrawingView *) data;

    // Get structure describing mouse event
   // Elm_Gesture_Taps_Info *move = (Elm_Gesture_Taps_Info *) event;

    //dlog_print(DLOG_DEBUG, LOG_TAG, "> _mouse_cb() x:%d y:%d", move->x, move->y);

	v->OnClick(10,10);

	return EVAS_EVENT_FLAG_ON_HOLD;
}

void TDrawingView::CreateContent(){

	/* Create image */
	image = evas_object_image_filled_add(evas_object_evas_get(conform));
	evas_object_show(image);

    // Add gesture layer

    Evas_Object *gesture_layer = elm_gesture_layer_add(conform);
    elm_gesture_layer_attach(gesture_layer, image);
    elm_gesture_layer_cb_set(gesture_layer, ELM_GESTURE_N_TAPS, ELM_GESTURE_STATE_START, _mouse_cb, this);

}


void TDrawingView::Resize(int width, int height) {
	myWidth = width;
	myHeight = height;
	if (surface) {
		/* Destroy previous cairo canvas */
		cairo_surface_destroy(surface);
		cairo_destroy(cairo);
		surface = NULL;
		cairo = NULL;
	}

	/* When window resize event occurred
		If no cairo surface exist or destroyed
		Create cairo surface with resized Window size */
	if (!surface) {
		/* Get screen size */
		//evas_object_geometry_get(obj, NULL, NULL, &s_info.width, &s_info.height);

		/* Set image size */
		evas_object_image_size_set(image, width, height);
		evas_object_resize(image, width, height);
		evas_object_show(image);

		/* Create new cairo canvas for resized window */
		pixels = (unsigned char*)evas_object_image_data_get(image, 1);
		surface = cairo_image_surface_create_for_data(pixels,
						CAIRO_FORMAT_ARGB32, width, height, width * 4);
		cairo = cairo_create(surface);

		/* Show cairo text */
		CairoDrawing();
	}
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
