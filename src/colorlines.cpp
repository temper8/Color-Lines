/*
 * colorlines.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#include "colorlines.h"
#include "TApplication.h"
#include "TView.h"

int main(int argc, char *argv[])
{
	int ret = 0;
	TApplication::Initialize(argc,argv);
	ret = TApplication::Run(new TView());
	return ret;

}
