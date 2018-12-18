/*
 * TApplication.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#include "TApplication.h"

#include "TView.h"
#include "TDrawingView.h"
#include "TBoardView.h"

TApplication *TApplication::self = 0;
int TApplication::my_argc = 0;
char **TApplication::my_argv = nullptr;
std::function<void()> TApplication::_app_cb = nullptr;


TApplication::TApplication() {
	self = this;

}

TApplication::~TApplication() {
	// TODO Auto-generated destructor stub
}

static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */

	//	std::function<void()> &app_cb = (std::function<void()>)data;
	//app_cb();

	TApplication::_app_cb();

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	/* Release all resources. */
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/

	int ret;
	char *language;

	ret = app_event_get_language(event_info, &language);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_event_get_language() failed. Err = %d.", ret);
		return;
	}

	if (language != NULL) {
		elm_language_set(language);
		free(language);
	}
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}



void TApplication::Initialize(int argc, char *argv[]) {
	new TApplication();

	TApplication::my_argc = argc;
	TApplication::my_argv = argv;
	app_event_handler_h handlers[5] = {NULL, };

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, nullptr);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, nullptr);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, nullptr);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, nullptr);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, nullptr);
}

int TApplication::Start(std::function<void()> app_cb){

	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};

	dlog_print(DLOG_ERROR, LOG_TAG, "Start");

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	TApplication::_app_cb = app_cb;

	ret = ui_app_main(TApplication::my_argc, TApplication::my_argv, &event_callback, &app_cb);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}
	return ret;
}

int TApplication::Start(){

	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};

	dlog_print(DLOG_ERROR, LOG_TAG, "Start");

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ret = ui_app_main(TApplication::my_argc, TApplication::my_argv, &event_callback, nullptr);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}
	return ret;
}



int TApplication::Run(TView* view) {

//	self->myView = view;

	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ret = ui_app_main(self->my_argc, self->my_argv, &event_callback, self);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;

}
