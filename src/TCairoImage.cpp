/*
 * TCairoGraphics.cpp
 *
 *  Created on: Dec 25, 2018
 *      Author: Alex
 */

#include "logger.h"
#include <app.h>
#include "TCairoImage.h"

//#include <Elementary.h>
//#include <system_settings.h>
//#include <efl_extension.h>



TCairoImage::TCairoImage() {
	// TODO Auto-generated constructor stub

}

TCairoImage::~TCairoImage() {
	// TODO Auto-generated destructor stub
}

void cairo_drawing(void *data, Evas_Object *o)
{
	TCairoImage *g = (TCairoImage*)data;
	g->Paint();
}

void TCairoImage::Create(Evas_Object *parent){


	myImage = evas_object_image_filled_add(evas_object_evas_get(parent));
	//evas_object_lower(myImage);
//	myImage = evas_object_image_add(evas_object_evas_get(parent));
//	evas_object_image_load_size_set(myImage,100, 100);

//	image = elm_object_part_content_get(parent, part_name);
	//evas_object_event_callback_add(image, EVAS_CALLBACK_RESIZE, win_resize_cb2, this);
	evas_object_show(myImage);
    evas_object_image_pixels_get_callback_set(myImage, cairo_drawing, this);
}

void TCairoImage::Destroy(){
	DBG("TCairoGraphics::Destroy");
	if (mySurface) {
		/* Destroy cairo canvas */
		cairo_surface_destroy(mySurface);
		cairo_destroy(myCairo);
		mySurface = NULL;
		myCairo = NULL;
		DBG("Destroy Cairo");
	}
}

void TCairoImage::Initialize(int width, int height){


	DBG("Initialize x:%d y:%d", width, height);

	myWidth = width;
	myHeight = height;

	if (mySurface) {
		/* Destroy previous cairo canvas */
		cairo_surface_destroy(mySurface);
		cairo_destroy(myCairo);
		mySurface = NULL;
		myCairo = NULL;
	}

	/* When window resize event occurred
		If no cairo surface exist or destroyed
		Create cairo surface with resized Window size */
	if (!mySurface) {
		/* Get screen size */
		//evas_object_geometry_get(obj, NULL, NULL, &s_info.width, &s_info.height);

		/* Set image size */
		evas_object_image_size_set(myImage, width, height);
		evas_object_resize(myImage, width, height);
		evas_object_show(myImage);

		/* Create new cairo canvas for resized window */
		unsigned char *pixels = (unsigned char*)evas_object_image_data_get(myImage, 1);

		mySurface = cairo_image_surface_create_for_data(pixels, CAIRO_FORMAT_ARGB32, width, height, width * 4);
		myCairo = cairo_create(mySurface);
	}
}



void TCairoImage::Refresh()
{
    evas_object_image_pixels_dirty_set(myImage, EINA_TRUE);
}
