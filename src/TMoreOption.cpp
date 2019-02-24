/*
 * TMoreOption.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Alex
 */

#include "TMoreOption.h"

#include "logger.h"

static void create_menu(Evas_Object *parent){
	Evas_Object *img = NULL;

	char buf[1024];

	/* Create the new item */
	Eext_Object_Item *item  = eext_more_option_item_append(parent);
	eext_more_option_item_part_text_set(item, "selector,main_text", "test1");
	eext_more_option_item_part_text_set(item, "selector,sub_text", "test1");
	img = elm_image_add(parent);
	/* Set the content in item content part */
	eext_more_option_item_part_content_set(item, "item,icon", img);
	snprintf(buf, sizeof(buf), "%s/music_controller_btn_play.png", app_get_resource_path());
	elm_image_file_set(img, buf, NULL);

	item  = eext_more_option_item_append(parent);
	eext_more_option_item_part_text_set(item, "selector,main_text", "test2");
	eext_more_option_item_part_text_set(item, "selector,sub_text", "sub_2");
	img = elm_image_add(parent);
	/* Set the content in item content part */
	eext_more_option_item_part_content_set(item, "item,icon", img);
	snprintf(buf, sizeof(buf), "%s/music_controller_btn_shuffle_on.png", app_get_resource_path());
	elm_image_file_set(img, buf, NULL);


	item  = eext_more_option_item_append(parent);
	eext_more_option_item_part_text_set(item, "selector,main_text", "exit");
	img = elm_image_add(parent);
	/* Set the content in item content part */
	eext_more_option_item_part_content_set(item, "item,icon", img);
	snprintf(buf, sizeof(buf), "%s/music_controller_btn_repeat_all.png", app_get_resource_path());
	elm_image_file_set(img, buf, NULL);


}
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
	Eext_Object_Item *item = (Eext_Object_Item *)event_info;
	const char *main_text;
	const char *sub_text;
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
	//evas_object_smart_callback_add(more_option, "item,selected", _item_selected, NULL);

	evas_object_smart_callback_add(more_option, "item,clicked", _item_clicked_cb, this);
	evas_object_smart_callback_add(more_option, "item,selected", _item_selected_cb, this);


	//create_menu(more_option);
    addItem("Play","op1","music_controller_btn_play.png", 1);
    addItem("New Game","op2","music_controller_btn_shuffle_on.png", 2);
    addItem("Help","op3","music_controller_btn_repeat_all.png", 3);
    addItem("Exit",nullptr,"music_controller_btn_play.png", 4);
}

TMoreOption::~TMoreOption(){

}
