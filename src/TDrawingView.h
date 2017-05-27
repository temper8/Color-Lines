/*
 * TDrawingView.h
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#ifndef TDRAWINGVIEW_H_
#define TDRAWINGVIEW_H_

#include "TView.h"
#include <cairo.h>
#include "TGraphics.h"


class TDrawingView: public TView {
public:
	TDrawingView();
	virtual ~TDrawingView();



public:

	TGraphics graphics;

	Evas_Object *image;
	Evas_Coord width;
	Evas_Coord height;
	//cairo_t *cairo;
	//cairo_surface_t *surface;
	//unsigned char *pixels;

	virtual void Resize(int width, int height);
	virtual void CairoDrawing();
	virtual void OnClick(int x, int y) {};

private:



protected:

	virtual void CreateContent();
	int myWidth, myHeight;


};

#endif /* TDRAWINGVIEW_H_ */
