/*
 * TApp.h
 *
 *  Created on: Dec 18, 2018
 *      Author: Alex
 */

#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include "TApplication.h"
#include "TView.h"
#include "TDrawingView.h"
#include "TBoardView.h"
#include "MainModelView.h"

class GameApp: public TApplication {
public:
	GameApp();
	virtual ~GameApp();

	MainModelView modelView;



	static GameApp *instance() { return static_cast<GameApp*>(self); };
};

#endif /* GAMEAPP_H_ */
