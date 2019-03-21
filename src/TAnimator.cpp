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
	animator = ecore_animator_add([](void *data){((TImage *) data)->Refresh(); return EINA_TRUE;}, img);
	ecore_animator_freeze(animator);

	selBall.x = 0;
	selBall.y = 0;
	image->Refresh();
}

void TAnimator::Freeze(){
	ecore_animator_freeze(animator);
}

void TAnimator::Thaw(){
	ecore_animator_thaw(animator);
}

void TAnimator::StartTimeLine(State s){
	state = s;
	ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TAnimator *) data)->Refresh(pos); return EINA_TRUE;}, this);
}

void TAnimator::Refresh(double pos){
   	Pos =pos;
   	image->Refresh();
}


void TAnimator::StartJumpingBall(int x, int y){
	selBall.x = x;
	selBall.y = y;
	selBall.color = 2;//linesGame->board[xx][yy];
	if (!isBallSelected)
		ecore_timer_add(1.0, [](void *data){return ((TAnimator *) data)->JumpBip(); }, this);
	isBallSelected = true;
	Thaw();
	soundPlayer.PlayWav();
}

Eina_Bool TAnimator::JumpBip(){

	soundPlayer.PlayWav();

	if (isBallSelected) return EINA_TRUE;

	 return EINA_FALSE;
}

void TAnimator::StartMoveBallAnimation(int x, int y){
    //TBall destSquare(x,y);
	Freeze();
	//state = State::Default;

    destBall.x = x;
    destBall.y = y;
	isBallSelected = false;
	linesGame->initSearch(selBall);

	if (linesGame->searchPath(selBall,destBall) >0) {

		image->SnakeBalls = linesGame->path;
		linesGame->path.clear();

		StartTimeLine(State::SnakeAnimation);
		ecore_timer_add(animation_time+animation_delay, [](void *data){((TAnimator *) data)->AfterMoveBall();  return EINA_FALSE;}, this);
	}
}

void TAnimator::AfterMoveBall(){
	linesGame->board[destBall.x][destBall.y] = linesGame->board[selBall.x][selBall.y];
	linesGame->board[selBall.x][selBall.y] = 0;
	image->ClearSnake();
	if (linesGame->checkLines() == 0 )	{
			image->balls = linesGame->addNewBalls();

			StartTimeLine(State::NewBallAnimation);

			if (linesGame->gameOver()) {
				ecore_timer_add(animation_time, [](void *data)	{ ((MainModelView *)data)->ShowGameOverBox(); return EINA_FALSE; }, modelView);
			}
			ecore_timer_add(animation_time+animation_delay, [](void *data)	{ ((TAnimator *)data)->AfterAppearanceNewBall(); return EINA_FALSE; }, this);

	}
	else {

		StartTimeLine(State::DeleteBallsAnimation);

		ecore_timer_add(animation_time+animation_delay, [](void *data)	{ ((TAnimator *)data)->state = State::DefaultWithBalls; ((TAnimator *)data)->image->Refresh(); return EINA_FALSE; }, this);
	}
	//img->DrawHeader();
}

void TAnimator::AfterAppearanceNewBall(){

	if (linesGame->checkLines() > 0 )
	{
		StartTimeLine(State::DeleteBallsAnimation);
	}
	linesGame->addNextBalls();
	state = State::DefaultWithBalls;
	image->Refresh();
}

void TAnimator::DelayStartShowAllBalls(){
	state = State::Default;
	image->Refresh();
	selBall.x = 0;
	selBall.y = 0;
	ecore_timer_add(animation_pause, [](void *data){((TAnimator *) data)->startShowAllBalls(); return EINA_FALSE;}, this);
}

void TAnimator::startShowAllBalls(){
    //NewBalls = linesGame->makeListBalls();
	image->balls = linesGame->board.getAllBalls();
	StartTimeLine(State::NewBallAnimation);
	ecore_timer_add(animation_time+animation_delay, [](void *data)	{  ((TAnimator *)data)->AfterAppearanceNewBall(); return EINA_FALSE; }, this);
}


