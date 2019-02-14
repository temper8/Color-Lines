/*
 * TBoardView.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#include "TBoardView.h"

#include <cmath>

#include <fstream>
#include <sstream>      // std::stringstream, std::stringbuf

#include "TPopupBox\TExitPopupBox.h"
#include "TPopupBox\TMenuPopupBox.h"
#include "TPopupBox\TInfoBox.h"
#include "TPopupBox\TGameOverBox.h"

#include "TApp.h"

TBoardView::TBoardView() {
	// TODO Auto-generated constructor stub

	modelView = &TApp::instance()->modelView;

	linesGame = &modelView->linesGame;

	img = new TImage(conform);


	AttachGesture(img->GetImage());

	CreateContent();


	animator.Initialize(img);
	animator.DelayStartShowAllBalls();
}

TBoardView::~TBoardView() {
	// TODO Auto-generated destructor stub
}


void TBoardView::OnResize(int width, int height){
	if ((width < 2)||(height < 2)) return;
	animator.Freeze();
	img->Initialize(width, height);
	img->Refresh();
	animator.Thaw();
}

void TBoardView::NewGame(){
	linesGame->newGame();

	animator.DelayStartShowAllBalls();
	//ecore_timer_add(animation_pause, [](void *data){((TBoardView *) data)->startShowAllBalls(); return EINA_FALSE;}, this);
}




void TBoardView::OnMenuKeyClick(){
	modelView->showMenu();
	/*
	if (myPopupBox!=NULL) closePopupBox();
	myPopupBox = new TMenuPopupBox({"Continue", "New Game", "Game Rules","Exit"});
	myPopupBox->OnBtnClick = [this](int tag) {
										closePopupBox();
										switch(tag) {
											case 1: break;
											case 2: NewGame(); break;
											case 3: showHelp(); break;
											case 4: ui_app_exit(); break;
											}
										};
	myPopupBox->show();
	*/
}

void TBoardView::OnBackKeyClick(){

}





void TBoardView::OnClick(int x, int y) {
	//if (BallSnakeRun) return;
	int xx =(x-img->left_margin) / img->squareSize + 1;
	int yy =(y-img->top_margin) / img->squareSize + 1;

	if (linesGame->OutOfBoundary(xx, yy)) return;

    if (linesGame->board[xx][yy] > 0) {
    	animator.StartJumpingBall(xx,yy);
      //  startJumpingBallAnimator();
    }
    else {
    	if (animator.isBallSelected)
    		animator.StartMoveBallAnimation(xx,yy);
    }
};

void TBoardView::OnMomentumStart(int x, int y) {
	//if (BallSnakeRun ) return;
/*
	x0 = x;
	y0 = y;
	int xx =(x-img->left_margin) / img->squareSize + 1;
	int yy =(y-img->top_margin) / img->squareSize + 1;
	xx0=xx;
	yy0=yy;
	xxm=xx;
	yym=yy;
	if (linesGame->OutOfBoundary(xx, yy)) return;

    if (linesGame->board[xx][yy] > 0) {
    //	img->graphics.tx = x;
    //	img->graphics.ty = y;
    //	img->graphics.ring = linesGame->board[xx][yy];
    //	img->graphics.goodPath = true;
    	animator.selBall.x = xx;
    	animator.selBall.y = yy;
    	animator.selBall.color = linesGame->board[xx][yy];
    	animator.isBallSelected = true;
    	linesGame->initSearch(animator.selBall);
    }

*/
};

void TBoardView::OnMomentumMove(int x, int y) {
	//dlog_print(DLOG_DEBUG, LOG_TAG, "TBoardView::OnMomentumMove x:%d y:%d", x, y);

	//img->DrawBoardX(x-x0);

//	img->graphics.tx = x;
//	img->graphics.ty = y;
/*
	int xx =(x-img->left_margin) / img->squareSize + 1;
	int yy =(y-img->top_margin) / img->squareSize + 1;

//	if ((xxm == xx)&&(yym==yy))		return;


	xxm=xx;
	yym=yy;
	destSquare.x = xx;
	destSquare.y = yy;

	if (animator.isBallSelected)  {
		ClearPath();
		if (linesGame->OutOfBoundary(xx, yy)) {
		//	img->graphics.goodPath = false;
			return;
		}

		linesGame->initSearch(animator.selBall);

		if (linesGame->board[xx][yy]>0)	{
			//img->graphics.goodPath = false;
			linesGame->searchClosestPath(animator.selBall,destSquare);
			DrawPath(0);
			return;
		}

        if (linesGame->searchPath(animator.selBall,destSquare) >0) {
        	// DrawPath(img->graphics.ring);
        	// img->graphics.goodPath = true;
        }
        else{
        	//img->graphics.goodPath = false;
        	linesGame->searchClosestPath(animator.selBall,destSquare);
        	DrawPath(0);
        }

	}
	else
	{
		animator.Freeze();

		//img->DrawBoardX(x-x0);
		img->xTranslation = x- x0;
		animator.state = TAnimator::State::Slipping;
		img->Refresh();
	}
*/
};

