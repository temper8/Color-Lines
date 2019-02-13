/*
 * TAnimator.cpp
 *
 *  Created on: Feb 13, 2019
 *      Author: Alex
 */

#include "TAnimator.h"

TAnimator::TAnimator() {
	// TODO Auto-generated constructor stub

}

TAnimator::~TAnimator() {
	// TODO Auto-generated destructor stub
}


void TAnimator::Initialize(TImage *img){
	image = img;
	animator = ecore_animator_add([](void *data){((TImage *) data)->Refresh(); return EINA_TRUE;}, img);
	ecore_animator_freeze(animator);
}

void TAnimator::Freeze(){
	ecore_animator_freeze(animator);
}

void TAnimator::Thaw(){
	ecore_animator_thaw(animator);
}

void TAnimator::StartJumpingBall(int x, int y){
	image->selBall.x = x;
	image->selBall.y = y;
	image->selBall.color = 2;//linesGame->board[xx][yy];
	image->isBallSelected = true;
}
