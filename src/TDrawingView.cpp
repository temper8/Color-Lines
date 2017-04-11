/*
 * TDrawingView.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#include "TDrawingView.h"

TDrawingView::TDrawingView() {
	// TODO Auto-generated constructor stub

}

TDrawingView::~TDrawingView() {
	// TODO Auto-generated destructor stub
}

void TDrawingView::CreateContent(){
	/* Label */
	/* Create an actual view of the base gui.
	   Modify this part to change the view. */
	label = elm_label_add(conform);
	elm_object_text_set(label, "<align=center>Hello Drawing View</align>");
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(conform, label);

}
