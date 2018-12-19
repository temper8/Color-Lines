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

    std::vector<TBall> balls;

    TBall selBall;
    TBall destSquare;

    bool isBallSelected = false;
	double tick;
	void JumpingBall();


	void Init(int width, int height);
	void CairoDrawing();
	void Flush();

	void CalcViewMarkup();
	void DrawHeader();
	void DrawBoard();

	void DrawSquare(TBall p);
    void DrawBall(double x, double y, int color);
    void DrawBall(double x, double y, double r, int color);
    void DrawBall(TBall p, double r, int color);
    void DrawBall(TBall p, double r);



	void appearanceNewBall(double pos);
};

#endif /* TIMAGE_H_ */
