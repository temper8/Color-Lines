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
#include <map>

class TView;
class TPopupBox {
public:
	TPopupBox(TView *view);
	virtual ~TPopupBox();

	void close();
	void show();

	void btnClick(int tag);
	void btnClick(Evas_Object * btn);
	std::function<void(int)> OnBtnClick;

protected:
	Evas_Object *myPopup;
	TView *myView;
	std::map<Evas_Object *,int > buttons;
};

#endif /* TPOPUPBOX_H_ */
