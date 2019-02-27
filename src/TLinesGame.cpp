/*
 * TLinesBoard.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#include "TLinesGame.h"

#include <cstdlib>

const int LineLength = 4;
const int BallColors = 6;

TBallsHolder::TBallsHolder(): holder("BallsHolder") {
	if (holder == 0 )
		genNewBalls();
	else
		load();
};

void TBallsHolder::genNewBalls(){
	for (int i=0;i<3;i++)
		balls[i] =  rand() % BallColors +1;
	save();
}
/*
std::vector<TBall> TLinesGame::makeListBalls(){
	std::vector<TBall> newBalls;
	for(int i=1; i<= sizeX; i++)
	  for(int j=1; j<= sizeY; j++) {
	      if (board[i][j]>0){
	      	  newBalls.emplace_back(i, j, board[i][j]);
	      }
	  }
	initBalls = true;
	return newBalls;
}
*/
void TBallsHolder::load(){
	balls[0] = holder % 10;
	balls[1] = (holder/10) % 10;
	balls[2] = holder/100;
}

void TBallsHolder::save(){
	holder = 100*balls[2] + 10*balls[1] + balls[0];
}


TLinesGame::TLinesGame(int x, int y): counterGames("counterGames"), score("score"), record("record") {
	// TODO Auto-generated constructor stub
	sizeX = x;
	sizeY = y;
	board.initSize(x, y);
	if (counterGames == 0)
		newGame();
	else restoreGame();

}

TLinesGame::~TLinesGame() {
	// TODO Auto-generated destructor stub
}



void TLinesGame::newGame() {
	counterGames+=1;
	score = 0;
	//board.clear();
	initBalls = false;
	//initPlayingField();
	board.setRandomBalls(BallColors);
    ballsHolder.genNewBalls();
    addNextBalls();
    board.save();
}

void TLinesGame::restoreGame() {
	//score = 0;
	board.load();
	initBalls = false;
	//randThreeBalls();
}

/*
void TLinesGame::initPlayingField(){
	board.clear();
	for(int i=1; i<= sizeX; i++)
	for(int j=1; j<= sizeY; j++) {
	      if (board[i][j] == 10) continue;
	      int rnd =  rand() % (BallColors*3);
	      if (rnd<BallColors)
	    	  board[i][j] = 1 + rnd;
	  }
}
*/


void TLinesGame::initSearch(TBall src){

     for(int i=1; i< 12; i++)
		for(int j=1; j< 12; j++) {
			if (board[i][j] > 0) sf[i][j] = 100;
	      else sf[i][j] = 0;
		}


     for(int i=1; i< 12; i++) {
         sf[sizeX+1][i] = 100;
         sf[0][i] = 100;
         sf[i][sizeY+1] = 100;
         sf[i][0] = 100;
     }

     counter = 1;
     std::vector<TBall> list;
     list.push_back(src);
     sf[src.x][src.y] = counter;
     FillNeighbors(list);
}

