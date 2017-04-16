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

}

TLinesBoard::~TLinesBoard() {
	// TODO Auto-generated destructor stub
}

void TLinesBoard::initRandom(){
	for(int i=1; i<= sizeX; i++)
	  for(int j=1; j<= sizeY; j++) {
	      square[i][j] = 0;
	      int rnd =  rand() % 25;
	      if (rnd<7)
	    	  square[i][j] = 1 + rnd;
	  }
}


void TLinesBoard::initSearch(TPoint src, TPoint dst){

     for(int i=1; i< 11; i++)
		for(int j=1; j< 11; j++) {
			if (square[i][j] > 0) sf[i][j] = 100;
	      else sf[i][j] = 0;
		}


     for(int i=1; i< 11; i++) {
         sf[sizeX+1][i] = 100;
         sf[0][i] = 100;
         sf[i][sizeY+1] = 100;
         sf[i][0] = 100;
     }

     counter = 1;
     std::vector<TPoint> list;
     list.push_back(src);
     sf[src.x][src.y] = counter;
     FillNeighbors(list);
}

void TLinesBoard::FillNeighbors( std::vector<TPoint> list){


	std::vector<TPoint> newList;

	int n = 0;
	int x = list[0].x;
	int y = list[0].y;
	int c = sf[x][y] + 1;

	for ( TPoint p : list ) {
		int x = p.x;
		int y = p.y;
		if (sf[x-1][y] == 0) {
		    sf[x-1][y] = c;
		    TPoint np;
		    np.x = x-1;
		    np.y = y;
		    newList.push_back(np);
			n = n + 1;
		}

		if (sf[x+1][y] == 0) {
				    sf[x+1][y] = c;
				    TPoint np;
				    np.x = x+1;
				    np.y = y;
				    newList.push_back(np);
					n = n + 1;
				}
		if (sf[x][y-1] == 0) {
				    sf[x][y-1] = c;
				    TPoint np;
				    np.x = x;
				    np.y = y-1;
				    newList.push_back(np);
					n = n + 1;
				}
		if (sf[x][y+1] == 0) {
				    sf[x][y+1] = c;
				    TPoint np;
				    np.x = x;
				    np.y = y+1;
				    newList.push_back(np);
					n = n + 1;
				}

	}
	if (n>0) FillNeighbors(newList);
}

int TLinesBoard::searchPath(TPoint src, TPoint dst){

 path.clear();

 int x =dst.x;
 int y =dst.y;
 int nn = sf[x][y];

 if (nn > 0) {
	    path.push_back(dst);
	    int n=nn;
	    for (int i = 1; i<nn; i++){
	    	  if (sf[x-1][y] == n-1){
				    TPoint np;
				    np.x = x-1;
				    np.y = y;
				    path.push_back(np);
	                x = x-1;
	    	  }
	    	  else if (sf[x+1][y] == n-1){
				    TPoint np;
				    np.x = x+1;
				    np.y = y;
				    path.push_back(np);
	                x = x+1;
	    	  }
	    	  else if (sf[x][y-1] == n-1) {
				    TPoint np;
				    np.x = x;
				    np.y = y-1;
				    path.push_back(np);
	                y = y-1;
	    	  }
	    	  else if (sf[x][y+1] == n-1) {
				    TPoint np;
				    np.x = x;
				    np.y = y+1;
				    path.push_back(np);
	                y = y+1;
	    	  }
              n = sf[x][y];
	    }
  }

 return nn;

}

void TLinesBoard::CheckLines(){
 clearBalls.clear();
 for(int x = 1; x<=sizeX; x++)
 for(int y = 1; y<=sizeY; y++){
   if ( square[x][y]>0){
	   checkHorzLine(x,y);
       checkVertLine(x,y);
       checkDiag1Line(x,y);
       checkDiag2Line(x,y);
   }
 }

 for ( TPoint p : clearBalls )
	 square[p.x][p.y] = 0;

}

void TLinesBoard::checkHorzLine(int x, int y){

}
void TLinesBoard::checkVertLine(int x, int y){

}
void TLinesBoard::checkDiag1Line(int x, int y){

}
void TLinesBoard::checkDiag2Line(int x, int y){

}


void TLinesBoard::addNewBalls(){

}
