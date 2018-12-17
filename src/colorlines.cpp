/*
 * colorlines.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#include "colorlines.h"
#include "TApplication.h"


int main(int argc, char *argv[])
{
	int ret = 0;
	TApplication::Initialize(argc,argv);
	//ret = TApplication::Run(new TBoardView());
	ret = TApplication::Start([]() {new TApplication; return true;});
//	ret = TApplication::Run(new TDrawingView());
//	ret = TApplication::Run(new TView());
	return ret;

}
