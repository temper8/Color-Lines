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

void TDrawingView::CreateContent(){
	/* Label */
	/* Create an actual view of the base gui.
	   Modify this part to change the view. */
//	label = elm_label_add(conform);
//	elm_object_text_set(label, "<align=center>Hello Drawing View</align>");
//	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
//	elm_object_content_set(conform, label);

	/* Create image */
//	img = evas_object_image_filled_add(evas_object_evas_get(conform));
//	evas_object_show(img);

}


void TDrawingView::Resize(int width, int height) {
	if (surface) {
		/* Destroy previous cairo canvas */
	//	cairo_surface_destroy(surface);
	//	cairo_destroy(cairo);
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
//		evas_object_image_size_set(img, width, height);
//		evas_object_resize(img, width, height);
//		evas_object_show(img);

		/* Create new cairo canvas for resized window */
//		pixels = (unsigned char*)evas_object_image_data_get(img, 1);
//		surface = cairo_image_surface_create_for_data(pixels,
//						CAIRO_FORMAT_ARGB32, width, height, width * 4);
//		cairo = cairo_create(surface);

		/* Show cairo text */
//		start_cairo_drawing();
	}
}
