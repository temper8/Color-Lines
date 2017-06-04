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

class TView;
class TPopupBox {
public:
	TPopupBox(TView *view);
	virtual ~TPopupBox();

	void close();
	void show();

	void btnClick(int tag);
	std::function<void(TView*, int)> OnBtnClick;

protected:
	Evas_Object *myPopup;
	TView *myView;
};

#endif /* TPOPUPBOX_H_ */
