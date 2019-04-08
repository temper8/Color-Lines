/*
 * TArray2D.cpp
 *
 *  Created on: May 15, 2017
 *      Author: Alex
 */

#include "TBoardModel.h"

#include <string>
#include <app_preference.h>

#include "logger.h"

static const char *key = "Board";

TBoardModel::TBoardModel() {
	// TODO Auto-generated constructor stub

}

TBoardModel::~TBoardModel() {
	// TODO Auto-generated destructor stub
}

void TBoardModel::initSize(int x, int y){
	sizeX = x;
	sizeY = y;
}

void TBoardModel::clear(){
	   for(auto &i: array) for(auto &k: i) k = 0;
	   array[1][1] = 10;
	   array[sizeX][1] = 10;
	   array[1][sizeY] = 10;
	   array[sizeX][sizeY] = 10;
}

void TBoardModel::save(){
	std::string out_str;
	for(auto &i: array) for(auto &k: i) out_str.push_back((char)k + 48);
	preference_set_string(key, out_str.c_str());
	DBG("out key %s out_str = %s.", key, out_str.c_str());
}

void TBoardModel::load(){
	bool existing;
	int ret = preference_is_existing(key, &existing);
	if (ret != PREFERENCE_ERROR_NONE) {
		//dlog_print(DLOG_ERROR, LOG_TAG, "%s() failed. Err = %d.", func_name, ret);
		clear();
		return ;
	}

	if (existing) {
		char *str;
		ret = preference_get_string(key, &str);
		if (ret == PREFERENCE_ERROR_NONE) {
			DBG("get key %s value = %s.", key, str);
			int i = 0;
			for(auto &row: array) for(auto &k: row) k = (int)str[i++] - 48;
		}
	}
}

bool TBoardModel::OutOfBoundary(int x, int y){
	if (x<1) return true;
	if (y<1) return true;
	if (x>sizeX) return true;
	if (y>sizeY) return true;
	if ((array[x][y]==10)) return true;
	return false;
}

std::vector<TBall> TBoardModel::getAllBalls(){
	std::vector<TBall> newBalls;
	for(int i=1; i<= sizeX; i++)
	  for(int j=1; j<= sizeY; j++) {
	      if ((array[i][j]>0)&&(array[i][j]<10)){
	      	  newBalls.emplace_back(i, j, array[i][j]);
	      }
	  }
	//initBalls = true;
	return newBalls;
}

void TBoardModel::setRandomBalls(int nuberOfColors){
	clear();
	int BallsCount = 0;
	for(int i=1; i<= sizeX; i++)
	for(int j=1; j<= sizeY; j++) {
	      if (array[i][j] == 10) continue;
	      int rnd =  rand() % (nuberOfColors*3);
	      if (BallsCount > 6) break;
	      if (rnd<nuberOfColors)
	      {
	    	  array[i][j] = 1 + rnd;
	    	  BallsCount++;
	      }

	  }
}
