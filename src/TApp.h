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

class TApp: public TApplication {
public:
	TApp();
	virtual ~TApp();

	TView* myView;
	TView* view() { return myView; };

	void OnApplicationCreate();
};

#endif /* TAPP_H_ */
