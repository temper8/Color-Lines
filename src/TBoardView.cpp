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

static Eina_Bool _startShowAllBalls(void *data) {
	TBoardView *bv = (TBoardView *) data;
	bv->startShowAllBalls();
   return EINA_FALSE;
}

TBoardView::TBoardView(): myPopupBox(NULL) {
	// TODO Auto-generated constructor stub
	loadHelp();

	linesGame = new TLinesGame(8,11);
	//linesBoard->initRandom();
	selBall.x = 0;
	selBall.y = 0;

    graphics.LoadBgImage();


//	animator = ecore_animator_add([](void *data){((TBoardView *) data)->RefreshGraphics(); return EINA_TRUE;}, this);

    ecore_timer_add(animation_pause, _startShowAllBalls, this);

}

TBoardView::~TBoardView() {
	// TODO Auto-generated destructor stub
}
void TBoardView::OnAppCreate(){
	TView::OnAppCreate();
	animator = ecore_animator_add([](void *data){((TBoardView *) data)->RefreshGraphics(); return EINA_TRUE;}, this);
}


void TBoardView::NewGame(){
	linesGame->newGame();
	selBall.x = 0;
	selBall.y = 0;
	CairoDrawing();
}

void TBoardView::loadHelp() {
    std::string filename(app_get_shared_resource_path());
    filename.append("help.en");
    std::ifstream t(filename.c_str());
    std::stringstream buffer;
    buffer << t.rdbuf();
    if (buffer.str().length()>0)
    	helpText = buffer.str();
    else {
    	helpText = "Game rules<br>Oops, an error occurred.";
    }
}

void TBoardView::closePopupBox(){
	delete myPopupBox;
	myPopupBox = NULL;
}

void TBoardView::callbackMore(){
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
}

void TBoardView::callbackBack(){
	if (myPopupBox!=NULL) closePopupBox();
	myPopupBox = new TExitPopupBox();
	myPopupBox->OnBtnClick = [this](int tag) { if (tag==1) ui_app_exit(); };
	myPopupBox->show();
}

void TBoardView::showHelp(){
	myPopupBox = new TInfoBox(helpText.c_str());
	myPopupBox->OnBtnClick = [this](int ) { closePopupBox(); };
	myPopupBox->show();
}

void TBoardView::showGameOverBox(){
	myPopupBox = new TGameOverBox();
	myPopupBox->OnBtnClick = [this](int tag) {closePopupBox(); if (tag==2) NewGame(); else ui_app_exit(); };
	myPopupBox->show();
}


void TBoardView::OnClick(int x, int y) {
	//if (BallSnakeRun) return;
	int xx =(x-left_margin) / squareSize + 1;
	int yy =(y-top_margin) / squareSize + 1;

	if (linesGame->OutOfBoundary(xx, yy)) return;

    if (linesGame->board[xx][yy] > 0) {
    	selBall.x = xx;
    	selBall.y = yy;
    	selBall.color = linesGame->board[xx][yy];
    	isBallSelected = true;
       // startJumpingBallAnimator();
    }
    else {
    	if (isBallSelected)  {
    		isBallSelected = false;

    		destSquare.x = xx;
    		destSquare.y = yy;

    		linesGame->initSearch(selBall);

            if (linesGame->searchPath(selBall,destSquare) >0) {
            	 createMoveBallAnimator();

            }


    	}

    }
};

void TBoardView::OnMomentumStart(int x, int y) {
	//if (BallSnakeRun ) return;
	x0 = x;
	y0 = y;
	int xx =(x-left_margin) / squareSize + 1;
	int yy =(y-top_margin) / squareSize + 1;
	xx0=xx;
	yy0=yy;
	xxm=xx;
	yym=yy;
	if (linesGame->OutOfBoundary(xx, yy)) return;

    if (linesGame->board[xx][yy] > 0) {
    	graphics.tx = x;
    	graphics.ty = y;
    	graphics.ring = linesGame->board[xx][yy];
    	graphics.goodPath = true;
    	selBall.x = xx;
    	selBall.y = yy;
    	selBall.color = linesGame->board[xx][yy];
    	isBallSelected = true;
    	linesGame->initSearch(selBall);
    }
};

