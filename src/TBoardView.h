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
	virtual void OnAppCreate();

	bool test = true;
public:

	std::string helpText;

	virtual void OnResize(int width, int height);
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
    void DrawPath(int color);
    void DrawSnake(double pos);

    virtual void OnClick(int x, int y);

    int x0,y0;
    int xx0,yy0;
    int xxm,yym;
	virtual void OnMomentumStart(int x, int y);
	virtual void OnMomentumMove(int x1, int y1);
	virtual void OnMomentumEnd(int x, int y);


    void closePopupBox();
    void showHelp();
    void showGameOverBox();

private:

    TPopupBox* myPopupBox;

	virtual void OnMenuKeyClick();
	virtual void OnBackKeyClick();


    void loadHelp();

    void SetColor(int color);
    void SetPattern(double x,double y, int r, int color);
    void SetPatternForSquare(int x, int y, int r);

    void DrawHeader();
    void DrawScore(double x, double y, int score);

    void DrawSquare(TPoint p);

    //double timeLinePos;
    bool animationOn = false;
    //bool appearanceNewBalls = false;
    //bool disappearanceBalls = false;
    //bool disAppearanceBalls = false;
	double ballSnakePos;
    //bool BallSnakeRun = false;
    bool isBallSelected = false;
   // bool needUpdateScore = true;
	TPoint selBall;
	TPoint destSquare;


	Ecore_Animator *JumpingAnimator;

	void RefreshGraphics();
	Ecore_Animator *animator;

    static constexpr const double animation_pause = 0.2;
    static constexpr const double animation_time = 0.4;

//	void startJumpingBallAnimator();
//	void deleteJumpingBallAnimator();
	void createMoveBallAnimator();
	void deleteMoveBallAnimator();

public:
	void ClearSnake();
	std::vector<TPoint> NewBalls;
	std::vector<TPoint> SnakeBalls;
	double tick;
	void jumpingBall();
	void moveBall(double pos);
	void afterMoveBall();
	void appearanceNewBall(double pos);
	void disappearanceLines(double pos);

	void NewGame();
};

#endif /* TBOARDVIEW_H_ */
