/*
 * TMoreOption.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Alex
 */

#include "TMoreOption.h"

#include "logger.h"

#include "GameApp.h"

void TMoreOption::setIcon(Evas_Object *img, const char* icon){
	char buf[1024];
	snprintf(buf, sizeof(buf), "%s/%s", app_get_resource_path(), icon);
	elm_image_file_set(img, buf, NULL);
}

void TMoreOption::addItem(const char *mainText, const char *subText, const char *iconPath, int tag){

#ifdef WEARABLE
	/* Create the new item */
	Eext_Object_Item *item  = eext_more_option_item_append(more_option);
	eext_more_option_item_part_text_set(item, "selector,main_text", mainText);
	eext_more_option_item_part_text_set(item, "selector,sub_text", subText);
	Evas_Object *img  = elm_image_add(more_option);
	/* Set the content in item content part */
	eext_more_option_item_part_content_set(item, "item,icon", img);
	setIcon(img, iconPath);

	items.insert(std::make_pair((Evas_Object*)item, tag));

#endif
}

void TMoreOption::checkItemClick(Evas_Object *item){
	Evas_Object *image =  eext_more_option_item_part_content_get((Eext_Object_Item*)item, "item,icon");
	if (image == NULL) return;
	MainModelView *m = &GameApp::instance()->modelView;
	if (m->animator->soundPlayer.isSoundEnabled == 0)
	{
		m->animator->soundPlayer.isSoundEnabled = 1;
		setIcon(image, "baseline_music_off_black_18dp.png");
	}
	else {
		m->animator->soundPlayer.isSoundEnabled = 0;
		setIcon(image, "baseline_music_note_black_18dp.png");
	}

}


void TMoreOption::itemClick(Evas_Object *item){
	int tag = items[item];
	DBG("itemClick tag =%d", tag);

	if (tag == 4)
		checkItemClick(item);
	else
	{
		eext_more_option_opened_set(more_option, EINA_FALSE);
		if (OnItemClick!=nullptr) OnItemClick(tag);
	}

}
#ifdef WEARABLE
static void _item_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	DBG("itemSelect!!");
}

static void _item_clicked_cb(void *user_data, Evas_Object *obj, void *event_info)
{
	TMoreOption *mo = (TMoreOption *)user_data;
	//DBG("itemClick!!");
	//eext_more_option_opened_set(obj, EINA_FALSE);
	mo->itemClick((Evas_Object *)event_info);
}

static void _more_option_opened(void *user_data, Evas_Object *obj, void *event_info)
{
	TMoreOption *mo = (TMoreOption *)user_data;
	if (mo->OnOpened!=nullptr) mo->OnOpened();
}

static void _more_option_closed(void *user_data, Evas_Object *obj, void *event_info)
{
	TMoreOption *mo = (TMoreOption *)user_data;
	if (mo->OnClosed!=nullptr) mo->OnClosed();
}
#endif

TMoreOption::TMoreOption(Evas_Object *parent, const char *part){
#ifdef WEARABLE
	more_option = eext_more_option_add(parent);
	elm_panel_hidden_set(more_option, EINA_TRUE);
	//evas_object_show(more_option);
	elm_object_part_content_set(parent, part, more_option);

	/* Add smart callback */
	evas_object_smart_callback_add(more_option, "more,option,opened", _more_option_opened, this);
	evas_object_smart_callback_add(more_option, "more,option,closed", _more_option_closed, this);

	evas_object_smart_callback_add(more_option, "item,clicked", _item_clicked_cb, this);
	evas_object_smart_callback_add(more_option, "item,selected", _item_selected_cb, this);


	//create_menu(more_option);
    addItem("Play","Continue game","baseline_play_circle_filled_black_18dp.png", 1);
    addItem("New Game",nullptr,"baseline_add_circle_black_18dp.png", 2);
    addItem("Help","About game","baseline_help_black_18dp.png", 3);
    addItem("Sound On","Enable sound","baseline_help_black_18dp.png", 4);
  //  addItem("Exit",nullptr,"tw_ic_popup_btn_delete.png", 4);
#endif
}

TMoreOption::~TMoreOption(){

}
