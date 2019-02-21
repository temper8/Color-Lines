/*
 * TPopupBoxFactory.h
 *
 *  Created on: Feb 19, 2019
 *      Author: Alex
 */

#ifndef TPOPUPBOX_TPOPUPBOXFACTORY_H_
#define TPOPUPBOX_TPOPUPBOXFACTORY_H_

#include "TMenuPopupBox.h"

class TPopupBoxFactory {
public:
	TPopupBoxFactory();
	virtual ~TPopupBoxFactory();

	static void DeletePopupBox();
	static TPopupBox* CreateMenuPopupBox(std::vector<const char*> buttonList);

private:
	static TPopupBox* myPopupBox;
};

#endif /* TPOPUPBOX_TPOPUPBOXFACTORY_H_ */
