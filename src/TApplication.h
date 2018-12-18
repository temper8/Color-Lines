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
#include <functional>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "colorlines"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.colorlines"
#endif

class TView;


//typedef bool (*TAppCreateCallback) (void *user_data);
typedef void  (*TAppCreateCallback) ();

class TApplication {
public:
	TApplication();
	virtual ~TApplication();

	static int my_argc;
	static char **my_argv;
	static std::function<void()> _app_cb;

public:

	static int Start(std::function<void()> app_cb);
	static int Start();

	static void Initialize(int argc, char *argv[]);
	static int Run(TView* view);

	static TApplication *instance() { return self; };


private:
	static TApplication *self;


};

#endif /* TAPPLICATION_H_ */
