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

TBoardView::TBoardView(): myPopupBox(NULL) {
	// TODO Auto-generated constructor stub

	modelView = &TApp::instance()->modelView;

	linesGame = &modelView->linesGame;
	//linesBoard->initRandom();


	img = new TImage(conform);
	img->selBall.x = 0;
	img->selBall.y = 0;

	AttachGesture(img->image);

	CreateContent();


	animator = ecore_animator_add([](void *data){((TImage *) data)->Flush(); return EINA_TRUE;}, img);
	ecore_animator_freeze(animator);
	ecore_timer_add(animation_pause, [](void *data){((TBoardView *) data)->startShowAllBalls(); return EINA_FALSE;}, this);
}

TBoardView::~TBoardView() {
	// TODO Auto-generated destructor stub
}


void TBoardView::OnResize(int width, int height){
	if ((width < 2)||(height < 2)) return;
	ecore_animator_freeze(animator);
	//TDrawingView::OnResize(width, height);
	img->Init(width, height);
	ecore_animator_thaw(animator);
}

void TBoardView::NewGame(){
	linesGame->newGame();
	img->selBall.x = 0;
	img->selBall.y = 0;
	img->CairoDrawing();
	ecore_timer_add(animation_pause, [](void *data){((TBoardView *) data)->startShowAllBalls(); return EINA_FALSE;}, this);
}



void TBoardView::closePopupBox(){
	delete myPopupBox;
	myPopupBox = NULL;
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
	if (myPopupBox!=NULL) closePopupBox();
	myPopupBox = new TExitPopupBox();
	myPopupBox->OnBtnClick = [this](int tag) { if (tag==1) ui_app_exit(); };
	myPopupBox->show();
}


void TBoardView::showGameOverBox(){
	myPopupBox = new TGameOverBox();
	myPopupBox->OnBtnClick = [this](int tag) {closePopupBox(); if (tag==2) NewGame(); else ui_app_exit(); };
	myPopupBox->show();
}


void TBoardView::OnClick(int x, int y) {
	//if (BallSnakeRun) return;
	int xx =(x-img->left_margin) / img->squareSize + 1;
	int yy =(y-img->top_margin) / img->squareSize + 1;

	if (linesGame->OutOfBoundary(xx, yy)) return;

    if (linesGame->board[xx][yy] > 0) {
    	img->selBall.x = xx;
    	img->selBall.y = yy;
    	img->selBall.color = linesGame->board[xx][yy];
    	img->isBallSelected = true;
       // startJumpingBallAnimator();
    }
    else {
    	if (img->isBallSelected)  {
    		img->isBallSelected = false;

    		destSquare.x = xx;
    		destSquare.y = yy;

    		linesGame->initSearch(img->selBall);

            if (linesGame->searchPath(img->selBall,destSquare) >0) {
            	 createMoveBallAnimator();

            }


    	}

    }
};

void TBoardView::OnMomentumStart(int x, int y) {
	//if (BallSnakeRun ) return;
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
    	img->graphics.tx = x;
    	img->graphics.ty = y;
    	img->graphics.ring = linesGame->board[xx][yy];
    	img->graphics.goodPath = true;
    	img->selBall.x = xx;
    	img->selBall.y = yy;
    	img->selBall.color = linesGame->board[xx][yy];
    	img->isBallSelected = true;
    	linesGame->initSearch(img->selBall);
    }
};

void TBoardView::OnMomentumMove(int x, int y) {
	//dlog_print(DLOG_DEBUG, LOG_TAG, "TBoardView::OnMomentumMove x:%d y:%d", x, y);
	img->graphics.tx = x;
	img->graphics.ty = y;

	int xx =(x-img->left_margin) / img->squareSize + 1;
	int yy =(y-img->top_margin) / img->squareSize + 1;

	if ((xxm == xx)&&(yym==yy))		return;


	xxm=xx;
	yym=yy;
	destSquare.x = xx;
	destSquare.y = yy;

	if (img->isBallSelected)  {
		ClearPath();
		if (linesGame->OutOfBoundary(xx, yy)) {
			img->graphics.goodPath = false;
			return;
		}

		linesGame->initSearch(img->selBall);

		if (linesGame->board[xx][yy]>0)	{
			img->graphics.goodPath = false;
			linesGame->searchClosestPath(img->selBall,destSquare);
			DrawPath(0);
			return;
		}

        if (linesGame->searchPath(img->selBall,destSquare) >0) {
        	 DrawPath(img->graphics.ring);
        	 img->graphics.goodPath = true;
        }
        else{
        	img->graphics.goodPath = false;
        	linesGame->searchClosestPath(img->selBall,destSquare);
        	DrawPath(0);
        }

	}

};

void TBoardView::OnMomentumEnd(int x, int y) {

	img->graphics.ring =0;
	img->graphics.goodPath = false;
	 int xx =(x-img->left_margin) / img->squareSize + 1;
	 int yy =(y-img->top_margin) / img->squareSize + 1;

	 if ((xx0 == xx)&&(yy0==yy))	return;
	 ClearPath();
	 linesGame->path.clear();

	if (img->isBallSelected)  {
			img->isBallSelected = false;
			if (linesGame->OutOfBoundary(xx, yy)||(linesGame->board[xx][yy]>0)||animationOn){
				img->DrawBall(img->selBall,1);
				return;
			}

			destSquare.x = xx;
			destSquare.y = yy;
			linesGame->initSearch(img->selBall);

			if (linesGame->searchPath(img->selBall,destSquare) >0) {
				createMoveBallAnimator();
			}
	}
};



