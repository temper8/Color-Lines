/*
 * TBoard.h
 *
 *  Created on: May 15, 2017
 *      Author: Alex
 */

#ifndef TBOARDMODEL_H_
#define TBOARDMODEL_H_

#include <array>
#include <vector>

struct TBall
{
    int x;
    int y;
    int color;
    TBall(int p_x, int p_y, int p_color) :x(p_x), y(p_y), color(p_color) {};
    TBall(int p_x, int p_y) :x(p_x), y(p_y), color(0) {};
    TBall() : x(0), y(0), color(0) {};
};

class TBoardModel {
public:
	TBoardModel();
	virtual ~TBoardModel();

	void initSize(int x, int y);
	void clear();
	void save();
	void load();


	void setRandomBalls(int nuberOfColors);

	bool OutOfBoundary(int x, int y);

	std::vector<TBall> getAllBalls();

	std::array<int, 12> &operator[] (int index ) {return array[index];	};
private:
	std::array<std::array<int, 12>, 12> array;
	int sizeX, sizeY;
};

#endif /* TBOARDMODEL_H_ */
