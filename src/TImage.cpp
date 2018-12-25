/*
 * TImage.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: Alex
 */

#include <cmath>

#include "TImage.h"
#include "TApp.h"

#include "logger.h"

TImage::TImage(Evas_Object *conform){
	// TODO Auto-generated constructor stub

	modelView = &TApp::instance()->modelView;

	linesGame = &modelView->linesGame;

	TCairoGraphics::Create(conform);

	//image = evas_object_image_filled_add(evas_object_evas_get(conform));

//	elm_object_part_content_set(layout, "elm.swallow.content", image);
	//evas_object_event_callback_add(image, EVAS_CALLBACK_RESIZE, win_resize_cb2, this);
	//evas_object_show(image);

	//graphics.setParentImage(image);

	LoadBgImage();
	DBG("TImage::Construktor");
}

TImage::~TImage() {
	// TODO Auto-generated destructor stub
}

void TImage::Paint(){
	CalcViewMarkup();

	if (xTranslation!=0)
		DrawBoardX(xTranslation);
	else
		{
			FillBackgroud();
			DrawBoard();
			DrawBalls();
			DrawNextBalls();
			if(isBallSelected)
					JumpingBall();

		}

//cairo_set_source_rgb(myCairo, 1.0, 0.1, 0.5);
//	cairo_paint(myCairo);
	cairo_surface_flush(mySurface);

}

#define BUFLEN 500

void TImage::LoadBgImage(){
	//  Load bg image, create surface from bg image

	char buff[BUFLEN];
    char *path = app_get_shared_resource_path();

    snprintf(buff, 300, "%s%s", path, "pat9.png");
    bg_image = cairo_image_surface_create_from_png(buff);
    free(path);
}

void TImage::Init(int width, int height){
//	myWidth = width;
//	myHeight = height;

//	graphics.Initialize(width, height);

//	CairoDrawing();
}


void TImage::Flush(){
	if(isBallSelected) {
			tick +=0.25;
			JumpingBall();
		}

//	graphics.Flush();
}


void TImage::CairoDrawing(){

//	graphics.FillBackgroud();

//	CalcViewMarkup();

//	DrawHeader();

//	DrawBoard();
	//DrawNextBalls();
	//if (linesGame->initBalls) DrawBalls();
//	graphics.DrawMask();
//	graphics.Flush();
}

void TImage::FillBackgroud(){

	cairo_set_source_rgb(myCairo, 0.5, 0.5, 1.0);
	cairo_paint(myCairo);

	cairo_pattern_t *pattern1 = cairo_pattern_create_for_surface(bg_image);

	cairo_set_source(myCairo, pattern1);
	cairo_pattern_set_extend(cairo_get_source(myCairo), CAIRO_EXTEND_REPEAT);
	cairo_rectangle(myCairo, 0, 0, myWidth, myHeight);
	cairo_fill(myCairo);

}

void TImage::CalcViewMarkup(){

	double BoardWidth = myWidth - 60;

	left_margin = ( myWidth - BoardWidth)/2;

	squareSize = BoardWidth / linesGame->sizeX;
//	graphics.squareSize = squareSize;

	double BoardHeight = squareSize * linesGame->sizeY;
	top_margin = ( myHeight - BoardHeight)/2;
}

void TImage::DrawHeader() {

	//graphics.DrawHeaderBG();

	//graphics.DrawScore(20,60,linesBoard->record);
	//graphics.DrawScore(myWidth - 60 ,60,linesBoard->score);

	//graphics.DrawScore(left_margin, squareSize/2 + 8,"Best", linesGame->record, 0);
//	graphics.DrawScore(myWidth /2 , squareSize/2 + 8,"Score", linesGame->score, 2);//1);

}

void TImage::DrawBalls(){
	for (int x = 0; x< linesGame->sizeX; x++)
	for (int y = 0; y< linesGame->sizeY; y++) {
			double xx = x*squareSize  + left_margin;
			double yy = y*squareSize  + top_margin;
			int c = linesGame->board[x+1][y+1];
			if (c>0)
				DrawBall(xx + squareSize / 2, yy + squareSize / 2, c);
	}
}

