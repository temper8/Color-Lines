/*
 * TBoardView.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#include "TBoardView.h"
#include "TLinesBoard.h"

TBoardView::TBoardView() {
	// TODO Auto-generated constructor stub
	left_margin = 20;
	top_margin = 100;
	linesBoard = new TLinesBoard(9,9);
}

TBoardView::~TBoardView() {
	// TODO Auto-generated destructor stub
}

void TBoardView::CairoDrawing(){
	cairo_set_source_rgb(cairo, 0.5, 0.5, 1.0);
	cairo_paint(cairo);

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
	cairo_arc(cairo, 250, 250, 60.0, 0, 2*M_PI);

	/* Fill a circle with configured color before (blue) */
	cairo_fill(cairo);

	DrawBoard();

	/* Render stacked cairo APIs on cairo context's surface */
	cairo_surface_flush(surface);

	/* Display cairo drawing on screen */
	evas_object_image_data_update_add(img, 0, 0, myWidth, myHeight);

}


void TBoardView::DrawBoard(){

	int BoardWidth = myWidth - 40;
	int BoardHeight = BoardWidth;

	left_margin = ( myWidth - BoardWidth)/2;
	top_margin = ( myHeight - BoardHeight)/2;

//	  myCanvas.Brush.Color:=clLtGray;
	cairo_set_source_rgba(cairo, 0.3, 0.3, 0.3, 0.3);
	cairo_rectangle (cairo, left_margin, top_margin, BoardWidth, BoardHeight);
	cairo_fill (cairo);

	squareSize = BoardWidth / linesBoard->sizeX;


	 cairo_set_source_rgb(cairo, 1.0,0.0,0.5);

	 cairo_set_line_width(cairo, 1);


	 for(int i = 0; i<linesBoard->sizeX; i++) {
				 cairo_move_to(cairo, left_margin + squareSize*i, top_margin);
				 cairo_line_to(cairo, left_margin + squareSize*i, BoardHeight+top_margin);
	  }

	 for(int i = 0; i<linesBoard->sizeX; i++) {
	 				 cairo_move_to(cairo, left_margin, squareSize*i + top_margin);
	 				 cairo_line_to(cairo, left_margin  + BoardWidth, squareSize*i + top_margin);
	 	  }
	 cairo_stroke(cairo);
}

void TBoardView::DrawTopText() {

	char text[100] = {0};
    cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

   // if (ad->win_w == 720) {
        cairo_set_font_size(cairo, 30);
        cairo_move_to(cairo, 50.0, 45.0);
   /* } else {
        cairo_set_font_size(ad->cr, 22);
        cairo_move_to(ad->cr, 30.0, 25.0);
    }*/
    sprintf(text, "w = %d h = %d",myWidth, myHeight);
    cairo_text_path(cairo, text);
    cairo_set_source_rgb(cairo, 127 / 255.0, 127 / 255.0, 127 / 255.0);
    cairo_fill(cairo);

}
