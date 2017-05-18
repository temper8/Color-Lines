/*
 * TGraphics.cpp
 *
 *  Created on: May 19, 2017
 *      Author: Alex
 */

#include "TGraphics.h"
#include <app.h>
//#include <Elementary.h>
//#include <system_settings.h>
//#include <efl_extension.h>


#define BUFLEN 500

TGraphics::TGraphics():surface(NULL) {
	// TODO Auto-generated constructor stub

}

TGraphics::~TGraphics() {
	// TODO Auto-generated destructor stub
}

void TGraphics::Initialize(int width, int height){

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
		evas_object_image_size_set(myImage, width, height);
		evas_object_resize(myImage, width, height);
		evas_object_show(myImage);

		/* Create new cairo canvas for resized window */
		pixels = (unsigned char*)evas_object_image_data_get(myImage, 1);
		surface = cairo_image_surface_create_for_data(pixels,
						CAIRO_FORMAT_ARGB32, width, height, width * 4);
		cairo = cairo_create(surface);

	}
}


void TGraphics::LoadBgImage(){
	//  Load bg image, create surface from bg image

	char buff[BUFLEN];
    char *path = app_get_shared_resource_path();

    snprintf(buff, 300, "%s%s", path, "pat9.png");
    bg_image = cairo_image_surface_create_from_png(buff);
    free(path);
}

void TGraphics::Flush(){

	/* Render stacked cairo APIs on cairo context's surface */
	cairo_surface_flush(surface);
	/* Display cairo drawing on screen */
	evas_object_image_data_update_add(myImage, 0, 0, myWidth, myHeight);
}

void TGraphics::FillBackgroud(){

	cairo_set_source_rgb(cairo, 0.5, 0.5, 1.0);
	cairo_paint(cairo);

	cairo_pattern_t *pattern1 = cairo_pattern_create_for_surface(bg_image);

	cairo_set_source(cairo, pattern1);
	cairo_pattern_set_extend(cairo_get_source(cairo), CAIRO_EXTEND_REPEAT);
	cairo_rectangle(cairo, 0, 0, myWidth, myHeight);
	cairo_fill(cairo);

}