// animation

void TBoardView::RefreshGraphics(){

}




void TBoardView::moveBall(double pos) {
	DrawPath(pos);
	img->graphics.Flush();
}

void TBoardView::createMoveBallAnimator(){
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
*/

void TBoardView::afterMoveBall(){
	ClearSnake();
	if (linesGame->checkLines() == 0 )	{
			//NewBalls = linesGame->addNewBalls();
			img->balls = linesGame->addNewBalls();
			ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TImage *) data)->appearanceNewBall(pos); return EINA_TRUE;}, img);
			if (linesGame->gameOver()) {
				ecore_timer_add(animation_time, [](void *data)	{ ((TBoardView *)data)->showGameOverBox(); return EINA_FALSE; }, this);
			}
			ecore_timer_add(animation_time, [](void *data)	{ ((TBoardView *)data)->afterAppearanceNewBall(); return EINA_FALSE; }, this);

	}
	else {
		ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TBoardView *) data)->disappearanceLines(pos); return EINA_TRUE;}, this);
		ecore_timer_add(animation_time, [](void *data)	{ ((TBoardView *)data)->DrawNextBalls(); return EINA_FALSE; }, this);

	}

	//DrawHeader();
}

void TBoardView::afterAppearanceNewBall(){
	if (linesGame->checkLines() > 0 )
		ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TBoardView *) data)->disappearanceLines(pos); return EINA_TRUE;}, this);
	animationOn = false;
	linesGame->addNextBalls();
	//UpdateView();

}
void TBoardView::startShowAllBalls(){
    //NewBalls = linesGame->makeListBalls();
	img->balls = linesGame->makeListBalls();
    animationOn = true;
	ecore_animator_timeline_add (animation_time, [](void *data, double pos){((TImage *) data)->appearanceNewBall(pos); return EINA_TRUE;}, img);
//	ecore_timer_add(animation_time, [](void *data)	{ ((TBoardView *)data)->animationOn = false; ((TBoardView *)data)->DrawNextBalls(); return EINA_FALSE; }, this);
}
/*
void TBoardView::appearanceNextBall(double pos) {
	for ( TBall p : linesGame->nextBalls )
		DrawBall(p,  pos);
}

void TBoardView::appearanceNewBall(double pos) {
	for ( TBall p : NewBalls )
		DrawBall(p,  pos);
}
*/
void TBoardView::disappearanceLines(double pos){
	double r = 0.95 - pos;
	if (r < 0) r = 0;
	for ( TBall p : linesGame->clearBalls ){
		img->DrawSquare(p);
	//	DrawBall(p,  r);
	}
}



/*
void TBoardView::DrawBalls() {
	for(int i=1; i<= linesGame->sizeX; i++)
	  for(int j=1; j<= linesGame->sizeY; j++){
			double x = i*squareSize - squareSize / 2 + left_margin;
			double y = j*squareSize - squareSize / 2 + top_margin;
			DrawBall(x,y,linesGame->board[i][j]);
	  }
}

void TBoardView::DrawSquare(TBall p){
	double x = (p.x-1)*squareSize  + left_margin;
	double y = (p.y-1)*squareSize  + top_margin;
	img->graphics.DrawSquare(x, y);
}

void TBoardView::CalcViewMarkup(){

	double BoardWidth = myWidth - 60;

	left_margin = ( myWidth - BoardWidth)/2;

	squareSize = BoardWidth / linesGame->sizeX;
	img->graphics.squareSize = squareSize;

	double BoardHeight = squareSize * linesGame->sizeY;
	top_margin = ( myHeight - BoardHeight)/2;
}
*/
/*
void TBoardView::DrawBoardWithBalls(){

	for (int x = 0; x< linesGame->sizeX; x++)
	for (int y = 0; y< linesGame->sizeY; y++) {
			double xx = x*squareSize  + left_margin;
			double yy = y*squareSize  + top_margin ;
			img->graphics.DrawSquare(xx, yy);
			int i = x + 1;
			int j = y +1;
			if (linesGame->board[i][j]>0){
				double xx = i*squareSize - squareSize / 2 + left_margin;
				double yy = j*squareSize - squareSize / 2 + top_margin;
				DrawBall(xx,yy,linesGame->board[i][j]);
			}
		}
}

void TBoardView::DrawBoard(){

	for (int x = 0; x< linesGame->sizeX; x++)
		for (int y = 0; y< linesGame->sizeY; y++) {
			double xx = x*squareSize  + left_margin;
			double yy = y*squareSize  + top_margin ;
			img->graphics.DrawSquare(xx, yy);
		}
}

*/

void TBoardView::ClearSnake(){
	for ( TBall p : SnakeBalls ){
		img->DrawSquare(p);
		if (linesGame->board[p.x][p.y] > 0)
			img->DrawBall(p,1.0,linesGame->board[p.x][p.y]);
		}
}

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
			img->graphics.DrawBall(xx, yy,  0.4, color);
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
void TBoardView::DrawNextBalls(){
	for ( TBall p : linesGame->nextBalls ){
				img->DrawSquare(p);
				img->DrawBall(p,0.2,p.color);
			}
}


