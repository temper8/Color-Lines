/*
 * TMenuPopupBox.h
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#ifndef TMENUPOPUPBOX_H_
#define TMENUPOPUPBOX_H_

#include "TPopupBox.h"

#include <vector>

class TMenuPopupBox: public TPopupBox {
public:
	TMenuPopupBox(TView *view, std::vector<const char*> buttonList);
	virtual ~TMenuPopupBox();



private:
	Evas_Object * evasRectangleAdd();

};

#endif /* TMENUPOPUPBOX_H_ */
