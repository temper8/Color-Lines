/*
 * TDrawingView.h
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#ifndef TDRAWINGVIEW_H_
#define TDRAWINGVIEW_H_

#include "TView.h"

class TDrawingView: public TView {
public:
	TDrawingView();
	virtual ~TDrawingView();

private:
	virtual void CreateContent();
};

#endif /* TDRAWINGVIEW_H_ */
