/*
 * TBoardView.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#include "TBoardView.h"

#include <cmath>

#include <fstream>
#include <sstream>      // std::stringstream, std::stringbuf

#include "TExitPopupBox.h"
#include "TMenuPopupBox.h"
#include "TInfoBox.h"

static Eina_Bool
add_random_balls(void *data)
{
	TBoardView *bv = (TBoardView *) data;
	bv->AddRandomBalls();

   return EINA_FALSE;
}

TBoardView::TBoardView(): myPopupBox(NULL) {
	// TODO Auto-generated constructor stub
	loadHelp();

	linesBoard = new TLinesBoard(8,11);
	//linesBoard->initRandom();
	selBall.x = 0;
	selBall.y = 0;

    graphics.LoadBgImage();

    ecore_timer_add(0.5, add_random_balls, this);
}

TBoardView::~TBoardView() {
	// TODO Auto-generated destructor stub
}

static Evas_Object *popup = NULL;

void TBoardView::NewGame(){
	linesBoard->newGame();
	selBall.x = 0;
	selBall.y = 0;
	CairoDrawing();
	ecore_timer_add(0.5, add_random_balls, this);
}

void TBoardView::loadHelp() {
   // auto filename = "my-file.txt";
	char filename[500];
    char *path = app_get_shared_resource_path();

    snprintf(filename, 500, "%s%s", path, "help.en");

    std::ifstream t(filename);
    std::stringstream buffer;
    buffer << t.rdbuf();
    if (buffer.str().length()>0)
    	helpText = buffer.str();
    else {
    	helpText = "Game rules<br>Oops, an error occurred.";
    }
}
void TBoardView::closePopupBox(){
	delete myPopupBox;
	myPopupBox = NULL;
}
void TBoardView::callbackMore(){
	//ShowPopup();
	if (myPopupBox!=NULL) closePopupBox();
	myPopupBox = new TMenuPopupBox(this);
	myPopupBox->result = [](TView* v, int r) {
										((TBoardView*)v)->closePopupBox();
										switch(r) {
											case 1: break;
											case 2: ((TBoardView*)v)->NewGame(); break;
											case 3: ((TBoardView*)v)->showHelp(); break;
											case 4: ui_app_exit(); break;
											}
										};//testResult;
	myPopupBox->show();
}

void testResult(int r) {
	if (r==1) ui_app_exit();
}

void TBoardView::callbackBack(){
//	ShowPopup();
	if (myPopupBox!=NULL) closePopupBox();
	myPopupBox = new TExitPopupBox(this);
	myPopupBox->result = [](TView* v, int r) { if (r==1) ui_app_exit(); };//testResult;
	myPopupBox->show();
}

void TBoardView::showHelp(){
	myPopupBox = new TInfoBox(this,helpText.c_str());
	myPopupBox->result = [](TView* v, int r) { ((TBoardView*)v)->closePopupBox(); };
	myPopupBox->show();
}


static void
popup_new_game_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(popup);
	popup = NULL;

	TBoardView *bv = (TBoardView*)data;
	bv->NewGame();
}

void popup_exit_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	//Evas_Object *popup = (Evas_Object*)data;
	evas_object_del(popup);
	popup = NULL;
	ui_app_exit();
}



void TBoardView::ShowPopup() {
	Evas_Object *btn;
    if (popup != NULL) {
    	evas_object_del(popup);
    	popup = NULL;
    	return;
    }
	/* popup */
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, 0.5);
	elm_object_text_set(popup, helpText.c_str());

	//evas_object_smart_callback_add(popup, "block,clicked", popup_block_clicked_cb, NULL);

	/* ok button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "New Game");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_smart_callback_add(btn, "clicked", popup_new_game_btn_clicked_cb, this);

	/* cancel button */
	btn = elm_button_add(popup);
	elm_object_style_set(btn, "popup");
	elm_object_text_set(btn, "Exit");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_smart_callback_add(btn, "clicked", popup_exit_btn_clicked_cb, popup);



	evas_object_show(popup);
}


