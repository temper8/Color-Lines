/*
 * TBoardView.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#include "TBoardView.h"

TBoardView::TBoardView() {
	// TODO Auto-generated constructor stub

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

	 /* Set blue color with opacity 0.3 value */
	 cairo_set_source_rgba(cairo, 0.2, 0.2, 1.0, 0.3);

	/* Draw a circle radius 10 on center point (x,y)
	   this circle displays the text start point */
	cairo_arc(cairo, 250, 250, 60.0, 0, 2*M_PI);

	/* Fill a circle with configured color before (blue) */
	cairo_fill(cairo);



	/* Render stacked cairo APIs on cairo context's surface */
	cairo_surface_flush(surface);

	/* Display cairo drawing on screen */
	evas_object_image_data_update_add(img, 0, 0, myWidth, myHeight);

}
