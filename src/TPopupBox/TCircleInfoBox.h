/*
 * TCircleInfoBox.h
 *
 *  Created on: Feb 24, 2019
 *      Author: Alex
 */

#ifndef TCIRCLEINFOBOX_H_
#define TCIRCLEINFOBOX_H_

#include "TPopupBox.h"

class TCircleInfoBox: public TPopupBox {
public:
	TCircleInfoBox(const char* text);
	virtual ~TCircleInfoBox();
};

#endif /* TCIRCLEINFOBOX_H_ */