void TBoardView::OnMomentumMove(int x, int y) {
	//dlog_print(DLOG_DEBUG, LOG_TAG, "TBoardView::OnMomentumMove x:%d y:%d", x, y);
	graphics.tx = x;
	graphics.ty = y;

	int xx =(x-left_margin) / squareSize + 1;
	int yy =(y-top_margin) / squareSize + 1;

	if ((xxm == xx)&&(yym==yy))		return;


	xxm=xx;
	yym=yy;
	destSquare.x = xx;
	destSquare.y = yy;

	if (isBallSelected)  {
		ClearPath();
		if (linesGame->OutOfBoundary(xx, yy)) {
			graphics.goodPath = false;
			return;
		}

		linesGame->initSearch(selBall);

		if (linesGame->board[xx][yy]>0)	{
			graphics.goodPath = false;
			linesGame->searchClosestPath(selBall,destSquare);
			DrawPath(0);
			return;
		}

        if (linesGame->searchPath(selBall,destSquare) >0) {
        	 DrawPath(graphics.ring);
        	 graphics.goodPath = true;
        }
        else{
        	graphics.goodPath = false;
        	linesGame->searchClosestPath(selBall,destSquare);
        	DrawPath(0);
        }

	}

};

void TBoardView::OnMomentumEnd(int x, int y) {

	 graphics.ring =0;
	 graphics.goodPath = false;
	 int xx =(x-left_margin) / squareSize + 1;
	 int yy =(y-top_margin) / squareSize + 1;

	 if ((xx0 == xx)&&(yy0==yy))	return;
	 ClearPath();
	 linesGame->path.clear();

	if (isBallSelected)  {
			isBallSelected = false;
			if (linesGame->OutOfBoundary(xx, yy)||(linesGame->board[xx][yy]>0)||animationOn){
				DrawBall(selBall,1);
				return;
			}

			destSquare.x = xx;
			destSquare.y = yy;
			linesGame->initSearch(selBall);

			if (linesGame->searchPath(selBall,destSquare) >0) {
				createMoveBallAnimator();
			}
	}
};



// animation

void TBoardView::RefreshGraphics(){

	if(isBallSelected) {
		tick +=0.15;
		jumpingBall();
	}

/*	if (BallSnakeRun) {
		DrawSnake(ballSnakePos);
	}
	if (appearanceNewBalls) {
		appearanceNewBall(timeLinePos);
	}
	if (disappearanceBalls) {
		disappearanceLines(timeLinePos);
	}
*/

	/*if (needUpdateScore) {
		DrawHeader();
		needUpdateScore = false;
	}
*/
	graphics.Flush();
}


void TBoardView::jumpingBall(){
	double x = (selBall.x-1)*squareSize  + left_margin;
	double y = (selBall.y-1)*squareSize  + top_margin;

	graphics.DrawSquare(x,y);
	x = x + squareSize / 2 ;
	y = y + squareSize / 2 + squareSize / 8*(1-std::abs(cos(tick))) - 1;
	// y = y + squareSize / 2 + 5*ecore_animator_pos_map((sin(tick)+1)/2,ECORE_POS_MAP_BOUNCE , 2,  4  );
	DrawBall(x,y,linesGame->board[selBall.x][selBall.y]);

}

void TBoardView::moveBall(double pos) {
	DrawPath(pos);
	graphics.Flush();
}

void TBoardView::createMoveBallAnimator(){
	linesGame->board[destSquare.x][destSquare.y] = linesGame->board[selBall.x][selBall.y];
	linesGame->board[selBall.x][selBall.y] = 0;
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
		    NewBalls = linesGame->addNewBalls();
			ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TBoardView *) data)->appearanceNewBall(pos); return EINA_TRUE;}, this);
			if (linesGame->gameOver()) {
				ecore_timer_add(animation_time, [](void *data)	{ ((TBoardView *)data)->showGameOverBox(); return EINA_FALSE; }, this);
			}
	}
	else {
		ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TBoardView *) data)->disappearanceLines(pos); return EINA_TRUE;}, this);
	}
	ecore_timer_add(animation_time, [](void *data)	{ ((TBoardView *)data)->animationOn = false; return EINA_FALSE; }, this);
	DrawHeader();
}

void TBoardView::startShowAllBalls(){
    NewBalls = linesGame->makeListBalls();
    timeLinePos = 0;
    animationOn = true;
	ecore_animator_timeline_add (animation_time, [](void *data, double pos){((TBoardView *) data)->appearanceNewBall(pos); return EINA_TRUE;}, this);
	ecore_timer_add(animation_time, [](void *data)	{ ((TBoardView *)data)->animationOn = false; return EINA_FALSE; }, this);
}

void TBoardView::appearanceNewBall(double pos) {
	for ( TPoint p : NewBalls )
		DrawBall(p,  pos);
}

void TBoardView::disappearanceLines(double pos){
	double r = 0.95 - pos;
	if (r < 0) r = 0;
	for ( TPoint p : linesGame->clearBalls ){
	    DrawSquare(p);
		DrawBall(p,  r);
	}
}

// drawing

void TBoardView::CairoDrawing(){

	graphics.FillBackgroud();

	CalcViewMarkup();

	DrawHeader();

	DrawBoard();

	//if (linesGame->initBalls) DrawBalls();
//	graphics.DrawMask();
	graphics.Flush();
}

