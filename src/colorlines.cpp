/*
 * colorlines.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#include "colorlines.h"
#include "TApp.h"


int main(int argc, char *argv[])
{
	int ret = 0;
	TApplication::Initialize(argc,argv);
	//ret = TApplication::Run(new TBoardView());
	ret = TApplication::Start([]() {new TApp; });
	//ret = TApplication::Start();
//	ret = TApplication::Run(new TDrawingView());
//	ret = TApplication::Run(new TView());
	return ret;

}
