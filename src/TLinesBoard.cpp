/*
 * TLinesBoard.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#include "TLinesBoard.h"
#include <cstdlib>

TBallsHolder::TBallsHolder(): holder("BallsHolder") {
	if (holder == 0 )
		genNewBalls();
	else
		load();
};

void TBallsHolder::genNewBalls(){
	for (int i=0;i<3;i++)
		balls[i] =  rand() % 7 +1;
	save();
}

void TBallsHolder::load(){
	balls[0] = holder % 10;
	balls[1] = (holder/10) % 10;
	balls[2] = holder/100;
}

void TBallsHolder::save(){
	holder = 100*balls[2] + 10*balls[1] + balls[0];
}


TLinesBoard::TLinesBoard(int x, int y): score("score"), record("record") {
	// TODO Auto-generated constructor stub
	sizeX = x;
	sizeY = y;
	if (score == 0)
		newGame();
	else restoreGame();

}

TLinesBoard::~TLinesBoard() {
	// TODO Auto-generated destructor stub
}

bool TLinesBoard::OutOfBoundary(int x, int y){
	if (x<1) return true;
	if (y<1) return true;
	if (x>sizeX) return true;
	if (y>sizeY) return true;
	return false;
}

void TLinesBoard::newGame() {
	score = 0;
	square.clear();
	initBalls = false;
	initPlayingField();
    ballsHolder.genNewBalls();
}

void TLinesBoard::restoreGame() {
	//score = 0;
	square.load();
	initBalls = true;
	//randThreeBalls();
}


void TLinesBoard::initPlayingField(){
	for(int i=1; i<= sizeX; i++)
	  for(int j=1; j<= sizeY; j++) {
	      square[i][j] = 0;
	      int rnd =  rand() % 35;
	      if (rnd<7)
	    	  square[i][j] = 1 + rnd;
	  }
}

std::vector<TPoint> TLinesBoard::AddRandomBalls(){
	std::vector<TPoint> newBalls;
	for(int i=1; i<= sizeX; i++)
	  for(int j=1; j<= sizeY; j++) {
	      //square[i][j] = 0;
	      //int rnd =  rand() % 35;
	      if (square[i][j]>0){
	    	//  square[i][j] = 1 + rnd;
	      	  newBalls.emplace_back(i, j, square[i][j]);
	      }
	  }
	initBalls = true;
	return newBalls;
}

void TLinesBoard::initSearch(TPoint src, TPoint dst){

     for(int i=1; i< 12; i++)
		for(int j=1; j< 12; j++) {
			if (square[i][j] > 0) sf[i][j] = 100;
	      else sf[i][j] = 0;
		}


     for(int i=1; i< 12; i++) {
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
		    newList.emplace_back(x-1, y);
			n = n + 1;
		}

		if (sf[x+1][y] == 0) {
				    sf[x+1][y] = c;
				    newList.emplace_back(x+1, y);
					n = n + 1;
				}
		if (sf[x][y-1] == 0) {
				    sf[x][y-1] = c;
				    newList.emplace_back(x, y-1);
					n = n + 1;
				}
		if (sf[x][y+1] == 0) {
				    sf[x][y+1] = c;
				    newList.emplace_back(x, y+1);
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
 int color =  square[src.x][src.y];
 if (nn > 0) {
	    path.emplace_back(dst.x, dst.y, color);
	    int n=nn;
	    for (int i = 1; i<nn; i++){
	    	  if (sf[x-1][y] == n-1){
				    path.emplace_back(x-1, y, color);
	                x = x-1;
	    	  }
	    	  else if (sf[x+1][y] == n-1){
				    path.emplace_back(x+1, y, color);
	                x = x+1;
	    	  }
	    	  else if (sf[x][y-1] == n-1) {
				    path.emplace_back(x, y-1, color);
	                y = y-1;
	    	  }
	    	  else if (sf[x][y+1] == n-1) {
				    path.emplace_back(x, y+1, color);
	                y = y+1;
	    	  }
              n = sf[x][y];
	    }
  }

 return nn;

}

int TLinesBoard::checkLines(){
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

 for ( TPoint p : clearBalls ) {
	 square[p.x][p.y] = 0;
 }

 score +=clearBalls.size();

 if (score>record) record = score;

 return clearBalls.size();
}

void TLinesBoard::checkHorzLine(int x, int y){
	int color = square[x][y];
	int xx =x+1;
	  while (square[xx][y] == color)
	        xx =xx+1;
	  int len = xx-x;
	  if (len >4) {
		  for (int i = 0; i<len; i++) {
			    clearBalls.emplace_back(x+i, y, color);
		  }
	  }
}

void TLinesBoard::checkVertLine(int x, int y){
	int color = square[x][y];
	int yy =y+1;
	  while (square[x][yy] == color)
	        yy =yy+1;
	  int len = yy-y;
	  if (len >4) {
		  for (int i = 0; i<len; i++) {
			    clearBalls.emplace_back(x, y+i, color);
		  }
	  }
}

void TLinesBoard::checkDiag1Line(int x, int y){
	int color = square[x][y];
	int xx =x+1;
	int yy =y+1;
	  while (square[xx][yy] == color)
	  	  {	xx++;  yy++; }

	  int len = xx-x;
	  if (len >4) {
		  for (int i = 0; i<len; i++) {
			    clearBalls.emplace_back(x+i, y+i, color);
		  }
	  }

}

void TLinesBoard::checkDiag2Line(int x, int y){
	int color = square[x][y];
	int xx =x+1;
	int yy =y-1;
	  while (square[xx][yy] == color)
	  	  {  xx++;  yy--;  }

	  int len = xx-x;
	  if (len >4) {
		  for (int i = 0; i<len; i++) {
			    clearBalls.emplace_back(x+i,y-i, color);
		  }
	  }
}


std::vector<TPoint> TLinesBoard::addNewBalls(){
	std::vector<TPoint> emptySquares;
	std::vector<TPoint> newBalls;

	for(int x = 1; x<=sizeX; x++)
	for(int y = 1; y<=sizeY; y++){
	   if ( square[x][y] == 0){
		   emptySquares.emplace_back(x,y);
	   }
	 }

	if (emptySquares.size()>2) {
		 int new1 =  rand() % emptySquares.size();
		 int new2 =  rand() % (emptySquares.size()-1);
		 int new3 =  rand() % (emptySquares.size()-2);

         if (new1<=new2) new2 = new2 + 1;
         if (new1<=new3) new3 = new3 + 1;
         if (new2<=new3) new3 = new3 + 1;

         newBalls.emplace_back(emptySquares[new1].x, emptySquares[new1].y, ballsHolder.balls[0]);
         newBalls.emplace_back(emptySquares[new2].x, emptySquares[new2].y, ballsHolder.balls[1]);
         newBalls.emplace_back(emptySquares[new3].x, emptySquares[new3].y, ballsHolder.balls[2]);

         for (TPoint p :newBalls ) {
        	 square[p.x][p.y] = p.color;
         }
         square.save();
         ballsHolder.genNewBalls();

		return newBalls;
	}
	else {
		return newBalls;
	}
}
