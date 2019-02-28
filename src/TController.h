/*
 * TController.h
 *
 *  Created on: Feb 28, 2019
 *      Author: Alex
 */

#ifndef TCONTROLLER_H_
#define TCONTROLLER_H_

#include "TImage.h"

class TController {
public:
	TController(TImage *img);
	virtual ~TController();

	TImage *image;
};

#endif /* TCONTROLLER_H_ */
