/*
 * TImage.h
 *
 *  Created on: Dec 19, 2018
 *      Author: Alex
 */

#ifndef TIMAGE_H_
#define TIMAGE_H_


#include <cairo.h>

#include "TGraphics.h"

#include "TLinesGame.h"
#include "MainModelView.h"

class TImage {
public:
	TImage(Evas_Object *conform);
	virtual ~TImage();

	TCairoGraphics graphics;

	Evas_Object *image;
	Evas_Coord width;
	Evas_Coord height;

	double squareSize;
	double left_margin,top_margin;
	int myWidth, myHeight;

	MainModelView *modelView;
    TLinesGame* linesGame;

	void Init(int width, int height);
	void CairoDrawing();
	void CalcViewMarkup();
	void DrawHeader();
	void DrawBoard();
};

#endif /* TIMAGE_H_ */
