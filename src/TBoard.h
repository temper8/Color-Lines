/*
 * TBoard.h
 *
 *  Created on: May 15, 2017
 *      Author: Alex
 */

#ifndef TBOARD_H_
#define TBOARD_H_

#include <array>

class TBoard {
public:
	TBoard();
	virtual ~TBoard();

	void clear();
	void save();
	void load();

	std::array<int, 12> &operator[] (int index ) {return array[index];	};
private:
	std::array<std::array<int, 12>, 12> array;
};

#endif /* TBOARD_H_ */
