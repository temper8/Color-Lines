/*
 * TExitPopup.h
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#ifndef TEXITPOPUP_H_
#define TEXITPOPUP_H_

#include "TPopupBox.h"

class TExitPopup: public TPopupBox {

public:
	TExitPopup(Evas_Object *win);
	virtual ~TExitPopup();
};

#endif /* TEXITPOPUP_H_ */
