/*
 * TLinesBoard.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#include "TLinesBoard.h"
#include <cstdlib>


TLinesBoard::TLinesBoard(int x, int y) {
	// TODO Auto-generated constructor stub
	sizeX = x;
	sizeY = y;
	selBall.x = 0;
	selBall.y = 0;
}

TLinesBoard::~TLinesBoard() {
	// TODO Auto-generated destructor stub
}

void TLinesBoard::initRandom(){
	for(int i=1; i<= sizeX; i++)
	  for(int j=1; j<= sizeY; j++) {
	      square[i][j] = 0;
	      int rnd =  rand() % 30;
	      if (rnd<8)
	    	  square[i][j] =  1 + rnd;
	  }
}
