/*
 * TBoardView.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#include "TBoardView.h"

#include <cmath>

#define BUFLEN 500

TBoardView::TBoardView() {
	// TODO Auto-generated constructor stub
	mx = 250;
	my = 250;
	linesBoard = new TLinesBoard(7,11);
	linesBoard->initRandom();
	selBall.x = 0;
	selBall.y = 0;

	//  Load bg image, create surface from bg image

	char buff[BUFLEN];
    char *path = app_get_shared_resource_path();

    snprintf(buff, 300, "%s%s", path, "pat2.png");
    bg_image = cairo_image_surface_create_from_png(buff);
    free(path);

}

TBoardView::~TBoardView() {
	// TODO Auto-generated destructor stub
}

Eina_Bool _refresh_graphic(void *data)
{
	TBoardView *bv = (TBoardView *) data;
    bv->RefreshBall();
    return EINA_TRUE;
}
void TBoardView::RefreshBall(){
 if (selBall.x !=0) {

		double x = (selBall.x-1)*squareSize  + left_margin;
		double y = (selBall.y-1)*squareSize  + top_margin;
	 tick +=0.15;

	  DrawSquare(x,y);
	  x = x + squareSize / 2 ;
	  y = y + squareSize / 2 + 9*(1-std::abs(sin(tick)));
	// y = y + squareSize / 2 + 5*ecore_animator_pos_map((sin(tick)+1)/2,ECORE_POS_MAP_BOUNCE , 2,  4  );
	  DrawBall(x,y,linesBoard->square[selBall.x][selBall.y]);

      cairo_surface_flush(surface);

	  /* Display cairo drawing on screen */
	  evas_object_image_data_update_add(image, 0, 0, myWidth, myHeight);

 }

}
void TBoardView::CreateAnimator(){
  tick = 0;
  if (animator != NULL)
  	   ecore_animator_del(animator);
  animator = ecore_animator_add(_refresh_graphic, this);
}

void TBoardView::DeleteAnimator(){
	if (animator != NULL)
	   ecore_animator_del(animator);
}

void TBoardView::MoveBall(double pos) {
	DrawPath(pos);
    cairo_surface_flush(surface);
	evas_object_image_data_update_add(image, 0, 0, myWidth, myHeight);
	if (pos == 1.0) OnEndMoveBall();
}

Eina_Bool move_ball(void *data, double pos)
{
   TBoardView *bv = (TBoardView *) data;
   bv->MoveBall(pos);
   return EINA_TRUE;
}

void TBoardView::CreateMoveBallAnimator(){
	if (animator != NULL)
	  	   ecore_animator_del(animator);
	ecore_animator_timeline_add (1.0, move_ball, this);
}
void TBoardView::DeleteMoveBallAnimator(){

}

Eina_Bool appearance_new_ball(void *data, double pos)
{
   TBoardView *bv = (TBoardView *) data;
   bv->AppearanceNewBall(pos);
   return EINA_TRUE;
}

Eina_Bool disappearance_lines(void *data, double pos)
{
   TBoardView *bv = (TBoardView *) data;
   bv->DisappearanceLines(pos);
   return EINA_TRUE;
}

void TBoardView::OnEndMoveBall(){

	if (linesBoard->checkLines() == 0 )	{
		    NewBalls = linesBoard->addNewBalls();
			ecore_animator_timeline_add (1.0, appearance_new_ball, this);

	}
	else {
		ecore_animator_timeline_add (1.0, disappearance_lines, this);
	}
	//CairoDrawing();

}

void TBoardView::AppearanceNewBall(double pos) {

	for ( TPoint p : NewBalls )
		DrawBall(p,  pos);
	cairo_surface_flush(surface);
	evas_object_image_data_update_add(image, 0, 0, myWidth, myHeight);
}

void TBoardView::DisappearanceLines(double pos){

	for ( TPoint p : linesBoard->clearBalls ){
	    DrawSquare(p);
		DrawBall(p,  1-pos);
	}
    cairo_surface_flush(surface);
	evas_object_image_data_update_add(image, 0, 0, myWidth, myHeight);
}

void TBoardView::OnClick(int x, int y) {
	mx=x;
	my=y;

	int xx =(x-left_margin) / squareSize + 1;
	int yy =(y-top_margin) / squareSize + 1;

    if (linesBoard->square[xx][yy] > 0) {
    	selBall.x = xx;
    	selBall.y = yy;

    	mx=(xx-1)*squareSize + left_margin + squareSize / 2;
        my=(yy-1)*squareSize + top_margin + squareSize / 2;

        CreateAnimator();
    	  //DrawSquare(xx,yy, true);
    }
    else {
    	if (selBall.x == 0) {
        	mx=100;
        	my=100;
        	DeleteAnimator();
    	}
    	else {

    		mx=(xx-1)*squareSize + left_margin + squareSize / 2;
    		my=(yy-1)*squareSize + top_margin + squareSize / 2;

    		destSquare.x = xx;
    		destSquare.y = yy;

    		linesBoard->initSearch(selBall,destSquare);

            if (linesBoard->searchPath(selBall,destSquare) >0) {
            	linesBoard->square[destSquare.x][destSquare.y] = linesBoard->square[selBall.x][selBall.y];
            	linesBoard->square[selBall.x][selBall.y] = 0;
            	 selBall.x = 0;
            	CreateMoveBallAnimator();

            }

    	}

    }
	//linesBoard->initRandom();
	CairoDrawing();
};

