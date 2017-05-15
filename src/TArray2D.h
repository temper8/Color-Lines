/*
 * TArray2D.h
 *
 *  Created on: May 15, 2017
 *      Author: Alex
 */

#ifndef TARRAY2D_H_
#define TARRAY2D_H_

#include <array>

class TArray2D {
public:
	TArray2D();
	virtual ~TArray2D();

	void clear();
	void save();
	void load();

	std::array<int, 12> &operator[] (int index ) {return array[index];	};
private:
	std::array<std::array<int, 12>, 12> array;
};

#endif /* TARRAY2D_H_ */
