/*
 * TBoardView.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Alex
 */

#include "TBoardView.h"

#include <cmath>



static Eina_Bool
add_random_balls(void *data)
{
	TBoardView *bv = (TBoardView *) data;
	bv->AddRandomBalls();

   return EINA_FALSE;
}

TBoardView::TBoardView() {
	// TODO Auto-generated constructor stub
	mx = 250;
	my = 250;
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

static void
popup_new_game_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(popup);
	popup = NULL;

	TBoardView *bv = (TBoardView*)data;
	bv->NewGame();
}

static void
popup_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	//Evas_Object *popup = (Evas_Object*)data;
	evas_object_del(popup);
	popup = NULL;
}

void TBoardView::ShowPopup() {
	Evas_Object *btn;
    if (popup != NULL) return;
	/* popup */
	popup = elm_popup_add(win);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_text_set(popup,"Game rules<br>The player can move one ball per turn, and the player may only move a ball to a particular place if there is a path (linked set of vertical and horizontal empty cells) between the current position of the ball and the desired destination. The goal is to remove balls by forming lines (horizontal, vertical or diagonal) of at least five balls of the same colour. If the player does form such lines of at least five balls of the same colour, the balls in those lines disappear, and he gains one turn, i.e. he can move another ball. If not, three new balls are added, and the game continues until the board is full.");

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
	evas_object_smart_callback_add(btn, "clicked", popup_btn_clicked_cb, popup);

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
	y = y + squareSize / 2 + 9*(1-std::abs(sin(tick)));
	// y = y + squareSize / 2 + 5*ecore_animator_pos_map((sin(tick)+1)/2,ECORE_POS_MAP_BOUNCE , 2,  4  );
	DrawBall(x,y,linesBoard->square[selBall.x][selBall.y]);


	graphics.Flush();

 }
}
void TBoardView::StartJumpingBallAnimator(){
  tick = 0;
  if (animator != NULL)
  	   ecore_animator_del(animator);
  animator = ecore_animator_add(jumping_ball, this);
}

void TBoardView::DeleteAnimator(){
	if (animator != NULL)
	   ecore_animator_del(animator);
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
	if (animator != NULL)
	  	   ecore_animator_del(animator);
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
	//CairoDrawing();

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
	mx=x;
	my=y;

	int xx =(x-left_margin) / squareSize + 1;
	int yy =(y-top_margin) / squareSize + 1;

    if (linesBoard->square[xx][yy] > 0) {
    	selBall.x = xx;
    	selBall.y = yy;

    	mx=(xx-1)*squareSize + left_margin + squareSize / 2;
        my=(yy-1)*squareSize + top_margin + squareSize / 2;

        StartJumpingBallAnimator();
    	  //DrawSquare(xx,yy, true);
    }
    else {
    	if (selBall.x == 0) {
        	mx=100;
        	my=100;
        	DeleteAnimator();
    	}
    	else {

    		mx=(xx-1)*squareSize + left_margin + squareSize / 2;
    		my=(yy-1)*squareSize + top_margin + squareSize / 2;

    		destSquare.x = xx;
    		destSquare.y = yy;

    		linesBoard->initSearch(selBall,destSquare);

            if (linesBoard->searchPath(selBall,destSquare) >0) {
            	linesBoard->square[destSquare.x][destSquare.y] = linesBoard->square[selBall.x][selBall.y];
            	linesBoard->square[selBall.x][selBall.y] = 0;
            	 selBall.x = 0;
            	CreateMoveBallAnimator();

            }

    	}

    }
	//linesBoard->initRandom();
	CairoDrawing();
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

	int BoardWidth = myWidth - 20;

	left_margin = ( myWidth - BoardWidth)/2;

	squareSize = BoardWidth / linesBoard->sizeX;
	graphics.squareSize = squareSize;

	int BoardHeight = squareSize * linesBoard->sizeY;
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

	graphics.DrawScore(10,65,linesBoard->record);
	graphics.DrawScore(650,65,linesBoard->score);
	double dx = (myWidth - 1.1*squareSize *3)/2;
	for (int i = 0; i<3; i++) {
		double x = dx + 1.1*squareSize*i;
		graphics.DrawSquare(x, 10);
		graphics.DrawBall(x + squareSize/2, 10 + squareSize/2,  1, linesBoard->threeBalls[i]);
	}
}



