/*
 * TImage.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: Alex
 */

#include <cmath>

#include "TImage.h"
#include "TApp.h"


#include "TAnimator.h"

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

	switch(animator->state){

	case TAnimator::State::Default:
		FillBackgroud();
		DrawHeader();
		DrawBoard();
		break;

	case TAnimator::State::DefaultWithBalls:
		FillBackgroud();
		DrawHeader();
		DrawBoard();
		DrawBalls();
		DrawNextBalls();
		if(animator->isBallSelected)
				JumpingBall();
		break;


	case TAnimator::State::Slipping:
		FillBackgroud();
		DrawHeader();
		DrawBoardX(xTranslation);
		break;

	case TAnimator::State::DelBallAnimation:
		disappearanceLines(animator->Pos);
		break;

	case TAnimator::State::NewBallAnimation:
		AppearanceNewBall(animator->Pos);
		break;

	case TAnimator::State::SnakeAnimation:
		DrawSnake(animator->Pos);
		break;
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

	 DrawHeaderBG();

	 if (modelView->deviceType == DeviceType::mobile){
		// DrawScore(20,60,linesBoard->record);
		// DrawScore(myWidth - 60 ,60,linesBoard->score);
		 DrawScore(left_margin, squareSize/2 + 12,"Best", linesGame->record, 0);
		 DrawScore(myWidth, squareSize/2 + 12,"Score", linesGame->score, 1);//1);
	 }
	 else
		 DrawScore(myWidth /2 , squareSize/2 + 8,"Score", linesGame->score, 2);//1);

}


void TImage::DrawScore(double x, double y, const char* caption, int score, int aling){

	char text[16] = {0};
    sprintf(text, "%0*d",4, score);

    double x1 = x;
    double x2 = x;

    cairo_select_font_face(myCairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(myCairo, 3*squareSize/7);
	cairo_text_extents_t extents;
	cairo_text_extents (myCairo, text, &extents);
	switch (aling){
	case 1:x2 = x - extents.width; break;
	case 2:x2 = x - extents.width/2;break;
	}
	double yy = y - extents.height - 8;
    cairo_move_to(myCairo, x2, y);
    cairo_text_path(myCairo, text);
    cairo_set_source_rgb(myCairo, 127 / 255.0, 127 / 255.0, 127 / 255.0);
    cairo_fill(myCairo);


	cairo_select_font_face(myCairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(myCairo, 2*squareSize/7);
	cairo_text_extents (myCairo, caption, &extents);
	switch (aling){
	case 1:x1 = x1 - extents.width; break;
	case 2:x1 = x1 - extents.width/2;break;
	}
    cairo_move_to(myCairo, x1, yy);
    cairo_text_path(myCairo, caption);
    cairo_set_source_rgb(myCairo, 127 / 255.0, 127 / 255.0, 127 / 255.0);
    cairo_fill(myCairo);


}



void TImage::DrawScore(double x, double y, int score){
	char text[16] = {0};
    cairo_select_font_face(myCairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

    cairo_set_font_size(myCairo, 50);
    cairo_move_to(myCairo, x, y);

    sprintf(text, "%d",score);
    cairo_text_path(myCairo, text);
    cairo_set_source_rgb(myCairo, 127 / 255.0, 127 / 255.0, 127 / 255.0);
    cairo_fill(myCairo);
}

void TImage::DrawHeaderBG(){
	int HeaderHeight = squareSize+20;

	//cairo_pattern_t *pattern1 = cairo_pattern_create_for_surface(bg_image);
	//cairo_set_source(cairo, pattern1);
	//cairo_pattern_set_extend(cairo_get_source(cairo), CAIRO_EXTEND_REPEAT);

	cairo_set_source_rgb(myCairo, 255.0/255.0, 217.0/255.0, 102.0/255.0);

	cairo_rectangle(myCairo, 0, 0, myWidth, HeaderHeight);
	cairo_fill(myCairo);
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

void TImage::AppearanceNewBall(double pos) {
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

	double x = (animator->selBall.x-1)*squareSize  + left_margin;
	double y = (animator->selBall.y-1)*squareSize  + top_margin;

	DrawSquare(x,y);
	x = x + squareSize / 2 ;
	y = y + squareSize / 2 + squareSize / 8*(1-std::abs(cos(tick))) - 1;
	// y = y + squareSize / 2 + 5*ecore_animator_pos_map((sin(tick)+1)/2,ECORE_POS_MAP_BOUNCE , 2,  4  );
	DrawBall(x,y,linesGame->board[animator->selBall.x][animator->selBall.y]);
//	cairo_surface_flush(mySurface);
}


void TImage::DrawSnake(double pos){
	if (SnakeBalls.size() == 0) return;
	double dx = M_PI/(SnakeBalls.size()-1);
	for (int i = 0; i<SnakeBalls.size(); i++ ) {
		TBall p  =  SnakeBalls[i];

		DrawSquare(p);

		double r = cos(dx*i - M_PI*(1-1.5*pos));
		if (r<0) r = 0.0; else r = 0.5*r;

		DrawBall(p, r, p.color);
	}
	if (pos>0.5) {
		TBall p = SnakeBalls.front();
		DrawBall(p, 1, p.color);
	}

}

void TImage::ClearSnake(){
	for ( TBall p : SnakeBalls ){
		DrawSquare(p);
		if (linesGame->board[p.x][p.y] > 0)
			DrawBall(p,1.0,linesGame->board[p.x][p.y]);
		}
}




void TImage::NewGameAnimation(){
	balls = linesGame->addNewBalls();
	/*
	state = State::NewBallAnimation;
	ecore_animator_timeline_add (animation_time,  [](void *data, double pos){((TImage *) data)->AnimationRefresh(pos); return EINA_TRUE;}, this);
	ecore_timer_add(animation_time, [](void *data)	{ ((TImage *)data)->state = State::Default; return EINA_FALSE; }, this);
	*/
}
