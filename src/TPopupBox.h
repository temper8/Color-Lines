/*
 * TPopupBox.h
 *
 *  Created on: May 26, 2017
 *      Author: Alex
 */

#ifndef TPOPUPBOX_H_
#define TPOPUPBOX_H_

#include <functional>

#include <Elementary.h>

class TPopupBox {
public:
	TPopupBox(Evas_Object *win);
	virtual ~TPopupBox();

	void close();
	void show();

	std::function<void(int)> result;

protected:
	Evas_Object *myPopup;
	Evas_Object *myWin;
};

#endif /* TPOPUPBOX_H_ */
