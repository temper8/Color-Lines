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

#include "TGraphics2.h"


class TDrawingView: public TView {
public:
	TDrawingView();
	virtual ~TDrawingView();



public:

	//TCairoGraphics graphics;
	void AttachGesture(Evas_Object *target);
	//Evas_Object *image;
	Evas_Coord width;
	Evas_Coord height;
	//cairo_t *cairo;
	//cairo_surface_t *surface;
	//unsigned char *pixels;

	virtual void OnResize(int width, int height) =0;
	//virtual void CairoDrawing();
	virtual void OnClick(int x, int y) {};
	virtual void OnLineStart(int x, int y) {};
	virtual void OnLineMove(int x1, int y1, int x2, int y2) {};
	virtual void OnLineEnd(int x, int y) {};
	virtual void OnLineAbort(int x, int y) {};

	virtual void OnMomentumStart(int x, int y) {};
	virtual void OnMomentumMove(int x1, int y1) {};
	virtual void OnMomentumEnd(int x, int y) {};

private:
	Evas_Object *layout;
	void bottom_btn_create();


protected:

	virtual void CreateContent();
	int myWidth, myHeight;


};

#endif /* TDRAWINGVIEW_H_ */
