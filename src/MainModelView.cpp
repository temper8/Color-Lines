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

MainModelView::MainModelView(): linesGame(5,5) {
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
