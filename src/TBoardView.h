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
    void DrawBall(double x, double y, double r, int color);
    void DrawBall(TPoint p, double r, int color);
    void DrawBall(TPoint p, double r);
    void DrawRoundRectangle(double x, double y, double w, double h, double r);
    void AddRandomBalls();
    void Test7Colors();
    void DrawBalls();
    void DrawGradienBall();
    void DrawSF();
    void DrawPath();
    void DrawPath(double pos);
    virtual void OnClick(int x, int y);

private:
    void SetColor(int color);
    void SetPattern(double x,double y, int r, int color);
    void SetPatternForSquare(int x, int y, int r);

    void DrawHeader();

    void DrawSquare(double x, double y);
    void DrawSquare(TPoint p);


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
	std::vector<TPoint> NewBalls;
	double tick;
	void RefreshBall();
	void MoveBall(double pos);
	void OnEndMoveBall();
	void AppearanceNewBall(double pos);
	void DisappearanceLines(double pos);
};

#endif /* TBOARDVIEW_H_ */
