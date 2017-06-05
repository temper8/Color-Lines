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

static Eina_Bool
add_random_balls(void *data)
{
	TBoardView *bv = (TBoardView *) data;
	bv->AddRandomBalls();

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

    ecore_timer_add(animation_pause, add_random_balls, this);

}

TBoardView::~TBoardView() {
	// TODO Auto-generated destructor stub
}


void TBoardView::NewGame(){
	linesGame->newGame();
	selBall.x = 0;
	selBall.y = 0;
	CairoDrawing();
	ecore_timer_add(animation_pause, add_random_balls, this);
}

void TBoardView::loadHelp() {
   // auto filename = "my-file.txt";
	char filename[500];
    char *path = app_get_shared_resource_path();

    snprintf(filename, 500, "%s%s", path, "help.en");

    std::ifstream t(filename);
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
	myPopupBox->OnBtnClick = [this](int r) { if (r==1) ui_app_exit(); };
	myPopupBox->show();
}

void TBoardView::showHelp(){
	myPopupBox = new TInfoBox(helpText.c_str());
	myPopupBox->OnBtnClick = [this](int r) { closePopupBox(); };
	myPopupBox->show();
}

void TBoardView::showGameOverBox(){
	myPopupBox = new TGameOverBox();
	myPopupBox->OnBtnClick = [this](int tag) {closePopupBox(); if (tag==2) NewGame(); else ui_app_exit(); };
	myPopupBox->show();
}


void TBoardView::OnClick(int x, int y) {

	int xx =(x-left_margin) / squareSize + 1;
	int yy =(y-top_margin) / squareSize + 1;

	if (linesGame->OutOfBoundary(xx, yy)) return;

    if (linesGame->board[xx][yy] > 0) {
    	selBall.x = xx;
    	selBall.y = yy;

        startJumpingBallAnimator();
    }
    else {
    	if (selBall.x > 0)  {

    		destSquare.x = xx;
    		destSquare.y = yy;

    		linesGame->initSearch(selBall,destSquare);

            if (linesGame->searchPath(selBall,destSquare) >0) {
            	linesGame->board[destSquare.x][destSquare.y] = linesGame->board[selBall.x][selBall.y];
            	linesGame->board[selBall.x][selBall.y] = 0;
            	 selBall.x = 0;
            	 deleteJumpingBallAnimator();
            	 createMoveBallAnimator();

            }

    	}

    }
};

// animation

void TBoardView::jumpingBall(){
 if (selBall.x !=0) {

	double x = (selBall.x-1)*squareSize  + left_margin;
	double y = (selBall.y-1)*squareSize  + top_margin;

	tick +=0.15;
	graphics.DrawSquare(x,y);
	x = x + squareSize / 2 ;
	y = y + squareSize / 2 + squareSize / 8*(1-std::abs(cos(tick))) - 1;
	// y = y + squareSize / 2 + 5*ecore_animator_pos_map((sin(tick)+1)/2,ECORE_POS_MAP_BOUNCE , 2,  4  );
	DrawBall(x,y,linesGame->board[selBall.x][selBall.y]);
	graphics.Flush();
 }
}

void TBoardView::startJumpingBallAnimator(){
  tick = 0;
  if (JumpingAnimator != NULL)
  	   ecore_animator_del(JumpingAnimator);
  JumpingAnimator = ecore_animator_add([](void *data){((TBoardView *) data)->jumpingBall(); return EINA_TRUE;}, this);
}

void TBoardView::deleteJumpingBallAnimator(){
	if (JumpingAnimator != NULL)
	   ecore_animator_del(JumpingAnimator);
}

void TBoardView::moveBall(double pos) {
	DrawPath(pos);
	graphics.Flush();
}

void TBoardView::createMoveBallAnimator(){
	ecore_animator_timeline_add (animation_time, [](void *data, double pos){((TBoardView *) data)->moveBall(pos); return EINA_TRUE;}, this);
	ecore_timer_add(animation_time, [](void *data){((TBoardView *) data)->afterMoveBall();  return EINA_FALSE;}, this);
}

void TBoardView::deleteMoveBallAnimator(){

}

Eina_Bool appearance_new_ball(void *data, double pos)
{
   TBoardView *bv = (TBoardView *) data;
   bv->appearanceNewBall(pos);
   return EINA_TRUE;
}

Eina_Bool disappearance_lines(void *data, double pos)
{
   TBoardView *bv = (TBoardView *) data;
   bv->disappearanceLines(pos);
   return EINA_TRUE;
}

void TBoardView::afterMoveBall(){

	if (linesGame->checkLines() == 0 )	{
		    NewBalls = linesGame->addNewBalls();
			ecore_animator_timeline_add (animation_time, appearance_new_ball, this);
			if (linesGame->gameOver()) {
				ecore_timer_add(animation_time, [](void *data)	{ ((TBoardView *)data)->showGameOverBox(); return EINA_FALSE; }, this);
			}
	}
	else {
		ecore_animator_timeline_add (animation_time, disappearance_lines, this);
	}
	DrawHeader();
}

void TBoardView::AddRandomBalls(){
    NewBalls = linesGame->AddRandomBalls();
	ecore_animator_timeline_add (animation_time, appearance_new_ball, this);
}

void TBoardView::appearanceNewBall(double pos) {
	for ( TPoint p : NewBalls )
		DrawBall(p,  pos);
	graphics.Flush();
}

void TBoardView::disappearanceLines(double pos){
	for ( TPoint p : linesGame->clearBalls ){
	    DrawSquare(p);
		DrawBall(p,  1-pos);
	}
	graphics.Flush();
}

// drawing

void TBoardView::CairoDrawing(){

	graphics.FillBackgroud();

	CalcViewMarkup();

	DrawHeader();

	DrawBoard();

	if (linesGame->initBalls) DrawBalls();

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

void TBoardView::DrawPath(){
	if (linesGame->path.size()>0) {
		TPoint p = linesGame->path.front();
		int color =  linesGame->board[p.x][p.y];
		for ( TPoint p : linesGame->path ){
			double xx = p.x*squareSize - squareSize / 2 + left_margin;
			double yy = p.y*squareSize - squareSize / 2 + top_margin;
			graphics.DrawBall(xx, yy,  0.4, color);
		}

	}

}

void TBoardView::DrawPath(double pos){
	if (linesGame->path.size() == 0) return;
	double dx = M_PI/linesGame->path.size();
	for (int i = 0; i<linesGame->path.size(); i++ ) {
		TPoint p  =  linesGame->path[i];

		DrawSquare(p);

		double r = cos(dx*i - M_PI*(1-1.5*pos));
		if (r<0) r = 0.0; else r = 0.5*r;

		DrawBall(p, r, p.color);
	}
	if (pos>0.5) {
		TPoint p = linesGame->path.front();
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



