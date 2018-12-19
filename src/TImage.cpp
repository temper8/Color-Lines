/*
 * TImage.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: Alex
 */

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

void TImage::DrawBoard(){

	for (int x = 0; x< linesGame->sizeX; x++)
		for (int y = 0; y< linesGame->sizeY; y++) {
			double xx = x*squareSize  + left_margin;
			double yy = y*squareSize  + top_margin ;
			graphics.DrawSquare(xx, yy);
		}
}
