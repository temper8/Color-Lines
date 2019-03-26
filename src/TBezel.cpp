/*
 * TBezel.cpp
 *
 *  Created on: Dec 11, 2017
 *      Author: Alex
 */

#include <colorlines.h>
#include "TBezel.h"
#include "logger.h"
#include <efl_extension.h>
#include <system_settings.h>
#include <system_info.h>


TBezel::TBezel() {
	// TODO Auto-generated constructor stub

}

TBezel::~TBezel() {
	// TODO Auto-generated destructor stub
}

#ifdef WEARABLE

static  Eina_Bool eext_rotary_event_cb(void *data, Evas_Object *obj,  Eext_Rotary_Event_Info *info){
	TBezel *v = (TBezel *) data;
	DBG("bezel eext_rotary_event_cb");
	if (info->direction == EEXT_ROTARY_DIRECTION_CLOCKWISE)
	   {
		 v->OnValueChenged(1.0);
	   }
	   else
	   {
		   v->OnValueChenged(-1.0);
	   }
	return EINA_TRUE;
}
#endif

bool TBezel::isSupportBezel(){
	bool value;
	int ret;

	ret = system_info_get_platform_bool("http://tizen.org/feature/input.rotating_bezel", &value);
	if (ret != SYSTEM_INFO_ERROR_NONE) {
	        /* Error handling */

	        return false;
	    }

	 //  dlog_print(DLOG_INFO, LOG_TAG, "Model name: %s", value);

	  return value;
}


void TBezel::Attach(Evas_Object *obj){
#ifdef WEARABLE
	if (isSupportBezel()){
		eext_rotary_object_event_activated_set(obj, EINA_TRUE);
			eext_rotary_object_event_callback_add(obj, eext_rotary_event_cb, this);
	}
#endif
}
