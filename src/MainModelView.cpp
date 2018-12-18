/*
 * MainModelView.cpp
 *
 *  Created on: Dec 18, 2018
 *      Author: Alex
 */

#include "MainModelView.h"

#include <string>
#include <fstream>
#include <sstream>
#include <app.h>
#include <Elementary.h>
#include <system_settings.h>

#include "TPopupBox\TExitPopupBox.h"
#include "TPopupBox\TMenuPopupBox.h"
#include "TPopupBox\TInfoBox.h"
#include "TPopupBox\TGameOverBox.h"

MainModelView::MainModelView(): linesGame(5,5), myPopupBox(NULL)  {
	// TODO Auto-generated constructor stub
	loadHelp();
}

MainModelView::~MainModelView() {
	// TODO Auto-generated destructor stub
}


void MainModelView::loadHelp() {
    std::string filename(app_get_shared_resource_path());
    filename.append("help.en");
    std::ifstream t(filename.c_str());
    std::stringstream buffer;
    buffer << t.rdbuf();
    if (buffer.str().length()>0)
    	helpText = buffer.str();
    else {
    	helpText = "Game rules<br>Oops, an error occurred.";
    }
}

void  MainModelView::showMenu(){
	if (myPopupBox!=NULL) ClosePopupBox();
	myPopupBox = new TMenuPopupBox({"Continue", "New Game", "Game Rules","Exit"});
	myPopupBox->OnBtnClick = [this](int tag) {
										ClosePopupBox();
										switch(tag) {
											case 1: break;
											case 2: NewGame(); break;
											case 3: ShowHelp(); break;
											case 4: ui_app_exit(); break;
											}
										};
	myPopupBox->show();
}

void MainModelView::ClosePopupBox(){
	delete myPopupBox;
	myPopupBox = NULL;
}

void MainModelView::ShowHelp(){
	myPopupBox = new TInfoBox(helpText.c_str());
	myPopupBox->OnBtnClick = [this](int ) { ClosePopupBox(); };
	myPopupBox->show();
}
void MainModelView::ShowGameOverBox(){

}
void MainModelView::NewGame(){

}