Eina_Bool jumping_ball(void *data)
{
	TBoardView *bv = (TBoardView *) data;
    bv->JumpingBall();
    return EINA_TRUE;
}

void TBoardView::JumpingBall(){
 if (selBall.x !=0) {

	double x = (selBall.x-1)*squareSize  + left_margin;
	double y = (selBall.y-1)*squareSize  + top_margin;

	tick +=0.15;
	graphics.DrawSquare(x,y);
	x = x + squareSize / 2 ;
	y = y + squareSize / 2 + squareSize / 8*(1-std::abs(cos(tick))) - 1;
	// y = y + squareSize / 2 + 5*ecore_animator_pos_map((sin(tick)+1)/2,ECORE_POS_MAP_BOUNCE , 2,  4  );
	DrawBall(x,y,linesBoard->square[selBall.x][selBall.y]);


	graphics.Flush();

 }
}
void TBoardView::StartJumpingBallAnimator(){
  tick = 0;
  if (JumpingAnimator != NULL)
  	   ecore_animator_del(JumpingAnimator);
  JumpingAnimator = ecore_animator_add(jumping_ball, this);
}

void TBoardView::DeleteJumpingBallAnimator(){
	if (JumpingAnimator != NULL)
	   ecore_animator_del(JumpingAnimator);
}

void TBoardView::MoveBall(double pos) {
	DrawPath(pos);
	graphics.Flush();
	if (pos == 1.0) OnEndMoveBall();
}

Eina_Bool move_ball(void *data, double pos)
{
   TBoardView *bv = (TBoardView *) data;
   bv->MoveBall(pos);
   return EINA_TRUE;
}

void TBoardView::CreateMoveBallAnimator(){
	ecore_animator_timeline_add (1.0, move_ball, this);
}

void TBoardView::DeleteMoveBallAnimator(){

}

Eina_Bool appearance_new_ball(void *data, double pos)
{
   TBoardView *bv = (TBoardView *) data;
   bv->AppearanceNewBall(pos);
   return EINA_TRUE;
}

Eina_Bool disappearance_lines(void *data, double pos)
{
   TBoardView *bv = (TBoardView *) data;
   bv->DisappearanceLines(pos);
   return EINA_TRUE;
}

void TBoardView::OnEndMoveBall(){

	if (linesBoard->checkLines() == 0 )	{
		    NewBalls = linesBoard->addNewBalls();
			ecore_animator_timeline_add (1.0, appearance_new_ball, this);

	}
	else {
		DrawHeader();
		ecore_animator_timeline_add (1.0, disappearance_lines, this);
	}
}

void TBoardView::AppearanceNewBall(double pos) {

	for ( TPoint p : NewBalls )
		DrawBall(p,  pos);

	graphics.Flush();
}

void TBoardView::DisappearanceLines(double pos){

	for ( TPoint p : linesBoard->clearBalls ){
	    DrawSquare(p);
		DrawBall(p,  1-pos);
	}

	graphics.Flush();
}

void TBoardView::OnClick(int x, int y) {

	int xx =(x-left_margin) / squareSize + 1;
	int yy =(y-top_margin) / squareSize + 1;

	if (linesBoard->OutOfBoundary(xx, yy)) return;

    if (linesBoard->square[xx][yy] > 0) {
    	selBall.x = xx;
    	selBall.y = yy;

        StartJumpingBallAnimator();
    }
    else {
    	if (selBall.x > 0)  {

    		destSquare.x = xx;
    		destSquare.y = yy;

    		linesBoard->initSearch(selBall,destSquare);

            if (linesBoard->searchPath(selBall,destSquare) >0) {
            	linesBoard->square[destSquare.x][destSquare.y] = linesBoard->square[selBall.x][selBall.y];
            	linesBoard->square[selBall.x][selBall.y] = 0;
            	 selBall.x = 0;
            	 DeleteJumpingBallAnimator();
            	 CreateMoveBallAnimator();

            }

    	}

    }
};

void TBoardView::AddRandomBalls(){
    NewBalls = linesBoard->AddRandomBalls();
	ecore_animator_timeline_add (1.0, appearance_new_ball, this);
}

