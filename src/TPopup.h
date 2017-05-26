/*
 * TPopup.h
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#ifndef TPOPUP_H_
#define TPOPUP_H_

#include <Elementary.h>

class TPopup {
public:
	TPopup(Evas_Object *win);
	virtual ~TPopup();

	void close();
	void show();

protected:
	Evas_Object *myPopup;
	Evas_Object *myWin;
};

#endif /* TPOPUP_H_ */
