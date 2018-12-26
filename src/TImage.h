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

public:
    enum class State
    {
        Default,
		Slipping,
		NewBallAnimation,
		DelBallAnimation,
		SnakeAnimation
    };
    State state = State::Default;

	void LoadBgImage();
	cairo_surface_t *bg_image;

	void DrawRoundRectangle(double x, double y, double w, double h, double r);
	void DrawSquare(double x, double y);
	void SetPatternForSquare(int x, int y, int r);

	void SetColor(int color);
	void SetPattern(double x,double y, int radius, int color);
	void DrawBall(double x, double y, double r, int color);
	void FillBackgroud();
	void DrawHeaderBG();
	void DrawScore(double x, double y, int score);
	void DrawScore(double x, double y, const char* caption, int score, int aling);


	int xTranslation = 0;
	double squareSize;
	double left_margin,top_margin;

	MainModelView *modelView;
    TLinesGame* linesGame;

    std::vector<TBall> balls;
	//std::vector<TBall> NewBalls;
	std::vector<TBall> SnakeBalls;

    TBall selBall;
    TBall destSquare;

    static constexpr const double animation_pause = 0.2;
    static constexpr const double animation_time = 0.4;

    bool isBallSelected = false;
	double tick = 0;
	double animationPos = 0;
	void AnimationRefresh(double pos);
	void JumpingBall();
	void StartMoveBallAnimation(TBall destSquare);
	void AfterMoveBall();
	void ClearSnake();
	void DrawSnake(double pos);

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

	void AppearanceNewBall(double pos);
	void disappearanceLines(double pos);
	void AfterAppearanceNewBall();
};

#endif /* TIMAGE_H_ */
