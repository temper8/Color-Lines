/*
 * TAnimator.cpp
 *
 *  Created on: Feb 13, 2019
 *      Author: Alex
 */

#include "TAnimator.h"

#include "GameApp.h"
#include "MainModelView.h"


TAnimator::TAnimator() {
	// TODO Auto-generated constructor stub
	modelView = &GameApp::instance()->modelView;

	modelView->animator = this;

	linesGame = &GameApp::instance()->modelView.linesGame;

}

TAnimator::~TAnimator() {
	// TODO Auto-generated destructor stub
}

void TAnimator::Initialize(TImage *img){
	image = img;
	image->animator = this;
	//animator = ecore_animator_add([](void *data){((TImage *) data)->Refresh(); return EINA_TRUE;}, img);
	//ecore_animator_freeze(animator);

	selBall.x = 0;
	selBall.y = 0;
	image->Refresh();
}

void TAnimator::Freeze(){
	if (animator!=nullptr)
		ecore_animator_freeze(animator);
	if (timer != nullptr)
		ecore_timer_freeze(timer);
}

void TAnimator::Thaw(){
	if (animator!=nullptr)
		ecore_animator_thaw(animator);
	if (timer != nullptr)
		ecore_timer_thaw(timer);
}

void TAnimator::StartTimeLineAnimator(State s){
	state = s;
	ecore_animator_timeline_add (animation_time,  [](void *data, double pos){return ((TAnimator *) data)->Refresh(pos); }, this);
}

Eina_Bool TAnimator::Refresh(double pos){
   	Pos =pos;
   	image->Refresh();
    return EINA_TRUE;
}


void TAnimator::StartJumpingBall(int x, int y){
	if (state == State::JampingTheBall)
	{
		StopJumpingTheBall();
		image->JumpingBall(0.0);
	}

	selBall.x = x;
	selBall.y = y;
	selBall.color = 2;//linesGame->board[xx][yy];
	//if (!isBallSelected)

	//Thaw();
	isBallSelected = true;

	StartJumpingTheBall();
}

Eina_Bool TAnimator::OneJump(){
	state = State::JampingTheBall;
	animator = ecore_animator_timeline_add (jumping_time,  [](void *data, double pos){return ((TAnimator *) data)->Refresh(pos); }, this);
	ecore_timer_add(jumping_time/2, [](void *data){ ((TSoundPlayer *) data)->PlayFocus();return EINA_FALSE; },	&soundPlayer);

	return EINA_TRUE;
}

Eina_Bool TAnimator::StartJumpingTheBall(){
	OneJump();
	timer = ecore_timer_add(jumping_time, [](void *data){return ((TAnimator *) data)->OneJump(); },	this);
	return EINA_TRUE;
}

void TAnimator::StopJumpingTheBall(){
	if (timer != nullptr)
			ecore_timer_del(timer);
	if (animator!=nullptr)
		ecore_animator_del(animator);
}

void TAnimator::StartMoveBallAnimation(int x, int y){

	//Freeze();

    destBall.x = x;
    destBall.y = y;

	linesGame->initSearch(selBall);

	if (linesGame->searchPath(selBall,destBall) >0) {

		isBallSelected = false;
		image->SnakeBalls = linesGame->path;
		linesGame->path.clear();

		StopJumpingTheBall();

		StartTimeLineAnimator(State::SnakeAnimation);

		soundPlayer.PlayMove();

		ecore_timer_add(animation_time, [](void *data){((TAnimator *) data)->AfterMoveBall();  return EINA_FALSE;}, this);
	}
	else {
		soundPlayer.PlayWav("error.wav");
	}
}




void TAnimator::AfterMoveBall(){

	if (timer != nullptr)
			ecore_timer_del(timer);

	linesGame->board[destBall.x][destBall.y] = linesGame->board[selBall.x][selBall.y];
	linesGame->board[selBall.x][selBall.y] = 0;
	image->ClearSnake();
	if (linesGame->checkLines() == 0 )	{
			image->balls = linesGame->addNewBalls();

			StartTimeLineAnimator(State::NewBallAnimation);

			if (linesGame->gameOver()) {
				soundPlayer.PlayWav("finish.wav");
				ecore_timer_add(animation_time, [](void *data)	{ ((MainModelView *)data)->ShowGameOverBox(); return EINA_FALSE; }, modelView);
			}
			ecore_timer_add(animation_time+animation_delay, [](void *data)	{ ((TAnimator *)data)->AfterAppearanceNewBall(); return EINA_FALSE; }, this);

	}
	else {
		soundPlayer.PlayDestroy();
		StartTimeLineAnimator(State::DeleteBallsAnimation);

		ecore_timer_add(animation_time+animation_delay, [](void *data)	{ ((TAnimator *)data)->state = State::DefaultWithBalls; ((TAnimator *)data)->image->Refresh(); return EINA_FALSE; }, this);
	}
}

void TAnimator::AfterAppearanceNewBall(){

	if (linesGame->checkLines() > 0 )
	{
		soundPlayer.PlayDestroy();
		StartTimeLineAnimator(State::DeleteBallsAnimation);
		ecore_timer_add(animation_time+animation_delay, [](void *data)	{ ((TAnimator *)data)->AddNewBalls(); return EINA_FALSE; }, this);
	}
	else {
		AddNewBalls();
	}
}

void  TAnimator::AddNewBalls(){
	linesGame->addNextBalls();
	state = State::DefaultWithBalls;
	image->Refresh();
}


void TAnimator::DelayStartShowAllBalls(){
	StopJumpingTheBall();
	state = State::Default;
	image->Refresh();
	selBall.x = 0;
	selBall.y = 0;
	ecore_timer_add(animation_pause, [](void *data){((TAnimator *) data)->startShowAllBalls(); return EINA_FALSE;}, this);
}

void TAnimator::startShowAllBalls(){
    //NewBalls = linesGame->makeListBalls();
	image->balls = linesGame->board.getAllBalls();
	StartTimeLineAnimator(State::NewBallAnimation);
	ecore_timer_add(animation_time+animation_delay, [](void *data)	{  ((TAnimator *)data)->AfterAppearanceNewBall(); return EINA_FALSE; }, this);
}


