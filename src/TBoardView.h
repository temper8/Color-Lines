/*
 * TBoardView.h
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#ifndef TBOARDVIEW_H_
#define TBOARDVIEW_H_

#include "TDrawingView.h"

class TLinesBoard;
class TBoardView: public TDrawingView {
public:
	TBoardView();
	virtual ~TBoardView();

public:
	virtual void CairoDrawing();

    int squareSize;
    int left_margin,top_margin;

    TLinesBoard* linesBoard;
    void DrawBoard();
    void DrawTopText();
};

#endif /* TBOARDVIEW_H_ */
