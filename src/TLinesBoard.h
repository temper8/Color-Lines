/*
 * TLinesBoard.h
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#ifndef TLINESBOARD_H_
#define TLINESBOARD_H_

#include <vector>


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

	int sizeX, sizeY;
	int square[11][11];
	int sf[11][11];
	int counter;
	std::vector<TPoint> path;
	void initRandom();
	void initSearch(TPoint src, TPoint dst);
	int searchPath(TPoint src, TPoint dst);
	void CheckLines();
	void addNewBalls();

private:
	void FillNeighbors( std::vector<TPoint> list);
};

#endif /* TLINESBOARD_H_ */