void TBoardView::CairoDrawing(){

	graphics.FillBackgroud();

	CalcViewMarkup();

	DrawHeader();

	DrawBoard();

	if (linesBoard->initBalls) DrawBalls();

	graphics.Flush();
}


void TBoardView::DrawBalls() {
	for(int i=1; i<= linesBoard->sizeX; i++)
	  for(int j=1; j<= linesBoard->sizeY; j++){
			double x = i*squareSize - squareSize / 2 + left_margin;
			double y = j*squareSize - squareSize / 2 + top_margin;
			DrawBall(x,y,linesBoard->square[i][j]);
	  }
}

void TBoardView::DrawSquare(TPoint p){
	double x = (p.x-1)*squareSize  + left_margin;
	double y = (p.y-1)*squareSize  + top_margin;
	graphics.DrawSquare(x, y);
}

void TBoardView::CalcViewMarkup(){

	double BoardWidth = myWidth - 20;

	left_margin = ( myWidth - BoardWidth)/2;

	squareSize = BoardWidth / linesBoard->sizeX;
	graphics.squareSize = squareSize;

	double BoardHeight = squareSize * linesBoard->sizeY;
	top_margin = ( myHeight - BoardHeight)/2;
}


void TBoardView::DrawBoard(){

	for (int x = 0; x< linesBoard->sizeX; x++)
		for (int y = 0; y< linesBoard->sizeY; y++) {
			double xx = x*squareSize  + left_margin;
			double yy = y*squareSize  + top_margin ;
			graphics.DrawSquare(xx, yy);
		}
}


void TBoardView::DrawBall(TPoint p, double r){
	double x = p.x*squareSize - squareSize / 2 + left_margin;
	double y = p.y*squareSize - squareSize / 2 + top_margin;
	graphics.DrawBall(x, y, r, p.color);
}

void TBoardView::DrawBall(TPoint p, double r, int color){
	double x = p.x*squareSize - squareSize / 2 + left_margin;
	double y = p.y*squareSize - squareSize / 2 + top_margin;
	graphics.DrawBall(x, y, r, color);
}

void TBoardView::DrawBall(double x, double y, int color){
	graphics.DrawBall(x,y,1,color);
}



void TBoardView::DrawPath(){
	if (linesBoard->path.size()>0) {
		TPoint p = linesBoard->path.front();
		int color =  linesBoard->square[p.x][p.y];
		for ( TPoint p : linesBoard->path ){
			double xx = p.x*squareSize - squareSize / 2 + left_margin;
			double yy = p.y*squareSize - squareSize / 2 + top_margin;
			graphics.DrawBall(xx, yy,  0.4, color);
		}

	}

}

void TBoardView::DrawPath(double pos){
	if (linesBoard->path.size() == 0) return;
	double dx = M_PI/linesBoard->path.size();
	for (int i = 0; i<linesBoard->path.size(); i++ ) {
		TPoint p  =  linesBoard->path[i];

		DrawSquare(p);

		double r = cos(dx*i - M_PI*(1-1.5*pos));
		if (r<0) r = 0.0; else r = 0.5*r;

		DrawBall(p, r, p.color);
	}
	if (pos>0.5) {
		TPoint p = linesBoard->path.front();
		DrawBall(p, 1, p.color);
	}

}

void TBoardView::DrawHeader() {

	graphics.DrawHeaderBG();

	//graphics.DrawScore(20,60,linesBoard->record);
	//graphics.DrawScore(myWidth - 60 ,60,linesBoard->score);

	graphics.DrawScore(left_margin, squareSize + 8,"Best", linesBoard->record, 0);
	graphics.DrawScore(myWidth - left_margin , squareSize + 8,"Score", linesBoard->score, 1);

	double dx = (myWidth - 1.1*squareSize *3)/2;
	for (int i = 0; i<3; i++) {
		double x = dx + 1.1*squareSize*i;
		graphics.DrawSquare(x, 10);
		graphics.DrawBall(x + squareSize/2, 10 + squareSize/2,  1, linesBoard->threeBalls[i]);
	}
}



