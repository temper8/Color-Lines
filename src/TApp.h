/*
 * TApp.h
 *
 *  Created on: Dec 18, 2018
 *      Author: Alex
 */

#ifndef TAPP_H_
#define TAPP_H_

#include "TApplication.h"
#include "TView.h"
#include "TDrawingView.h"
#include "TBoardView.h"
#include "MainModelView.h"

class TApp: public TApplication {
public:
	TApp();
	virtual ~TApp();

	MainModelView modelView;



	static TApp *instance() { return static_cast<TApp*>(self); };
};

#endif /* TAPP_H_ */
