/*
 * TBoardView.h
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#ifndef TBOARDVIEW_H_
#define TBOARDVIEW_H_

#include "TDrawingView.h"
#include "TLinesBoard.h"

class TLinesBoard;
class TBoardView: public TDrawingView {
public:
	TBoardView();
	virtual ~TBoardView();

public:
	virtual void CairoDrawing();

    int squareSize;
    int left_margin,top_margin;

    TLinesBoard* linesBoard;
    void DrawBoard();
    void DrawTopText();
    void DrawBall(double x, double y, int color);
    void Test7Colors();
    void DrawBalls();
    void DrawGradienBall();
    void DrawSF();
    void DrawPathBall(int x, int y, int color);
    void DrawPath();
    virtual void OnClick(int x, int y);

private:
    void SetColor(int color);
    void SetPattern(double x,double y, int r, int color);
    void SetPatternForSquare(int x, int y, int r);
    void DrawSquare(double x, double y);
    int mx,my;
	TPoint selBall;
	TPoint destSquare;

	void CreateAnimator();
	void DeleteAnimator();
	void CreateMoveBallAnimator();
	void DeleteMoveBallAnimator();
	Ecore_Animator *animator;
	cairo_surface_t *bg_image;
public:
	double tick;
	void RefreshBall();
	void MoveBall(double pos);
};

#endif /* TBOARDVIEW_H_ */
