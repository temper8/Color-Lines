/*
 * TMoreOption.h
 *
 *  Created on: Feb 24, 2019
 *      Author: Alex
 */


#ifndef TMOREOPTION_H_
#define TMOREOPTION_H_


#include "colorlines.h"

#include <dlog.h>

class TMoreOption {
public:
	TMoreOption(Evas_Object *parent, const char *part);
	virtual ~TMoreOption();


	void addItem(const char *mainText, const char *subText, const char *iconPath);
    Evas_Object *more_option = nullptr;

};

#endif /* TMOREOPTION_H_ */
