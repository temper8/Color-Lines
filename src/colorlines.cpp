/*
 * colorlines.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#include "colorlines.h"
#include "TApplication.h"

int
main(int argc, char *argv[])
{
	int ret = 0;
	TApplication::Initialize();
	ret = TApplication::Run(argc,argv);
	return ret;

}
