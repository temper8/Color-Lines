/*
 * TImage.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: Alex
 */

#include <cmath>

#include "TImage.h"
#include "TApp.h"

TImage::TImage(Evas_Object *conform):width(0),height(0) {
	// TODO Auto-generated constructor stub

	modelView = &TApp::instance()->modelView;

	linesGame = &modelView->linesGame;

	image = evas_object_image_filled_add(evas_object_evas_get(conform));

//	elm_object_part_content_set(layout, "elm.swallow.content", image);
	//evas_object_event_callback_add(image, EVAS_CALLBACK_RESIZE, win_resize_cb2, this);
	evas_object_show(image);

	graphics.setParentImage(image);

	graphics.LoadBgImage();
}

TImage::~TImage() {
	// TODO Auto-generated destructor stub
}

void TImage::Init(int width, int height){
	myWidth = width;
	myHeight = height;

	graphics.Initialize(width, height);

	CairoDrawing();
}


void TImage::Flush(){
	if(isBallSelected) {
			tick +=0.25;
			JumpingBall();
		}

	graphics.Flush();
}


void TImage::CairoDrawing(){

	graphics.FillBackgroud();

	CalcViewMarkup();

	DrawHeader();

	DrawBoard();
	//DrawNextBalls();
	//if (linesGame->initBalls) DrawBalls();
//	graphics.DrawMask();
	graphics.Flush();
}

void TImage::CalcViewMarkup(){

	double BoardWidth = myWidth - 60;

	left_margin = ( myWidth - BoardWidth)/2;

	squareSize = BoardWidth / linesGame->sizeX;
	graphics.squareSize = squareSize;

	double BoardHeight = squareSize * linesGame->sizeY;
	top_margin = ( myHeight - BoardHeight)/2;
}

void TImage::DrawHeader() {

	//graphics.DrawHeaderBG();

	//graphics.DrawScore(20,60,linesBoard->record);
	//graphics.DrawScore(myWidth - 60 ,60,linesBoard->score);

	//graphics.DrawScore(left_margin, squareSize/2 + 8,"Best", linesGame->record, 0);
	graphics.DrawScore(myWidth /2 , squareSize/2 + 8,"Score", linesGame->score, 2);//1);

}

void TImage::DrawBalls(){
	for (int x = 0; x< linesGame->sizeX; x++)
	for (int y = 0; y< linesGame->sizeY; y++) {
			double xx = x*squareSize  + left_margin;
			double yy = y*squareSize  + top_margin;
			int c = linesGame->board[x+1][y+1];
			if (c>0) DrawBall(xx + squareSize / 2, yy + squareSize / 2, c);
	}
}

void TImage::DrawBoardX(int translation){
	if (semaphor) return;
	semaphor = true;
	graphics.FillBackgroud();

	int dx = 0;
	if (translation>squareSize/2) dx = -1;
	if (translation<-squareSize/2) dx = 1;
	xOffset = dx;
	for (int x = 0; x< linesGame->sizeX; x++)
	for (int y = 0; y< linesGame->sizeY; y++) {
				int k = x+dx;
				double xx = k*squareSize  + left_margin + translation;
				double yy = y*squareSize  + top_margin ;
				graphics.DrawSquare(xx, yy);

				if (k<0)
					k = linesGame->sizeX+k;
				else
					if(k == linesGame->sizeX) k = k - linesGame->sizeX;
				int c = linesGame->board[k+1][y+1];
				//if (c>0) DrawBall(xx + squareSize / 2, yy + squareSize / 2, c);

			}
	graphics.Flush();
	semaphor = false;
}

void TImage::DrawBoard(){

	for (int x = 0; x< linesGame->sizeX; x++)
		for (int y = 0; y< linesGame->sizeY; y++) {
			double xx = x*squareSize  + left_margin;
			double yy = y*squareSize  + top_margin ;
			graphics.DrawSquare(xx, yy);
		}
}

void TImage::DrawSquare(TBall p){
	double x = (p.x-1)*squareSize  + left_margin;
	double y = (p.y-1)*squareSize  + top_margin;
	graphics.DrawSquare(x, y);
}

void TImage::DrawBall(TBall p, double r){
	double x = p.x*squareSize - squareSize / 2 + left_margin;
	double y = p.y*squareSize - squareSize / 2 + top_margin;
	graphics.DrawBall(x, y, r, p.color);
}


void TImage::DrawBall(TBall p, double r, int color){
	double x = p.x*squareSize - squareSize / 2 + left_margin;
	double y = p.y*squareSize - squareSize / 2 + top_margin;
	graphics.DrawBall(x, y, r, color);
}

void TImage::DrawBall(double x, double y, int color){
	graphics.DrawBall(x,y,1,color);
}

void TImage::DrawNextBalls(){
	for ( TBall p : linesGame->nextBalls ){
				DrawSquare(p);
				DrawBall(p,0.2,p.color);
			}
}

void TImage::appearanceNewBall(double pos) {
	for ( TBall p : balls )
		DrawBall(p,  pos);
}

void TImage::disappearanceLines(double pos){
	double r = 0.95 - pos;
	if (r < 0) r = 0;
	for ( TBall p : linesGame->clearBalls ){
		DrawSquare(p);
		DrawBall(p,  r);
	}
}

void TImage::JumpingBall(){
	double x = (selBall.x-1)*squareSize  + left_margin;
	double y = (selBall.y-1)*squareSize  + top_margin;

	graphics.DrawSquare(x,y);
	x = x + squareSize / 2 ;
	y = y + squareSize / 2 + squareSize / 8*(1-std::abs(cos(tick))) - 1;
	// y = y + squareSize / 2 + 5*ecore_animator_pos_map((sin(tick)+1)/2,ECORE_POS_MAP_BOUNCE , 2,  4  );
	DrawBall(x,y,linesGame->board[selBall.x][selBall.y]);
}