void TImage::DrawBoardX(int translation){
	//if (semaphor) return;
	semaphor = true;
	FillBackgroud();

	int dx = 0;
	if (translation>squareSize/2) dx = -1;
	if (translation<-squareSize/2) dx = 1;
	xOffset = dx;
	for (int x = 0; x< linesGame->sizeX; x++)
	for (int y = 0; y< linesGame->sizeY; y++) {
				int k = x+dx;
				double xx = k*squareSize  + left_margin + translation;
				double yy = y*squareSize  + top_margin ;
				DrawSquare(xx, yy);

				if (k<0)
					k = linesGame->sizeX+k;
				else
					if(k == linesGame->sizeX) k = k - linesGame->sizeX;
				int c = linesGame->board[k+1][y+1];
				if (c>0) DrawBall(xx + squareSize / 2, yy + squareSize / 2, c);

			}
	//graphics.Flush();
	//graphics.Refresh();
	semaphor = false;
}

void TImage::DrawBoard(){

	for (int x = 0; x< linesGame->sizeX; x++)
		for (int y = 0; y< linesGame->sizeY; y++) {
			double xx = x*squareSize  + left_margin;
			double yy = y*squareSize  + top_margin ;
			DrawSquare(xx, yy);
		}
}

void TImage::DrawSquare(TBall p){
	double x = (p.x-1)*squareSize  + left_margin;
	double y = (p.y-1)*squareSize  + top_margin;
	DrawSquare(x, y);
}

void TImage::DrawRoundRectangle(double x, double y, double w, double h, double r){
	cairo_move_to (myCairo, x+r, y);
	cairo_rel_line_to (myCairo, w-2*r, 0);
	cairo_rel_line_to (myCairo, r, r);
	cairo_rel_line_to (myCairo, 0, h-2*r);
	cairo_rel_line_to (myCairo, -r, r);
	cairo_rel_line_to (myCairo, -w+2*r, 0);
	cairo_rel_line_to (myCairo, -r, -r);
	cairo_rel_line_to (myCairo, 0, -h+2*r);
	cairo_close_path (myCairo);
}


void TImage::SetPatternForSquare(int x, int y, int r){
//  gold
//  double r1 = 1.0; double r2 = 1.0;
//  double g1 = 242.0/255.0; double g2 = 217.0/255.0;
//  double b1 = 204.0/255.0; double b2 = 102.0/255.0;

	// sepiya
	  double r2 = 159.0/255.0; double r1 = 191.0/255.0;
	  double g2 = 142.0/255.0; double g1 = 178.0/255.0;
	  double b2 = 126.0/255.0; double b1 = 165.0/255.0;
    cairo_pattern_t *pattern1 = cairo_pattern_create_radial (x - r/4 , y - r/4  , r/2.5 , x, y, 1.5*r);
	cairo_pattern_add_color_stop_rgba(pattern1, 1.0, r1, g1, b1, 0.8);
	cairo_pattern_add_color_stop_rgba(pattern1, 0.0, r2, g2, b2, 0.5);

	cairo_set_source(myCairo, pattern1);
}

void TImage::DrawSquare(double x, double y){

	cairo_pattern_t *pattern1 = cairo_pattern_create_for_surface(bg_image);

	cairo_set_source(myCairo, pattern1);
	cairo_pattern_set_extend(cairo_get_source(myCairo), CAIRO_EXTEND_REPEAT);
	DrawRoundRectangle(x+2, y+2, squareSize-4, squareSize-4, 5);
	cairo_fill(myCairo);


	//SetPatternForSquare(x + squareSize /2, y + squareSize/2, squareSize-4);
	cairo_set_source_rgba(myCairo, 128.0/255.0, 128.0/255.0, 128.0/255.0, 0.35);
	DrawRoundRectangle(x+2, y+2, squareSize-4, squareSize-4, 5);
	cairo_fill (myCairo);
}



