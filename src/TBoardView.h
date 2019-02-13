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
#include "MainModelView.h"
#include "TImage.h"
#include "TAnimator.h"

class TPopupBox;
class TLinesGame;
class TBoardView: public TDrawingView {
public:
	TBoardView();
	virtual ~TBoardView();

	MainModelView *modelView;

	bool test = true;
public:

	TImage *img;

	virtual void OnResize(int width, int height);


    TLinesGame* linesGame;

    void CalcViewMarkup();

    void DrawBoard();


   // void startShowAllBalls();

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


  //  void closePopupBox();
  //  void showGameOverBox();

private:

   // TPopupBox* myPopupBox;

	virtual void OnMenuKeyClick();
	virtual void OnBackKeyClick();


    void loadHelp();

    void SetColor(int color);
    void SetPattern(double x,double y, int r, int color);
    void SetPatternForSquare(int x, int y, int r);

    bool animationOn = false;

	double ballSnakePos;

    TBall destSquare;

    TAnimator animator;

	void RefreshGraphics();


    //static constexpr const double animation_pause = 0.2;
   // static constexpr const double animation_time = 0.4;


	void createMoveBallAnimator();
	void deleteMoveBallAnimator();

public:
//	void ClearSnake();
	//std::vector<TBall> NewBalls;
	std::vector<TBall> SnakeBalls;
	//double tick;
	//void jumpingBall();
	void moveBall(double pos);
//	void afterMoveBall();
	//void appearanceNewBall(double pos);
//	void disappearanceLines(double pos);

	//void appearanceNextBall(double pos);
	//void afterAppearanceNewBall();
	//void UpdateView();
	void DrawBoardWithBalls();
	void addNextBalls();

	void NewGame();
};

#endif /* TBOARDVIEW_H_ */
