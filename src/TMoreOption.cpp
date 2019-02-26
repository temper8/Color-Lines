/*
 * TMoreOption.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Alex
 */

#include "TMoreOption.h"

#include "logger.h"


void TMoreOption::addItem(const char *mainText, const char *subText, const char *iconPath, int tag){
	char buf[1024];

	/* Create the new item */
	Eext_Object_Item *item  = eext_more_option_item_append(more_option);
	eext_more_option_item_part_text_set(item, "selector,main_text", mainText);
	eext_more_option_item_part_text_set(item, "selector,sub_text", subText);
	Evas_Object *img  = elm_image_add(more_option);
	/* Set the content in item content part */
	eext_more_option_item_part_content_set(item, "item,icon", img);
	snprintf(buf, sizeof(buf), "%s/%s", app_get_resource_path(), iconPath);
	elm_image_file_set(img, buf, NULL);   
	items.insert(std::make_pair((Evas_Object*)item, tag));
}

void TMoreOption::itemClick(Evas_Object *item){
	int tag = items[item];
	DBG("itemClick tag =%d", tag);
	//close();
	if (OnItemClick!=nullptr) OnItemClick(tag);
}

static void _item_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
	DBG("itemSelect!!");
}

static void _item_clicked_cb(void *user_data, Evas_Object *obj, void *event_info)
{
	TMoreOption *mo = (TMoreOption *)user_data;

	DBG("itemClick!!");
	eext_more_option_opened_set(obj, EINA_FALSE);
	mo->itemClick((Evas_Object *)event_info);
}


TMoreOption::TMoreOption(Evas_Object *parent, const char *part){
	more_option = eext_more_option_add(parent);
	elm_panel_hidden_set(more_option, EINA_TRUE);
	//evas_object_show(more_option);
	elm_object_part_content_set(parent, part, more_option);

	/* Add smart callback */
	//evas_object_smart_callback_add(more_option, "more,option,opened", _more_option_opened, NULL);
	//evas_object_smart_callback_add(more_option, "more,option,closed", _more_option_closed, NULL);

	evas_object_smart_callback_add(more_option, "item,clicked", _item_clicked_cb, this);
	evas_object_smart_callback_add(more_option, "item,selected", _item_selected_cb, this);


	//create_menu(more_option);
    addItem("Play","Continue game","baseline_play_circle_filled_black_18dp.png", 1);
    addItem("New Game",nullptr,"baseline_add_circle_black_18dp.png", 2);
    addItem("Help","About game","baseline_help_black_18dp.png", 3);
  //  addItem("Exit",nullptr,"tw_ic_popup_btn_delete.png", 4);
}

TMoreOption::~TMoreOption(){

}
