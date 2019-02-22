/*
 * TView.h
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#ifndef TVIEW_H_
#define TVIEW_H_


#include "colorlines.h"

#include <dlog.h>

class TView {
public:
	TView();
	virtual ~TView();

//	friend void callback_back(void *data, Evas_Object *obj, void *event_info);
//	friend void callback_more(void *data, Evas_Object *obj, void *event_info);

public:

	Evas_Object *win = nullptr;
	Evas_Object *conform = nullptr;
	Evas_Object *layout = nullptr;
	Evas_Object *nf = nullptr;
	Evas_Object *more_option = nullptr;

	Eext_Circle_Surface *circle_surface = nullptr;

	virtual void OnResize(int width, int height) {};

private:

	virtual void OnMenuKeyClick() = 0;
	virtual void OnBackKeyClick() = 0;

private:
	void Create_Base_GUI_Mobile(const char *pkg_name);
	void Create_Base_GUI_Wearable(const char *pkg_name);
	virtual void CreateContent();

	void create_win(const char *pkg_name);
	void create_conform();
	void create_naviframe();
};

#endif /* TVIEW_H_ */
