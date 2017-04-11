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


class TApplication {
public:
	TApplication();
	virtual ~TApplication();

public:
	static TApplication *Instance;
	static void Initialize();
	static int Run(int argc, char *argv[]);


	void create_base_gui();
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;

};

#endif /* TAPPLICATION_H_ */
