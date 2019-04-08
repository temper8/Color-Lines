/*
 * TMoreOption.h
 *
 *  Created on: Feb 24, 2019
 *      Author: Alex
 */


#ifndef TMOREOPTION_H_
#define TMOREOPTION_H_


#include "colorlines.h"

#include <Elementary.h>

#include <functional>
#include <map>

#ifdef WEARABLE
class TMoreOption {
public:
	TMoreOption(Evas_Object *parent, const char *part);
	virtual ~TMoreOption();


	void addItem(const char *mainText, const char *subText, const char *iconPath, int tag);
	void addCheckItem(const char *mainText, const char *subText, int tag);

	std::function<void()> OnOpened;
	std::function<void()> OnClosed;
	std::function<void(int)> OnItemClick;
	void itemClick(Evas_Object *item);
	void checkItemClick(Evas_Object *item);
	//void setIcon(Evas_Object *img, const char* icon);

    Evas_Object *more_option = nullptr;
	std::map<Evas_Object *,int > items;



};
#endif
#endif /* TMOREOPTION_H_ */
