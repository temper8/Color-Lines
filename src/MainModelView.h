/*
 * MainModelView.h
 *
 *  Created on: Dec 18, 2018
 *      Author: Alex
 */

#ifndef MAINMODELVIEW_H_
#define MAINMODELVIEW_H_

#include "TLinesGame.h"


class MainModelView {
public:
	MainModelView();
	virtual ~MainModelView();

	TLinesGame linesGame;

	std::string helpText;
	void loadHelp();
};

#endif /* MAINMODELVIEW_H_ */
