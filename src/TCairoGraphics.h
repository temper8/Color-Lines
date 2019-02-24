/*
 * TCairoGraphics.h
 *
 *  Created on: Dec 25, 2018
 *      Author: Alex
 */

#ifndef TCAIROGRAPHICS_H_
#define TCAIROGRAPHICS_H_

#include <cairo.h>
#include <Elementary.h>

class TCairoImage {
public:
	TCairoImage();
	virtual ~TCairoImage();

	void Create(Evas_Object *obj);
	void Destroy();

	void Initialize(int width, int height);

	void Refresh();
	virtual void Paint() = 0;

	Evas_Object * GetImage() { return myImage; };

	Evas_Object *myImage;

protected:




	int myWidth = 0;
	int myHeight = 0;

	cairo_t *myCairo = nullptr;
	cairo_surface_t *mySurface = nullptr;

};


#endif /* TCAIROGRAPHICS_H_ */
