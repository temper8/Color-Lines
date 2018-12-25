/*
 * TImage.h
 *
 *  Created on: Dec 19, 2018
 *      Author: Alex
 */

#ifndef TIMAGE_H_
#define TIMAGE_H_


#include <cairo.h>

#include "TLinesGame.h"
#include "MainModelView.h"
#include "TGraphics2.h"

#include "TCairoGraphics.h"

class TImage: public TCairoGraphics {
public:
	TImage(Evas_Object *conform);
	virtual ~TImage();

	virtual void Paint();

	void LoadBgImage();
	cairo_surface_t *bg_image;

	void DrawRoundRectangle(double x, double y, double w, double h, double r);
	void DrawSquare(double x, double y);
	void SetPatternForSquare(int x, int y, int r);

	void SetColor(int color);
	void SetPattern(double x,double y, int radius, int color);
	void DrawBall(double x, double y, double r, int color);
	void FillBackgroud();

	//TCairoGraphics2 graphics;

//	Evas_Object *image;
//	Evas_Coord width;
//	Evas_Coord height;

	double squareSize;
	double left_margin,top_margin;
//	int myWidth, myHeight;

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
	void DrawBoardX(int translation);
	int xOffset = 0;
	void DrawSquare(TBall p);
    void DrawBall(double x, double y, int color);
    //void DrawBall(double x, double y, double r, int color);
    void DrawBall(TBall p, double r, int color);
    void DrawBall(TBall p, double r);

    bool semaphor = false;

    void DrawBalls();

    void DrawNextBalls();

	void appearanceNewBall(double pos);
	void disappearanceLines(double pos);
};

#endif /* TIMAGE_H_ */
