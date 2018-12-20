/*
 * TGraphics.cpp
 *
 *  Created on: May 19, 2017
 *      Author: Alex
 */

#include "TGraphics.h"
#include <app.h>
//#include <Elementary.h>
//#include <system_settings.h>
//#include <efl_extension.h>


#define BUFLEN 500

TCairoGraphics::TCairoGraphics():surface(NULL) {
	// TODO Auto-generated constructor stub

}

TCairoGraphics::~TCairoGraphics() {
	// TODO Auto-generated destructor stub
}

void TCairoGraphics::Initialize(int width, int height){


	dlog_print(DLOG_DEBUG, LOG_TAG, " Initialize x:%d y:%d", width, height);

	myWidth = width;
	myHeight = height;

	if (surface) {
		/* Destroy previous cairo canvas */
		cairo_surface_destroy(surface);
		cairo_destroy(cairo);
		surface = NULL;
		cairo = NULL;
	}

	/* When window resize event occurred
		If no cairo surface exist or destroyed
		Create cairo surface with resized Window size */
	if (!surface) {
		/* Get screen size */
		//evas_object_geometry_get(obj, NULL, NULL, &s_info.width, &s_info.height);

		/* Set image size */
		evas_object_image_size_set(myImage, width, height);
		evas_object_resize(myImage, width, height);
		evas_object_show(myImage);

		/* Create new cairo canvas for resized window */
		pixels = (unsigned char*)evas_object_image_data_get(myImage, 1);
	//	surface = cairo_image_surface_create( CAIRO_FORMAT_ARGB32, width, height);
//		cairo = cairo_create(surface);

		//my
		surface = cairo_image_surface_create_for_data(pixels, CAIRO_FORMAT_ARGB32, width, height, width * 4);
		cairo = cairo_create(surface);
		//cairo = myCairo;
		//DrawMask();
	}
}

void TCairoGraphics::DrawRing(){
	if (ring>0){
		cairo_save (cairo);
		if (goodPath) SetColor2(ring);
		else SetColor2(0);
		cairo_arc(cairo, tx, ty, 80, 0, 2*M_PI);
		cairo_set_line_width(cairo, 30);
		cairo_stroke(cairo);
		cairo_restore (cairo);
	}
}

void TCairoGraphics::LoadBgImage(){
	//  Load bg image, create surface from bg image

	char buff[BUFLEN];
    char *path = app_get_shared_resource_path();

    snprintf(buff, 300, "%s%s", path, "pat9.png");
    bg_image = cairo_image_surface_create_from_png(buff);
    free(path);
}

void TCairoGraphics::Refresh()
{
    evas_object_image_pixels_dirty_set(myImage, EINA_TRUE);
}


void TCairoGraphics::Flush(){

	//dlog_print(DLOG_DEBUG, LOG_TAG, " cairo_surface_flush");


	/* Render stacked cairo APIs on cairo context's surface */
	cairo_surface_flush(surface);

//	cairo_set_source_surface (myCairo, surface, 0, 0);
//	cairo_paint (myCairo);

//	DrawRing();

//	cairo_surface_flush(mySurface);
	/* Display cairo drawing on screen */
	evas_object_image_data_update_add(myImage, 0, 0, myWidth, myHeight);

}

void TCairoGraphics::FillBackgroud(){

	cairo_set_source_rgb(cairo, 0.5, 0.5, 1.0);
	cairo_paint(cairo);

	cairo_pattern_t *pattern1 = cairo_pattern_create_for_surface(bg_image);

	cairo_set_source(cairo, pattern1);
	cairo_pattern_set_extend(cairo_get_source(cairo), CAIRO_EXTEND_REPEAT);
	cairo_rectangle(cairo, 0, 0, myWidth, myHeight);
	cairo_fill(cairo);

}

void TCairoGraphics::DrawLine(double x0, double y0, double x1, double y1){

	cairo_set_source_rgba(cairo, 0.0/255.0, 250.0/255.0, 250.0/255.0, 1.0);
	cairo_set_line_width(cairo, 5);

	cairo_move_to(cairo, x0, y0);
	cairo_line_to(cairo, x1, y1);
	//cairo_close_path (cairo);
	cairo_stroke(cairo);
	//cairo_fill (cairo);
}

void TCairoGraphics::DrawRoundRectangle(double x, double y, double w, double h, double r){
	cairo_move_to (cairo, x+r, y);
	cairo_rel_line_to (cairo, w-2*r, 0);
	cairo_rel_line_to (cairo, r, r);
	cairo_rel_line_to (cairo, 0, h-2*r);
	cairo_rel_line_to (cairo, -r, r);
	cairo_rel_line_to (cairo, -w+2*r, 0);
	cairo_rel_line_to (cairo, -r, -r);
	cairo_rel_line_to (cairo, 0, -h+2*r);
	cairo_close_path (cairo);
}

