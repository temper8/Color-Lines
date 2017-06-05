/*
 * TApplication.h
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#ifndef TAPPLICATION_H_
#define TAPPLICATION_H_

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "colorlines"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.colorlines"
#endif

class TView;

class TApplication {
public:
	TApplication();
	virtual ~TApplication();

	int my_argc;
	char **my_argv;

public:

	static void Initialize(int argc, char *argv[]);
	static int Run(TView* view);

	static TApplication *instance() { return self; };
	TView* view() { return myView; };

private:
	static TApplication *self;
	TView* myView;
};

#endif /* TAPPLICATION_H_ */
