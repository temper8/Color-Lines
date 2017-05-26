/*
 * TExitPopup.h
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#ifndef TEXITPOPUP_H_
#define TEXITPOPUP_H_

#include "TPopup.h"

class TExitPopup: public TPopup {

public:
	TExitPopup(Evas_Object *win);
	virtual ~TExitPopup();
};

#endif /* TEXITPOPUP_H_ */
