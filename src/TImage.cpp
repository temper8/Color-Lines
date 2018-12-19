/*
 * TImage.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: Alex
 */

#include "TImage.h"

TImage::TImage(Evas_Object *conform):width(0),height(0) {
	// TODO Auto-generated constructor stub
	image = evas_object_image_filled_add(evas_object_evas_get(conform));

//	elm_object_part_content_set(layout, "elm.swallow.content", image);
	//evas_object_event_callback_add(image, EVAS_CALLBACK_RESIZE, win_resize_cb2, this);
	evas_object_show(image);

	graphics.setParentImage(image);
}

TImage::~TImage() {
	// TODO Auto-generated destructor stub
}