void TImage::DrawBall(TBall p, double r){
	double x = p.x*squareSize - squareSize / 2 + left_margin;
	double y = p.y*squareSize - squareSize / 2 + top_margin;
    DrawBall(x, y, r, p.color);
}


void TImage::DrawBall(TBall p, double r, int color){
	double x = p.x*squareSize - squareSize / 2 + left_margin;
	double y = p.y*squareSize - squareSize / 2 + top_margin;
	DrawBall(x, y, r, color);
}

void TImage::DrawBall(double x, double y, int color){
	DrawBall(x,y,1,color);
}


void TImage::SetPattern(double x,double y, int radius, int color){

	double r,g,b;
	switch (color) {
	case 0: r = 0.5; g = 0.5, b = 0.5; break;
	case 1: r = 1.0; g = 0.2, b = 0.2; break;
	case 2: r = 0.2; g = 1.0, b = 0.2; break;
	case 3: r = 0.2; g = 0.2, b = 1.0; break;
	case 4: r = 1.0; g = 1.0, b = 0.2; break;
	case 5: r = 1.0; g = 0.0, b = 1.0; break;
	case 6: r = 0.0; g = 1.0, b = 1.0; break;
	case 7: r = 1.0; g = 1.0, b = 1.0; break;

	default:
		r = 0.0; g = 0.0, b = 0.0;

	}

	cairo_pattern_t *pattern1 = cairo_pattern_create_radial (x - radius/2, y - radius, radius/2 , x, y, 3*radius);


	cairo_pattern_add_color_stop_rgb(pattern1, 1.0, r/2, g/2, b/2);
	cairo_pattern_add_color_stop_rgb(pattern1, 0.0, r, g, b);

	cairo_set_source(myCairo, pattern1);


}
void TImage::SetColor(int color){
	switch (color) {
	case 0: cairo_set_source_rgba(myCairo, 0.5, 0.5, 0.5, 0.9); break;
	case 1: cairo_set_source_rgba(myCairo, 1.0, 0.2, 0.2, 0.9); break;
	case 2: cairo_set_source_rgba(myCairo, 0.2, 1.0, 0.2, 0.9); break;
	case 3: cairo_set_source_rgba(myCairo, 0.2, 0.2, 1.0, 0.9); break;
	case 4: cairo_set_source_rgba(myCairo, 1.0, 1.0, 0.2, 0.9); break;
	case 5: cairo_set_source_rgba(myCairo, 1.0, 0.0, 1.0, 0.9); break;
	case 6: cairo_set_source_rgba(myCairo, 0.0, 1.0, 1.0, 0.9); break;
	case 7: cairo_set_source_rgba(myCairo, 1.0, 1.0, 1.0, 0.9); break;

	default:
	 cairo_set_source_rgba(myCairo, 0.0, 0.0, 0.0, 1.0);
	}
}

void TImage::DrawBall(double x, double y, double r, int color){

	//if (color == 0) return;

	double  radius = r * 3*squareSize / 8;

	//cairo_set_source_rgba(cairo, 1.0, 0.2, 0.2, 0.9);

	//SetColor(color);
	SetPattern(x,y, radius, color);

	cairo_arc(myCairo, x, y, radius, 0, 2*M_PI);
	cairo_fill(myCairo);
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

	tick +=0.25;

	double x = (selBall.x-1)*squareSize  + left_margin;
	double y = (selBall.y-1)*squareSize  + top_margin;

	DrawSquare(x,y);
	x = x + squareSize / 2 ;
	y = y + squareSize / 2 + squareSize / 8*(1-std::abs(cos(tick))) - 1;
	// y = y + squareSize / 2 + 5*ecore_animator_pos_map((sin(tick)+1)/2,ECORE_POS_MAP_BOUNCE , 2,  4  );
	DrawBall(x,y,linesGame->board[selBall.x][selBall.y]);
//	cairo_surface_flush(mySurface);
}
