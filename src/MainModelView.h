/*
 * MainModelView.h
 *
 *  Created on: Dec 18, 2018
 *      Author: Alex
 */

#ifndef MAINMODELVIEW_H_
#define MAINMODELVIEW_H_

#include "TLinesGame.h"

class TPopupBox;

enum class DeviceType{
	mobile,
	wearable
};

class TAnimator;
class MainModelView {

public:
	MainModelView();
	virtual ~MainModelView();

	TLinesGame linesGame;
	TAnimator *animator;
	std::string helpText;
	void loadHelp();
	void showMenu();
	DeviceType deviceType = DeviceType::mobile;
private:
    TPopupBox* myPopupBox;
    bool isSupportBezel();
public:
    void ClosePopupBox();
    void ShowHelp();
    void ShowGameOverBox();
    void NewGame();
};

#endif /* MAINMODELVIEW_H_ */
