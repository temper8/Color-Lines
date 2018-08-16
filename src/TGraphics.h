/*
 * TGraphics.h
 *
 *  Created on: May 19, 2017
 *      Author: Alex
 */

#ifndef TGRAPHICS_H_
#define TGRAPHICS_H_

#include <cairo.h>
#include <Elementary.h>

#define LOG_TAG "Color Lines"
#include <dlog.h>

class TCairoGraphics {
public:
	TCairoGraphics();
	virtual ~TCairoGraphics();
	void setParentImage(Evas_Object *image) {myImage = image; };

	void Initialize(int width, int height);

	void LoadBgImage();

	void Flush();
    void FillBackgroud();



    void DrawLine(double x0, double y0, double x1, double x2);
    void DrawRoundRectangle(double x, double y, double w, double h, double r);
    void DrawSquare(double x, double y);
    void DrawBall(double x, double y, double r, int color);
    void DrawScore(double x, double y, int score);
    void DrawScore(double x, double y, const char* caption, int score, int aling);
    void DrawHeaderBG();

    void SetPatternForSquare(int x, int y, int r);
    void SetPattern(double x,double y, int radius, int color);
    void SetColor(int color);
    void SetColor2(int color);

    double squareSize;


    void DrawRing();
    int tx,ty;
    int ring = 0;
    bool goodPath = false;
private:
	Evas_Object *myImage;
	//Evas_Coord width;
	//Evas_Coord height;
	cairo_t *cairo;
	cairo_surface_t *surface;

	cairo_t *myCairo;
	cairo_surface_t *mySurface;
	unsigned char *pixels;

	int myWidth, myHeight;

	cairo_surface_t *bg_image;
};

#endif /* TGRAPHICS_H_ */