void TBoardView::DrawBalls() {
	for(int i=1; i<= linesGame->sizeX; i++)
	  for(int j=1; j<= linesGame->sizeY; j++){
			double x = i*squareSize - squareSize / 2 + left_margin;
			double y = j*squareSize - squareSize / 2 + top_margin;
			DrawBall(x,y,linesGame->board[i][j]);
	  }
}

void TBoardView::DrawSquare(TPoint p){
	double x = (p.x-1)*squareSize  + left_margin;
	double y = (p.y-1)*squareSize  + top_margin;
	graphics.DrawSquare(x, y);
}

void TBoardView::CalcViewMarkup(){

	double BoardWidth = myWidth - 20;

	left_margin = ( myWidth - BoardWidth)/2;

	squareSize = BoardWidth / linesGame->sizeX;
	graphics.squareSize = squareSize;

	double BoardHeight = squareSize * linesGame->sizeY;
	top_margin = ( myHeight - BoardHeight)/2;
}

void TBoardView::DrawBoard(){

	for (int x = 0; x< linesGame->sizeX; x++)
		for (int y = 0; y< linesGame->sizeY; y++) {
			double xx = x*squareSize  + left_margin;
			double yy = y*squareSize  + top_margin ;
			graphics.DrawSquare(xx, yy);
		}
}

void TBoardView::DrawBall(TPoint p, double r){
	double x = p.x*squareSize - squareSize / 2 + left_margin;
	double y = p.y*squareSize - squareSize / 2 + top_margin;
	graphics.DrawBall(x, y, r, p.color);
}

void TBoardView::DrawBall(TPoint p, double r, int color){
	double x = p.x*squareSize - squareSize / 2 + left_margin;
	double y = p.y*squareSize - squareSize / 2 + top_margin;
	graphics.DrawBall(x, y, r, color);
}

void TBoardView::DrawBall(double x, double y, int color){
	graphics.DrawBall(x,y,1,color);
}

void TBoardView::ClearSnake(){
	for ( TPoint p : SnakeBalls ){
		DrawSquare(p);
		if (linesGame->board[p.x][p.y] > 0)
			DrawBall(p,1.0,linesGame->board[p.x][p.y]);
		}
}

void TBoardView::ClearPath(){
	if (linesGame->path.size()>0) {
		//TPoint p = linesGame->path.front();
		//int color =  linesGame->board[p.x][p.y];
		for ( TPoint p : linesGame->path ){
			//double xx = p.x*squareSize - squareSize / 2 + left_margin;
			//double yy = p.y*squareSize - squareSize / 2 + top_margin;
			//graphics.DrawBall(xx, yy,  0.4, p.color);
			DrawSquare(p);
			if (linesGame->board[p.x][p.y] > 0)
				DrawBall(p,1.0,linesGame->board[p.x][p.y]);
		}

	}
}
void TBoardView::DrawPath(int color){
	if (linesGame->path.size()>0) {
		//TPoint p = linesGame->path.front();
		//int color =  linesGame->board[p.x][p.y];
		for ( TPoint p : linesGame->path ){
			double xx = p.x*squareSize - squareSize / 2 + left_margin;
			double yy = p.y*squareSize - squareSize / 2 + top_margin;
			graphics.DrawBall(xx, yy,  0.4, color);
		}

	}
}

void TBoardView::DrawSnake(double pos){
	if (SnakeBalls.size() == 0) return;
	double dx = M_PI/(SnakeBalls.size()-1);
	for (int i = 0; i<SnakeBalls.size(); i++ ) {
		TPoint p  =  SnakeBalls[i];

		DrawSquare(p);

		double r = cos(dx*i - M_PI*(1-1.5*pos));
		if (r<0) r = 0.0; else r = 0.5*r;

		DrawBall(p, r, p.color);
	}
	if (pos>0.5) {
		TPoint p = SnakeBalls.front();
		DrawBall(p, 1, p.color);
	}

}

void TBoardView::DrawHeader() {

	graphics.DrawHeaderBG();

	//graphics.DrawScore(20,60,linesBoard->record);
	//graphics.DrawScore(myWidth - 60 ,60,linesBoard->score);

	graphics.DrawScore(left_margin, squareSize + 8,"Best", linesGame->record, 0);
	graphics.DrawScore(myWidth - left_margin , squareSize + 8,"Score", linesGame->score, 1);

	double dx = (myWidth - 1.1*squareSize *3)/2;
	for (int i = 0; i<3; i++) {
		double x = dx + 1.1*squareSize*i;
		graphics.DrawSquare(x, 10);
		graphics.DrawBall(x + squareSize/2, 10 + squareSize/2,  1, linesGame->ballsHolder.balls[i]);
	}
}



