/*
 * TBoardView.h
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#ifndef TBOARDVIEW_H_
#define TBOARDVIEW_H_

#include <string>

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

    void startShowAllBalls();

    void DrawBalls();

    void ClearPath();
    void DrawPath();
    void DrawPath(double pos);

    virtual void OnClick(int x, int y);

    int x0,y0;
	virtual void OnMomentumStart(int x, int y);
	virtual void OnMomentumMove(int x1, int y1);
	virtual void OnMomentumEnd(int x, int y);



	virtual void OnLineStart(int x, int y);
	virtual void OnLineMove(int x1, int y1, int x2, int y2);
	virtual void OnLineEnd(int x, int y);
	virtual void OnLineAbort(int x, int y);

    void closePopupBox();
    void showHelp();
    void showGameOverBox();

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


	Ecore_Animator *JumpingAnimator;

    static constexpr const double animation_pause = 0.5;
    static constexpr const double animation_time = 1.0;

	void startJumpingBallAnimator();
	void deleteJumpingBallAnimator();
	void createMoveBallAnimator();
	void deleteMoveBallAnimator();

public:
	std::vector<TPoint> NewBalls;
	double tick;
	void jumpingBall();
	void moveBall(double pos);
	void afterMoveBall();
	void appearanceNewBall(double pos);
	void disappearanceLines(double pos);

	void NewGame();
};

#endif /* TBOARDVIEW_H_ */
