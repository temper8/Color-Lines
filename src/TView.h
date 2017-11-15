/*
 * TView.h
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#ifndef TVIEW_H_
#define TVIEW_H_

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>

#define LOG_TAG "Color Lines"

#include <dlog.h>

class TView {
public:
	TView();
	virtual ~TView();
	virtual void OnAppCreate();

	friend void callback_back(void *data, Evas_Object *obj, void *event_info);
	friend void callback_more(void *data, Evas_Object *obj, void *event_info);

public:

	Evas_Object *win;
	Evas_Object *conform;


	virtual void OnResize(int width, int height) {};

private:

	virtual void callbackMore() = 0;
	virtual void callbackBack() = 0;

private:
	void CreateWin(const char *pkg_name);
	virtual void CreateContent();

};

#endif /* TVIEW_H_ */
