/*
 * TMenuPopupBox.h
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#ifndef TMENUPOPUPBOX_H_
#define TMENUPOPUPBOX_H_

#include "TPopupBox.h"

class TMenuPopupBox: public TPopupBox {
public:
	TMenuPopupBox(TView *view);
	virtual ~TMenuPopupBox();

private:
	Evas_Object * buttonAdd(const char* title, int tag);
};

#endif /* TMENUPOPUPBOX_H_ */
