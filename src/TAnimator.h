/*
 * TAnimator.h
 *
 *  Created on: Feb 13, 2019
 *      Author: Alex
 */

#ifndef TANIMATOR_H_
#define TANIMATOR_H_
#include "TImage.h"

class TAnimator {
public:
	TAnimator();
	virtual ~TAnimator();

	Ecore_Animator *animator;

	TImage *image;
    TLinesGame* linesGame;

	void Initialize(TImage *img);
	void Freeze();
	void Thaw();

	void StartJumpingBall(int x, int y);
	void StartMoveBallAnimation(int x, int y);
	void AfterMoveBall();

    static constexpr const double animation_pause = 0.2;
    static constexpr const double animation_time = 0.4;

    enum class State
    {
        Default,
		Slipping,
		NewBallAnimation,
		DelBallAnimation,
		SnakeAnimation
    };
    State state = State::Default;

    bool isBallSelected = false;
    TBall selBall;


    double Pos;
    void Refresh(double pos);
};

#endif /* TANIMATOR_H_ */
