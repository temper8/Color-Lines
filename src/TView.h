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

class TView {
public:
	TView();
	virtual ~TView();
	void Create();

public:

	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;

	virtual void Resize(int width, int height) {};

private:
	void CreateWin(const char *pkg_name);
	virtual void CreateContent();

};

#endif /* TVIEW_H_ */