void TBoardView::OnMomentumEnd(int x, int y) {
/*
	if (animator.state == TAnimator::State::Slipping)
	{
		linesGame->OffsetBoard(img->xOffset);

		img->xOffset = 0;
		img->xTranslation = 0;
		animator.state = TAnimator::State::Default;
		img->Refresh();
		animator.Thaw();
		return;
	}

	//img->graphics.ring =0;
	//img->graphics.goodPath = false;
	 int xx =(x-img->left_margin) / img->squareSize + 1;
	 int yy =(y-img->top_margin) / img->squareSize + 1;

	 if ((xx0 == xx)&&(yy0==yy))	return;
	 ClearPath();
	 linesGame->path.clear();

	if (animator.isBallSelected)  {
			animator.isBallSelected = false;
			if (linesGame->OutOfBoundary(xx, yy)||(linesGame->board[xx][yy]>0)||animationOn){
				img->DrawBall(animator.selBall,1);
				return;
			}

			animator.StartMoveBallAnimation(xx,yy);
	}
	*/
};



// animation



void TBoardView::moveBall(double pos) {
	DrawPath(pos);
	//img->graphics.Flush();
}

void TBoardView::createMoveBallAnimator(){
	/*
	linesGame->board[destSquare.x][destSquare.y] = linesGame->board[img->selBall.x][img->selBall.y];
	linesGame->board[img->selBall.x][img->selBall.y] = 0;
	SnakeBalls = linesGame->path;
	linesGame->path.clear();
	//ecore_animator_timeline_add (animation_time, [](void *data, double pos){((TBoardView *) data)->moveBall(pos); return EINA_TRUE;}, this);
	//ecore_animator_timeline_add (animation_time, [](void *data, double pos){((TBoardView *) data)->DrawPath(pos); return EINA_TRUE;}, this);
	ballSnakePos = 0;
	animationOn = true;
	ecore_animator_timeline_add (animation_time, [](void *data, double pos){((TBoardView *) data)->DrawSnake(pos); return EINA_TRUE;}, this);

//	ecore_animator_timeline_add (animation_time, [ballSnakePos](void *data, double pos){ ballSnakePos = pos; return EINA_TRUE;}, this);
	ecore_timer_add(animation_time, [](void *data){((TBoardView *) data)->afterMoveBall();  return EINA_FALSE;}, this);
	*/
}
/*
void TBoardView::deleteMoveBallAnimator(){

}

Eina_Bool appearance_new_ball(void *data, double pos)
{
   TBoardView *bv = (TBoardView *) data;
   bv->appearanceNewBall(pos);
   return EINA_TRUE;
}
*/
/*
Eina_Bool disappearance_lines(void *data, double pos)
{
   TBoardView *bv = (TBoardView *) data;
   bv->disappearanceLines(pos);
   return EINA_TRUE;
}


void TBoardView::afterMoveBall(){
	ClearSnake();
	if (linesGame->checkLines() == 0 )	{
			//NewBalls = linesGame->addNewBalls();
			img->balls = linesGame->addNewBalls();
			//ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TImage *) data)->appearanceNewBall(pos); return EINA_TRUE;}, img);
			if (linesGame->gameOver()) {
			//	ecore_timer_add(animation_time, [](void *data)	{ ((TBoardView *)data)->showGameOverBox(); return EINA_FALSE; }, this);
			}
			ecore_timer_add(animation_time, [](void *data)	{ ((TBoardView *)data)->afterAppearanceNewBall(); return EINA_FALSE; }, this);

	}
	else {
		ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TImage *) data)->disappearanceLines(pos); return EINA_TRUE;}, img);
		ecore_timer_add(animation_time, [](void *data)	{ ((TImage *)data)->DrawNextBalls(); return EINA_FALSE; }, img);

	}

	img->DrawHeader();
}

void TBoardView::afterAppearanceNewBall(){
	if (linesGame->checkLines() > 0 )
		ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TImage *) data)->disappearanceLines(pos); return EINA_TRUE;}, img);
	animationOn = false;
	linesGame->addNextBalls();
	//UpdateView();
}


*/

void TBoardView::ClearPath(){
	if (linesGame->path.size()>0) {
		//TPoint p = linesGame->path.front();
		//int color =  linesGame->board[p.x][p.y];
		for ( TBall p : linesGame->path ){
			//double xx = p.x*squareSize - squareSize / 2 + left_margin;
			//double yy = p.y*squareSize - squareSize / 2 + top_margin;
			//graphics.DrawBall(xx, yy,  0.4, p.color);
			img->DrawSquare(p);
			if (linesGame->board[p.x][p.y] > 0)
				img->DrawBall(p,1.0,linesGame->board[p.x][p.y]);
		}

	}
}
void TBoardView::DrawPath(int color){
	if (linesGame->path.size()>0) {
		//TPoint p = linesGame->path.front();
		//int color =  linesGame->board[p.x][p.y];
		for ( TBall p : linesGame->path ){
			double xx = p.x*img->squareSize - img->squareSize / 2 + img->left_margin;
			double yy = p.y*img->squareSize - img->squareSize / 2 + img->top_margin;
		//	img->graphics.DrawBall(xx, yy,  0.4, color);
		}

	}
}

void TBoardView::DrawSnake(double pos){
	if (SnakeBalls.size() == 0) return;
	double dx = M_PI/(SnakeBalls.size()-1);
	for (int i = 0; i<SnakeBalls.size(); i++ ) {
		TBall p  =  SnakeBalls[i];

		img->DrawSquare(p);

		double r = cos(dx*i - M_PI*(1-1.5*pos));
		if (r<0) r = 0.0; else r = 0.5*r;

		img->DrawBall(p, r, p.color);
	}
	if (pos>0.5) {
		TBall p = SnakeBalls.front();
		img->DrawBall(p, 1, p.color);
	}

}


