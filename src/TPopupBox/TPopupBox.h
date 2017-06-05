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
	TPopupBox();
	virtual ~TPopupBox();

	void close();
	void show();

	void btnClick(int tag);
	void btnClick(Evas_Object * btn);
	std::function<void(int)> OnBtnClick;

protected:
	Evas_Object *myPopup;
	std::map<Evas_Object *,int > buttons;
	Evas_Object * elmButtonAdd(const char* title, const char* style, int tag);
};

#endif /* TPOPUPBOX_H_ */
