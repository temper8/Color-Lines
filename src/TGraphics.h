/*
 * TGraphics.h
 *
 *  Created on: May 19, 2017
 *      Author: Alex
 */

#ifndef TGRAPHICS_H_
#define TGRAPHICS_H_

#include <cairo.h>
#include <Elementary.h>

class TGraphics {
public:
	TGraphics();
	virtual ~TGraphics();

private:
	Evas_Object *image;
	Evas_Coord width;
	Evas_Coord height;
	cairo_t *cairo;
	cairo_surface_t *surface;
	unsigned char *pixels;
};

#endif /* TGRAPHICS_H_ */
