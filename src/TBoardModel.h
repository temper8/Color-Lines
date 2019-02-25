/*
 * TBoard.h
 *
 *  Created on: May 15, 2017
 *      Author: Alex
 */

#ifndef TBOARDMODEL_H_
#define TBOARDMODEL_H_

#include <array>

class TBoardModel {
public:
	TBoardModel();
	virtual ~TBoardModel();

	void clear();
	void save();
	void load();

	std::array<int, 12> &operator[] (int index ) {return array[index];	};
private:
	std::array<std::array<int, 12>, 12> array;
};

#endif /* TBOARDMODEL_H_ */
