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
    int color;
    TPoint(int p_x, int p_y, int p_color) :x(p_x), y(p_y), color(p_color) {};
    TPoint(int p_x, int p_y) :x(p_x), y(p_y), color(0) {};
    TPoint() : x(0), y(0), color(0) {};
};

class TLinesBoard {
public:
	TLinesBoard(int x,int y);
	virtual ~TLinesBoard();

public:

	int sizeX, sizeY;
	int square[12][12];
	int sf[12][12];
	int counter;
	int score;
	int threeBalls[3];
	void randThreeBalls();
	bool initBalls;
	std::vector<TPoint> path;
	void initRandom();
	std::vector<TPoint> AddRandomBalls();
	void initSearch(TPoint src, TPoint dst);
	int searchPath(TPoint src, TPoint dst);
	int checkLines();
	std::vector<TPoint> addNewBalls();

	std::vector<TPoint> clearBalls;

	void newGame();

private:

	void FillNeighbors( std::vector<TPoint> list);
	void checkHorzLine(int x, int y);
    void checkVertLine(int x, int y);
    void checkDiag1Line(int x, int y);
    void checkDiag2Line(int x, int y);
};

#endif /* TLINESBOARD_H_ */
