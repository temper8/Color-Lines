/*
 * TMenuPopupBox.h
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#ifndef TMENUPOPUPBOX_H_
#define TMENUPOPUPBOX_H_

#include "TPopupBox.h"
#include <map>
#include <vector>

class TMenuPopupBox: public TPopupBox {
public:
	TMenuPopupBox(TView *view, std::vector<const char*> buttonList);
	virtual ~TMenuPopupBox();

	void btnClick2(Evas_Object * btn);

private:
	Evas_Object * buttonAdd(const char* title, int tag);
	std::map<Evas_Object *,int > buttons;
};

#endif /* TMENUPOPUPBOX_H_ */
