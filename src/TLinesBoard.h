/*
 * TLinesBoard.h
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#ifndef TLINESBOARD_H_
#define TLINESBOARD_H_

class TLinesBoard {
public:
	TLinesBoard(int x,int y);
	virtual ~TLinesBoard();

public:

	int sizeX, sizeY;
	int square[10][10];
	void initRandom();

};

#endif /* TLINESBOARD_H_ */