void TLinesGame::FillNeighbors( std::vector<TBall> list){


	std::vector<TBall> newList;

	int n = 0;
	int x = list[0].x;
	int y = list[0].y;
	int c = sf[x][y] + 1;

	for ( TBall p : list ) {
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

int TLinesGame::searchClosestPath(TBall src, TBall dst){
	int rmin = 100000;
	int x,y;
    for(int i=1; i<= sizeX; i++)
    for(int j=1; j<= sizeY; j++) {
			if ((sf[i][j] != 100)&&(sf[i][j] != 0)){
				int r = (dst.x - i)*(dst.x - i) + (dst.y - j)*(dst.y - j) + sf[i][j];
				if (r<rmin){
					rmin = r;
					x = i;
					y = j;
				}
			}
		}
    if (rmin<100000){
    	return searchPath(src, TBall(x,y));
    }
    else
    	return 0;
}

int TLinesGame::searchPath(TBall src, TBall dst){

 path.clear();

 int x =dst.x;
 int y =dst.y;
 int nn = sf[x][y];
 int color =  board[src.x][src.y];
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

int TLinesGame::checkLines(){
 clearBalls.clear();
 for(int x = 1; x<=sizeX; x++)
 for(int y = 1; y<=sizeY; y++){
   if ((board[x][y]>0)&&(board[x][y]<10)){
	   checkHorzLine(x,y);
       checkVertLine(x,y);
       checkDiag1Line(x,y);
       checkDiag2Line(x,y);
   }
 }

 for ( TBall p : clearBalls ) {
	 board[p.x][p.y] = 0;
 }

 board.save();

 score +=clearBalls.size();

 if (score>record) record = score;


 return clearBalls.size();
}

void TLinesGame::checkHorzLine(int x, int y){
	int color = board[x][y];
	int xx =x+1;
	  while (board[xx][y] == color)
	        xx =xx+1;
	  int len = xx-x;
	  if (len >=LineLength) {
		  for (int i = 0; i<len; i++) {
			    clearBalls.emplace_back(x+i, y, color);
		  }
	  }
}

void TLinesGame::checkVertLine(int x, int y){
	int color = board[x][y];
	int yy =y+1;
	  while (board[x][yy] == color)
	        yy =yy+1;
	  int len = yy-y;
	  if (len >=LineLength) {
		  for (int i = 0; i<len; i++) {
			    clearBalls.emplace_back(x, y+i, color);
		  }
	  }
}

void TLinesGame::checkDiag1Line(int x, int y){
	int color = board[x][y];
	int xx =x+1;
	int yy =y+1;
	  while (board[xx][yy] == color)
	  	  {	xx++;  yy++; }

	  int len = xx-x;
	  if (len >=LineLength) {
		  for (int i = 0; i<len; i++) {
			    clearBalls.emplace_back(x+i, y+i, color);
		  }
	  }

}

void TLinesGame::checkDiag2Line(int x, int y){
	int color = board[x][y];
	int xx =x+1;
	int yy =y-1;
	  while (board[xx][yy] == color)
	  	  {  xx++;  yy--;  }

	  int len = xx-x;
	  if (len >=LineLength) {
		  for (int i = 0; i<len; i++) {
			    clearBalls.emplace_back(x+i,y-i, color);
		  }
	  }
}

bool TLinesGame::gameOver(){
	for(int x = 1; x<=sizeX; x++)
	for(int y = 1; y<=sizeY; y++){
	   if ( board[x][y] == 0){
		   return false;
	   }
	 }
	return true;
}
void TLinesGame::addNextBalls(){
	std::vector<TBall> emptySquares;
//	std::vector<TBall> newBalls;
	nextBalls.clear();
	for(int x = 1; x<=sizeX; x++)
	for(int y = 1; y<=sizeY; y++){
	   if ((board[x][y] == 0)&&( board[x][y] <10)){
		   emptySquares.emplace_back(x,y);
	   }
	 }

	if (emptySquares.size()>3) {
		 int new1 =  rand() % emptySquares.size();
		 int new2 =  rand() % (emptySquares.size()-1);
		 int new3 =  rand() % (emptySquares.size()-2);

         if (new1<=new2) new2 = new2 + 1;
         if (new1<=new3) new3 = new3 + 1;
         if (new2<=new3) new3 = new3 + 1;

         nextBalls.emplace_back(emptySquares[new1].x, emptySquares[new1].y, ballsHolder.balls[0]);
         nextBalls.emplace_back(emptySquares[new2].x, emptySquares[new2].y, ballsHolder.balls[1]);
         nextBalls.emplace_back(emptySquares[new3].x, emptySquares[new3].y, ballsHolder.balls[2]);

        // for (TBall p :nextBalls ) {
       // 	 board[p.x][p.y] = p.color;
       //  }
        // board.save();
        // ballsHolder.genNewBalls();
        // nextBalls = newBalls;
		//return newBalls;
	}
	else {
		int i = 0;
		for (TBall p :emptySquares ) {
			nextBalls.emplace_back(p.x, p.y, ballsHolder.balls[i]);
		        	// board[p.x][p.y] = ballsHolder.balls[i++];
		         }
		//return newBalls;
	}

	 ballsHolder.genNewBalls();
}

std::vector<TBall> TLinesGame::addNewBalls(){
	std::vector<TBall> emptySquares;
	std::vector<TBall> newBalls;

	int color = 0;
    for (TBall p :nextBalls ) {
    	if(board[p.x][p.y] == 0) {
    		board[p.x][p.y] = p.color;
    		newBalls.emplace_back(p.x,p.y,p.color);
    	}
    	else {
			color = p.color;
		}

    }

    if (color>0){
    	for(int x = 1; x<=sizeX; x++)
    	for(int y = 1; y<=sizeY; y++){
    	   if ( board[x][y] == 0){
    			   emptySquares.emplace_back(x,y);
    		   }
    		 }
    		int new1 =  rand() % emptySquares.size();
    		board[emptySquares[new1].x][emptySquares[new1].y] = color;
    	    newBalls.emplace_back(emptySquares[new1].x, emptySquares[new1].y, color);
    }

    board.save();

    //nextBalls = newBalls;
    return newBalls;
}


void TLinesGame::OffsetBoard(int dx){
	int tmp[12][12];
	for(int x = 1; x<=sizeX; x++)
	for(int y = 1; y<=sizeY; y++){
		int k = x + dx;
		if (k<1)
			k = sizeX+k;
		else
			if(k > sizeX) k = k - sizeX;
	    tmp[x][y]= board[k][y];
	}

	for(int x = 1; x<=sizeX; x++)
	for(int y = 1; y<=sizeY; y++){

	     board[x][y] = tmp[x][y];
	}

	std::vector<TBall> tmpBalls;
	for (TBall p :nextBalls ) {
		 int k = p.x - dx;
		 if (k<1)
		 	k = sizeX+k;
		 else
	 	if(k > sizeX) k = k - sizeX;
		tmpBalls.emplace_back(k, p.y, p.color);
	}
	nextBalls.clear();
	for (TBall p :tmpBalls ) {
		nextBalls.emplace_back(p);
	}

	/*
	 for (TBall p :nextBalls ) {
		 int k = p.x + dx;
		 if (k<1)
		 	k = sizeX+k;
		 else
		 	if(k > sizeX) k = k - sizeX;
		 p.x = 3;
	 }
	 */
}
