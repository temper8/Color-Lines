/*
 * TBoardView.h
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#ifndef TBOARDVIEW_H_
#define TBOARDVIEW_H_

#include "TDrawingView.h"
#include "TLinesGame.h"

class TPopupBox;
class TLinesGame;
class TBoardView: public TDrawingView {
public:
	TBoardView();
	virtual ~TBoardView();

public:

	std::string helpText;

	virtual void CairoDrawing();

	double squareSize;
	double left_margin,top_margin;

    TLinesGame* linesGame;

    void CalcViewMarkup();

    void DrawBoard();

    void DrawBall(double x, double y, int color);
    void DrawBall(double x, double y, double r, int color);
    void DrawBall(TPoint p, double r, int color);
    void DrawBall(TPoint p, double r);

    void AddRandomBalls();

    void DrawBalls();

    void DrawPath();
    void DrawPath(double pos);

    virtual void OnClick(int x, int y);

    void closePopupBox();
    void showHelp();

private:

    TPopupBox* myPopupBox;
	virtual void callbackMore();
	virtual void callbackBack();


    void loadHelp();
    void SetColor(int color);
    void SetPattern(double x,double y, int r, int color);
    void SetPatternForSquare(int x, int y, int r);

    void DrawHeader();
    void DrawScore(double x, double y, int score);

    void DrawSquare(TPoint p);


	TPoint selBall;
	TPoint destSquare;

	void StartJumpingBallAnimator();
	void DeleteJumpingBallAnimator();
	void CreateMoveBallAnimator();
	void DeleteMoveBallAnimator();
	Ecore_Animator *JumpingAnimator;

public:
	std::vector<TPoint> NewBalls;
	double tick;
	void JumpingBall();
	void MoveBall(double pos);
	void OnEndMoveBall();
	void AppearanceNewBall(double pos);
	void DisappearanceLines(double pos);

	void NewGame();
};

#endif /* TBOARDVIEW_H_ */
