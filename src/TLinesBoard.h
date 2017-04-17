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
	int score;
	std::vector<TPoint> path;
	void initRandom();
	void initSearch(TPoint src, TPoint dst);
	int searchPath(TPoint src, TPoint dst);
	int checkLines();
	bool addNewBalls();

private:
	std::vector<TPoint> clearBalls;
	void FillNeighbors( std::vector<TPoint> list);
	void checkHorzLine(int x, int y);
    void checkVertLine(int x, int y);
    void checkDiag1Line(int x, int y);
    void checkDiag2Line(int x, int y);
};

#endif /* TLINESBOARD_H_ */