void TCairoGraphics::DrawSquare(double x, double y){

	cairo_pattern_t *pattern1 = cairo_pattern_create_for_surface(bg_image);

	cairo_set_source(cairo, pattern1);
	cairo_pattern_set_extend(cairo_get_source(cairo), CAIRO_EXTEND_REPEAT);
	DrawRoundRectangle(x+2, y+2, squareSize-4, squareSize-4, 5);
	cairo_fill(cairo);


	SetPatternForSquare(x + squareSize /2, y + squareSize/2, squareSize-4);
	//cairo_set_source_rgba(cairo, 128.0/255.0, 128.0/255.0, 128.0/255.0, 0.35);
	DrawRoundRectangle(x+2, y+2, squareSize-4, squareSize-4, 5);
	cairo_fill (cairo);
	//cairo_set_source_rgba(cairo, 250.0/255.0, 250.0/255.0, 250.0/255.0, 1.0);
	//cairo_rectangle (cairo, x+2, y+2, squareSize-4, squareSize-4);
	//DrawRoundRectangle(x+2, y+2, squareSize-4, squareSize-4, 5);
	//cairo_set_line_width(cairo, 1);
	//cairo_stroke(cairo);
	//cairo_fill (cairo);
}


void TCairoGraphics::SetPatternForSquare(int x, int y, int r){
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

	cairo_set_source(cairo, pattern1);
}

void TCairoGraphics::SetPattern(double x,double y, int radius, int color){

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

	cairo_set_source(cairo, pattern1);

}
void TCairoGraphics::SetColor2(int color){
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


void TCairoGraphics::SetColor(int color){
	switch (color) {
	case 0: cairo_set_source_rgba(cairo, 0.5, 0.5, 0.5, 0.9); break;
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

void TCairoGraphics::DrawBall(double x, double y, double r, int color){

	//if (color == 0) return;

	double  radius = r * 3*squareSize / 8;

	//cairo_set_source_rgba(cairo, 1.0, 0.2, 0.2, 0.9);

	//SetColor(color);
	SetPattern(x,y, radius, color);

	cairo_arc(cairo, x, y, radius, 0, 2*M_PI);
	cairo_fill(cairo);
}


void TCairoGraphics::DrawScore(double x, double y, const char* caption, int score, int aling){

	char text[16] = {0};
    sprintf(text, "%0*d",4, score);

    double x1 = x;
    double x2 = x;

    cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cairo, 3*squareSize/7);
	cairo_text_extents_t extents;
	cairo_text_extents (cairo, text, &extents);
	switch (aling){
	case 1:x2 = x - extents.width; break;
	case 2:x2 = x - extents.width/2;break;
	}
	double yy = y - extents.height - 8;
    cairo_move_to(cairo, x2, y);
    cairo_text_path(cairo, text);
    cairo_set_source_rgb(cairo, 127 / 255.0, 127 / 255.0, 127 / 255.0);
    cairo_fill(cairo);


	cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cairo, 2*squareSize/7);
	cairo_text_extents (cairo, caption, &extents);
	switch (aling){
	case 1:x1 = x1 - extents.width; break;
	case 2:x1 = x1 - extents.width/2;break;
	}
    cairo_move_to(cairo, x1, yy);
    cairo_text_path(cairo, caption);
    cairo_set_source_rgb(cairo, 127 / 255.0, 127 / 255.0, 127 / 255.0);
    cairo_fill(cairo);


}

void TCairoGraphics::DrawScore(double x, double y, int score){
	char text[16] = {0};
    cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

    cairo_set_font_size(cairo, 50);
    cairo_move_to(cairo, x, y);

    sprintf(text, "%d",score);
    cairo_text_path(cairo, text);
    cairo_set_source_rgb(cairo, 127 / 255.0, 127 / 255.0, 127 / 255.0);
    cairo_fill(cairo);
}

void TCairoGraphics::DrawHeaderBG(){
	int HeaderHeight = squareSize+20;

	//cairo_pattern_t *pattern1 = cairo_pattern_create_for_surface(bg_image);
	//cairo_set_source(cairo, pattern1);
	//cairo_pattern_set_extend(cairo_get_source(cairo), CAIRO_EXTEND_REPEAT);

	cairo_set_source_rgb(cairo, 255.0/255.0, 217.0/255.0, 102.0/255.0);

	cairo_rectangle(cairo, 0, 0, myWidth, HeaderHeight);
	cairo_fill(cairo);
}
