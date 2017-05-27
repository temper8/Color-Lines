/*
 * TInfoBox.h
 *
 *  Created on: May 27, 2017
 *      Author: Alex
 */

#ifndef TINFOBOX_H_
#define TINFOBOX_H_

#include "TPopupBox.h"

class TInfoBox: public TPopupBox {
public:
	TInfoBox(TView *view);
	virtual ~TInfoBox();
};

#endif /* TINFOBOX_H_ */