void TBoardView::CairoDrawing(){
	cairo_set_source_rgb(cairo, 0.5, 0.5, 1.0);
	cairo_paint(cairo);

	cairo_pattern_t *pattern1 = cairo_pattern_create_for_surface(bg_image);

	cairo_set_source(cairo, pattern1);
	cairo_pattern_set_extend(cairo_get_source(cairo), CAIRO_EXTEND_REPEAT);
	cairo_rectangle(cairo, 0, 0, myWidth, myHeight);
	cairo_fill(cairo);

	DrawTopText();

	DrawBoard();

	DrawBalls();

//	DrawSF();
	//DrawGradienBall();
	//DrawPath(0.5);
	/* Render stacked cairo APIs on cairo context's surface */

	cairo_surface_flush(surface);

	/* Display cairo drawing on screen */
	evas_object_image_data_update_add(image, 0, 0, myWidth, myHeight);

}

void TBoardView::DrawBalls() {
	for(int i=1; i<= linesBoard->sizeX; i++)
	  for(int j=1; j<= linesBoard->sizeY; j++){
			double x = i*squareSize - squareSize / 2 + left_margin;
			double y = j*squareSize - squareSize / 2 + top_margin;
			DrawBall(x,y,linesBoard->square[i][j]);
	  }
}

void TBoardView::DrawSquare(TPoint p){
	double x = (p.x-1)*squareSize  + left_margin;
	double y = (p.y-1)*squareSize  + top_margin;
	DrawSquare(x, y);
}

void TBoardView::DrawSquare(double x, double y){
	SetPatternForSquare(x + squareSize /2, y + squareSize/2, squareSize);
	cairo_rectangle (cairo, x, y, squareSize, squareSize);
	cairo_fill (cairo);
}

void TBoardView::DrawBoard(){

	int BoardWidth = myWidth - 40;

	left_margin = ( myWidth - BoardWidth)/2;

	squareSize = BoardWidth / linesBoard->sizeX;
	int BoardHeight = squareSize * linesBoard->sizeY;
	top_margin = ( myHeight - BoardHeight)/2;

	cairo_set_line_width(cairo, 3);

	for (int x = 0; x< linesBoard->sizeX; x++)
		for (int y = 0; y< linesBoard->sizeY; y++) {
			double xx = x*squareSize  + left_margin;
			double yy = y*squareSize  + top_margin ;
			DrawSquare(xx, yy);
		}

	 cairo_set_source_rgb(cairo, 0.5,0.5,0.5);
	 cairo_set_line_width(cairo, 1);
}

void TBoardView::SetPatternForSquare(int x, int y, int r){

    double r1 = 1.0; double r2 = 1.0;
    double g1 = 242.0/255.0; double g2 = 217.0/255.0;
    double b1 = 204.0/255.0; double b2 = 102.0/255.0;

    cairo_pattern_t *pattern1 = cairo_pattern_create_radial (x - r/4 , y - r/4  , r/2.5 , x, y, 1.5*r);
	cairo_pattern_add_color_stop_rgb(pattern1, 1.0, r1, g1, b1);
	cairo_pattern_add_color_stop_rgb(pattern1, 0.0, r2, g2, b2);

	cairo_set_source(cairo, pattern1);
}

void TBoardView::SetColor(int color){
	switch (color) {
	case 0: cairo_set_source_rgba(cairo, 0.0, 0.0, 0.0, 0.0); break;
	case 1: cairo_set_source_rgba(cairo, 1.0, 0.2, 0.2, 0.9); break;
	case 2: cairo_set_source_rgba(cairo, 0.2, 1.0, 0.2, 0.9); break;
	case 3: cairo_set_source_rgba(cairo, 0.2, 0.2, 1.0, 0.9); break;
	case 4: cairo_set_source_rgba(cairo, 1.0, 1.0, 0.2, 0.9); break;
	case 5: cairo_set_source_rgba(cairo, 1.0, 0.0, 1.0, 0.9); break;
	case 6: cairo_set_source_rgba(cairo, 0.0, 1.0, 1.0, 0.9); break;
	case 7: cairo_set_source_rgba(cairo, 1.0, 1.0, 1.0, 0.9); break;

	default:
	 cairo_set_source_rgba(cairo, 0.0, 0.0, 0.0, 1.0);
	}
}

