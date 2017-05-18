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
	void setParentImage(Evas_Object *image) {myImage = image; };

	void Initialize(int width, int height);

	void LoadBgImage();

	void Flush();

private:
	Evas_Object *myImage;
	Evas_Coord width;
	Evas_Coord height;
	cairo_t *cairo;
	cairo_surface_t *surface;
	unsigned char *pixels;

	int myWidth, myHeight;

	cairo_surface_t *bg_image;
};

#endif /* TGRAPHICS_H_ */
