/*
 * TLinesBoard.h
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#ifndef TLINESBOARD_H_
#define TLINESBOARD_H_

struct TPoint
{
    int x;
    int y;
};

class TLinesBoard {
public:
	TLinesBoard(int x,int y);
	virtual ~TLinesBoard();

public:
	TPoint selBall;
	int sizeX, sizeY;
	int square[10][10];
	void initRandom();

};

#endif /* TLINESBOARD_H_ */
