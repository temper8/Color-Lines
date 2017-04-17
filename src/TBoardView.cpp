/*
 * TBoardView.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#include "TBoardView.h"

#define BUFLEN 500

TBoardView::TBoardView() {
	// TODO Auto-generated constructor stub
	mx = 250;
	my = 250;
	linesBoard = new TLinesBoard(9,9);
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

void TBoardView::OnClick(int x, int y) {
	mx=x;
	my=y;

	int xx =(x-left_margin) / squareSize + 1;
	int yy =(y-top_margin) / squareSize + 1;

    if (linesBoard->square[xx][yy] > 0) {
    	selBall.x = xx;
    	selBall.y = yy;
    	linesBoard->path.clear();
    	mx=(xx-1)*squareSize + left_margin + squareSize / 2;
        my=(yy-1)*squareSize + top_margin + squareSize / 2;
    	  //DrawSquare(xx,yy, true);
    }
    else {
    	if (selBall.x == 0) {
        	mx=100;
        	my=100;
    	}
    	else {

    		mx=(xx-1)*squareSize + left_margin + squareSize / 2;
    		my=(yy-1)*squareSize + top_margin + squareSize / 2;

    		destSquare.x = xx;
    		destSquare.y = yy;

    		linesBoard->initSearch(selBall,destSquare);

            if (linesBoard->searchPath(selBall,destSquare) >0) {

            	linesBoard->square[xx][yy] = linesBoard->square[selBall.x][selBall.y];
            	linesBoard->square[selBall.x][selBall.y] = 0;
            	if (linesBoard->checkLines() == 0 )
            			linesBoard->addNewBalls();
                selBall.x = 0;
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

//	cairo_set_line_width (cairo, 0.1);
//	cairo_set_source_rgb (cairo, 0, 0, 0);
//	cairo_rectangle (cairo, 50,50, 100, 100);
//	cairo_stroke (cairo);

//	cairo_set_source_rgb (cairo, 0, 0, 0);
//	cairo_rectangle (cairo, 25, 25, 50, 50);
//	cairo_fill (cairo);

	DrawTopText();
	 /* Set blue color with opacity 0.3 value */
	 cairo_set_source_rgba(cairo, 0.2, 0.2, 1.0, 0.3);

	/* Draw a circle radius 10 on center point (x,y)
	   this circle displays the text start point */
	cairo_arc(cairo, mx, my, 40.0, 0, 2*M_PI);

	/* Fill a circle with configured color before (blue) */
	cairo_fill(cairo);

	DrawBoard();

	DrawBalls();

//	DrawSF();

	DrawPath();
	/* Render stacked cairo APIs on cairo context's surface */
	cairo_surface_flush(surface);

	/* Display cairo drawing on screen */
	evas_object_image_data_update_add(image, 0, 0, myWidth, myHeight);

}

void TBoardView::DrawBalls() {
	for(int i=1; i<= linesBoard->sizeX; i++)
	  for(int j=1; j<= linesBoard->sizeY; j++)
		  DrawBall(i,j,linesBoard->square[i][j]);

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

void TBoardView::DrawBoard(){

	int BoardWidth = myWidth - 40;
	int BoardHeight = BoardWidth;

	left_margin = ( myWidth - BoardWidth)/2;
	top_margin = ( myHeight - BoardHeight)/2;

//	  myCanvas.Brush.Color:=clLtGray;
	cairo_set_source_rgba(cairo, 0.3, 0.3, 0.3, 0.6);
//	cairo_rectangle (cairo, left_margin, top_margin, BoardWidth, BoardHeight);
//	cairo_fill (cairo);

	squareSize = BoardWidth / linesBoard->sizeX;
	cairo_set_line_width(cairo, 3);

	for (int x = 0; x< linesBoard->sizeX; x++)
		for (int y = 0; y< linesBoard->sizeX; y++) {
			int xx = x*squareSize  + left_margin;
			int yy = y*squareSize  + top_margin ;
			cairo_rectangle (cairo, xx, yy, squareSize - 3 ,squareSize - 3);
			cairo_fill (cairo);
			//cairo_stroke(cairo);
		}


	 cairo_set_source_rgb(cairo, 0.5,0.5,0.5);

	 cairo_set_line_width(cairo, 1);

/*
	 for(int i = 0; i<linesBoard->sizeX; i++) {
				 cairo_move_to(cairo, left_margin + squareSize*i, top_margin);
				 cairo_line_to(cairo, left_margin + squareSize*i, BoardHeight+top_margin);
	  }

	 for(int i = 0; i<linesBoard->sizeX; i++) {
	 				 cairo_move_to(cairo, left_margin, squareSize*i + top_margin);
	 				 cairo_line_to(cairo, left_margin  + BoardWidth, squareSize*i + top_margin);
	 	  }
	 cairo_stroke(cairo);
	 */
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

void TBoardView::DrawBall(int x, int y, int color){
	if (color == 0) return;

	int xx = x*squareSize - squareSize / 2 + left_margin;
	int yy = y*squareSize - squareSize / 2 + top_margin;
	int  r = 3*squareSize / 8;

	//cairo_set_source_rgba(cairo, 1.0, 0.2, 0.2, 0.9);

	SetColor(color);

	cairo_arc(cairo, xx, yy, r, 0, 2*M_PI);
	cairo_fill(cairo);
}

void TBoardView::DrawPath(){
	if (linesBoard->path.size()>0) {
		TPoint p = linesBoard->path.front();
		int color =  linesBoard->square[p.x][p.y];
		for ( TPoint p : linesBoard->path )
			DrawPathBall(p.x, p.y, color);
	}

}

void TBoardView::DrawPathBall(int x, int y, int color){

	int xx = x*squareSize - squareSize / 2 + left_margin;
	int yy = y*squareSize - squareSize / 2 + top_margin;
	int  r = 3*squareSize / 16;

	//cairo_set_source_rgba(cairo, 0.0, 0.0, 0.0, 1.0);

	SetColor(color);

	cairo_arc(cairo, xx, yy, r, 0, 2*M_PI);
	cairo_fill(cairo);
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
