/*
 * TImage.h
 *
 *  Created on: Dec 19, 2018
 *      Author: Alex
 */

#ifndef TIMAGE_H_
#define TIMAGE_H_


#include <cairo.h>

#include "TGraphics.h"

class TImage {
public:
	TImage(Evas_Object *conform);
	virtual ~TImage();

	TCairoGraphics graphics;

	Evas_Object *image;
	Evas_Coord width;
	Evas_Coord height;
};

#endif /* TIMAGE_H_ */