void TBoardView::SetPattern(double x,double y, int radius, int color){

	double r,g,b;
	switch (color) {
	case 0: r = 0.0; g = 0.0, b = 0.0; break;
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

	cairo_set_source(cairo, pattern1);

}

void TBoardView::DrawBall(TPoint p, double r){
	double x = p.x*squareSize - squareSize / 2 + left_margin;
	double y = p.y*squareSize - squareSize / 2 + top_margin;
	DrawBall(x, y, r, p.color);
}

void TBoardView::DrawBall(TPoint p, double r, int color){
	double x = p.x*squareSize - squareSize / 2 + left_margin;
	double y = p.y*squareSize - squareSize / 2 + top_margin;
	DrawBall(x, y, r, color);
}

void TBoardView::DrawBall(double x, double y, int color){
	DrawBall(x,y,1,color);
}

void TBoardView::DrawBall(double x, double y, double r, int color){
	if (color == 0) return;


	double  radius = r * 3*squareSize / 8;

	//cairo_set_source_rgba(cairo, 1.0, 0.2, 0.2, 0.9);

	//SetColor(color);
	SetPattern(x,y, radius, color);

	cairo_arc(cairo, x, y, radius, 0, 2*M_PI);
	cairo_fill(cairo);
}

void TBoardView::DrawPath(){
	if (linesBoard->path.size()>0) {
		TPoint p = linesBoard->path.front();
		int color =  linesBoard->square[p.x][p.y];
		for ( TPoint p : linesBoard->path ){
			double xx = p.x*squareSize - squareSize / 2 + left_margin;
			double yy = p.y*squareSize - squareSize / 2 + top_margin;
			DrawBall(xx, yy,  0.4, color);
		}

	}

}

void TBoardView::DrawPath(double pos){
	if (linesBoard->path.size() == 0) return;
	double dx = M_PI/linesBoard->path.size();
	for (int i = 0; i<linesBoard->path.size(); i++ ) {
		TPoint p  =  linesBoard->path[i];

		DrawSquare(p);

		double r = cos(dx*i - M_PI*(1-1.5*pos));
		if (r<0) r = 0.0; else r = 0.5*r;

		DrawBall(p, r, p.color);
	}
	if (pos>0.5) {
		TPoint p = linesBoard->path.front();
		DrawBall(p, 1, p.color);
	}

}

void TBoardView::DrawTopText() {

	char text[100] = {0};
    cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

   // if (ad->win_w == 720) {
        cairo_set_font_size(cairo, 50);
        cairo_move_to(cairo, 50.0, 45.0);
   /* } else {
        cairo_set_font_size(ad->cr, 22);
        cairo_move_to(ad->cr, 30.0, 25.0);
    }*/
   // sprintf(text, "w = %d h = %d",myWidth, myHeight);
    sprintf(text, "score = %d ",linesBoard->score);
    cairo_text_path(cairo, text);
    cairo_set_source_rgb(cairo, 127 / 255.0, 127 / 255.0, 127 / 255.0);
    cairo_fill(cairo);

}

//
// test functions
//

void TBoardView::DrawSF() {

	char text[100] = {0};

	cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

	cairo_set_font_size(cairo, 28);
	cairo_set_source_rgb(cairo, 0.0, 0.0, 0.0);

	for(int i=0; i< 11; i++)
	  for(int j=0; j< 11; j++) {
			int xx = i*squareSize  - squareSize  + left_margin;
			int yy = j*squareSize  - squareSize / 2 + top_margin;
			cairo_move_to(cairo, xx, yy);
			sprintf(text, "%d", linesBoard->square[i][j]);
			cairo_text_path(cairo, text);
			cairo_fill(cairo);
	  }

}

void TBoardView::Test7Colors(){

	DrawBall(3,5,1);

	DrawBall(5,3,2);

	DrawBall(7,8,3);

	DrawBall(2,7,4);

	DrawBall(7,2,5);

	DrawBall(8,7,6);

	DrawBall(4,5,7);
}

void  TBoardView::DrawGradienBall(){

	int xx = 100;
	int yy = 140;
	int  r = 3*3*squareSize / 8;

	cairo_set_source_rgba(cairo, 1.0, 0.2, 0.2, 0.9);

	//cairo_pattern_t *pattern1 = cairo_pattern_create_linear(0, 0, r, 0);

	cairo_pattern_t *pattern1 = cairo_pattern_create_radial (xx - r/6, yy - r/3, r/6 , xx, yy, r);


	cairo_pattern_add_color_stop_rgb(pattern1, 1.0, 0.2, 0.65, 0.1);
	cairo_pattern_add_color_stop_rgb(pattern1, 0.0, 0.4, 0.9, 0.2);

	cairo_set_source(cairo, pattern1);
	//SetColor(color);

	cairo_arc(cairo, xx, yy, r, 0, 2*M_PI);
	cairo_fill(cairo);
}
