/*
 * TAnimator.h
 *
 *  Created on: Feb 13, 2019
 *      Author: Alex
 */

#ifndef TANIMATOR_H_
#define TANIMATOR_H_


#include "TSoundPlayer.h"

#include "TImage.h"

class MainModelView;
class TAnimator {
public:
	TAnimator();
	virtual ~TAnimator();

	Ecore_Animator *animator;

	MainModelView *modelView;
	TImage *image;
    TLinesGame* linesGame;

	void Initialize(TImage *img);
	void Freeze();
	void Thaw();

	void StartJumpingBall(int x, int y);
	Eina_Bool StartJumpingTheBall();
	Eina_Bool OneJump();
    void StopJumpingTheBall();
	void StartMoveBallAnimation(int x, int y);
	void AfterMoveBall();
	void AfterAppearanceNewBall();
	void startShowAllBalls();
	void DelayStartShowAllBalls();

    static constexpr const double animation_pause = 0.2;
    static constexpr const double animation_time = 0.4;
    static constexpr const double animation_delay = 0.1;
    static constexpr const double jumping_time = 0.6;

    enum class State
    {
        Default,
		DefaultWithBalls,
		JampingTheBall,
		Slipping,
		NewBallAnimation,
		DeleteBallsAnimation,
		SnakeAnimation
    };
    State state = State::Default;

    bool isBallSelected = false;
    TBall selBall;
    TBall destBall;


    double Pos;
    void StartTimeLineAnimator(State s);



    Eina_Bool Refresh(double pos);

    Ecore_Timer *timer = nullptr;
    TSoundPlayer soundPlayer;
    int tone_type = 0;
	Eina_Bool JumpBip();
};

#endif /* TANIMATOR_H_ */
