/*
 * TLinesGame.h
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#ifndef TLINESGAME_H_
#define TLINESGAME_H_

#include <vector>

#include "TBoardModel.h"
#include "TPreferenceInt.h"

struct TBall
{
    int x;
    int y;
    int color;
    TBall(int p_x, int p_y, int p_color) :x(p_x), y(p_y), color(p_color) {};
    TBall(int p_x, int p_y) :x(p_x), y(p_y), color(0) {};
    TBall() : x(0), y(0), color(0) {};
};

class TBallsHolder {
public:
	TBallsHolder();
	int balls[3];
	void genNewBalls();
	void load();
	void save();

private:
	TPreferenceInt holder;
};

class TLinesGame {
public:
	TLinesGame(int x,int y);
	virtual ~TLinesGame();

public:

	int sizeX, sizeY;
	TBoardModel board;
	 //std::array<std::array<int, 12>, 12> square;
	//int square[12][12];

	int sf[12][12];
	int counter;
	TPreferenceInt counterGames;
	TPreferenceInt score;
	TPreferenceInt record;
	TBallsHolder ballsHolder;

	void OffsetBoard(int dx);
	bool OutOfBoundary(int x, int y);
	void randThreeBalls();
	bool initBalls;
	std::vector<TBall> path;
	void initPlayingField();
	std::vector<TBall> makeListBalls();
	void initSearch(TBall src);
	int searchPath(TBall src, TBall dst);
	int searchClosestPath(TBall src, TBall dst);
	int checkLines();

	std::vector<TBall> addNewBalls();
	void addNextBalls();
	std::vector<TBall> clearBalls;

	std::vector<TBall> nextBalls;
	void newGame();
	void restoreGame();
	bool gameOver();

private:

	void FillNeighbors( std::vector<TBall> list);
	void checkHorzLine(int x, int y);
    void checkVertLine(int x, int y);
    void checkDiag1Line(int x, int y);
    void checkDiag2Line(int x, int y);
};

#endif /* TLINESGAME_H_ */
