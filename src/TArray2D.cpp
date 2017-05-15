/*
 * TArray2D.cpp
 *
 *  Created on: May 15, 2017
 *      Author: Alex
 */

#include "TArray2D.h"

TArray2D::TArray2D() {
	// TODO Auto-generated constructor stub

}

TArray2D::~TArray2D() {
	// TODO Auto-generated destructor stub
}

void TArray2D::clear(){
	   for(auto &i: array) for(auto &k: i) k = 0;
}

void TArray2D::save(){

}

void TArray2D::load(){

}
