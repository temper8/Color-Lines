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
