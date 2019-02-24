/*
 * TMoreOption.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: Alex
 */

#include "TMoreOption.h"


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
void TMoreOption::addItem(const char *mainText, const char *subText, const char *iconPath){
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
}

TMoreOption::TMoreOption(Evas_Object *parent, const char *part){
	more_option = eext_more_option_add(parent);
	evas_object_show(more_option);
	elm_object_part_content_set(parent, part, more_option);

	//create_menu(more_option);
    addItem("Option1","op1",music_controller_btn_play.png);
    addItem("Option2","op2",music_controller_btn_shuffle_on.png);
    addItem("Option3","op3",music_controller_btn_repeat_all.png);
    addItem("Option4","op4",music_controller_btn_play.png);
}

TMoreOption::~TMoreOption(){

}