/*
 * TBoardView.h
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#ifndef TBOARDVIEW_H_
#define TBOARDVIEW_H_

#include "TDrawingView.h"

class TBoardView: public TDrawingView {
public:
	TBoardView();
	virtual ~TBoardView();

public:
	virtual void CairoDrawing();
};

#endif /* TBOARDVIEW_H_ */
