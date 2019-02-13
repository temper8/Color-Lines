/*
 * TAnimator.cpp
 *
 *  Created on: Feb 13, 2019
 *      Author: Alex
 */

#include "TAnimator.h"
#include "TApp.h"
#include "MainModelView.h"

TAnimator::TAnimator() {
	// TODO Auto-generated constructor stub
	modelView = &TApp::instance()->modelView;


	linesGame = &TApp::instance()->modelView.linesGame;
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
}

void TAnimator::Freeze(){
	ecore_animator_freeze(animator);
}

void TAnimator::Thaw(){
	ecore_animator_thaw(animator);
}

void TAnimator::Refresh(double pos){
   	Pos =pos;
   	image->Refresh();
}


void TAnimator::StartJumpingBall(int x, int y){
	selBall.x = x;
	selBall.y = y;
	selBall.color = 2;//linesGame->board[xx][yy];
	isBallSelected = true;
}

void TAnimator::StartMoveBallAnimation(int x, int y){
    TBall destSquare(x,y);
	isBallSelected = false;
	linesGame->initSearch(selBall);

	if (linesGame->searchPath(selBall,destSquare) >0) {
		linesGame->board[destSquare.x][destSquare.y] = linesGame->board[selBall.x][selBall.y];
		linesGame->board[selBall.x][selBall.y] = 0;
		image->SnakeBalls = linesGame->path;
		linesGame->path.clear();


		state = State::SnakeAnimation;
		ecore_animator_timeline_add (animation_time, [](void *data, double pos){((TAnimator *) data)->Refresh(pos); return EINA_TRUE;}, this);
		ecore_timer_add(animation_time, [](void *data){((TAnimator *) data)->AfterMoveBall();  return EINA_FALSE;}, this);
	}
}

void TAnimator::AfterMoveBall(){
	image->ClearSnake();
	if (linesGame->checkLines() == 0 )	{
			image->balls = linesGame->addNewBalls();
			state = State::NewBallAnimation;
			ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TAnimator *) data)->Refresh(pos); return EINA_TRUE;}, this);
			if (linesGame->gameOver()) {
				ecore_timer_add(animation_time, [](void *data)	{ ((MainModelView *)data)->ShowGameOverBox(); return EINA_FALSE; }, modelView);
			}
			ecore_timer_add(animation_time, [](void *data)	{ ((TAnimator *)data)->AfterAppearanceNewBall(); return EINA_FALSE; }, this);

	}
	else {
		state = State::DelBallAnimation;
		ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TAnimator *) data)->Refresh(pos); return EINA_TRUE;}, this);

		ecore_timer_add(animation_time, [](void *data)	{ ((TAnimator *)data)->state = State::Default; ((TAnimator *)data)->image->Refresh(); return EINA_FALSE; }, this);
	}

}

void TAnimator::AfterAppearanceNewBall(){

	if (linesGame->checkLines() > 0 )
	{
		state = State::DelBallAnimation;
		ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TAnimator *) data)->Refresh(pos); return EINA_TRUE;}, this);
	}
	linesGame->addNextBalls();
	state = State::Default;
	image->Refresh();
}

