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

class TCairoGraphics {
public:
	TCairoGraphics();
	virtual ~TCairoGraphics();

	void Create(Evas_Object *obj);
	void Destroy();

	void Initialize(int width, int height);

	void Refresh();
	virtual void Paint() = 0;

	Evas_Object * GetImage() { return myImage; };

protected:

	Evas_Object *myImage;


	int myWidth = 0;
	int myHeight = 0;

	cairo_t *myCairo = nullptr;
	cairo_surface_t *mySurface = nullptr;

};


#endif /* TCAIROGRAPHICS_H_ */
