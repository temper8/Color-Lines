/*
 * TGesture.h
 *
 *  Created on: Dec 6, 2017
 *      Author: Alex
 */

#ifndef TGESTURE_H_
#define TGESTURE_H_

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>

#include <functional>

class TGesture {
public:
	TGesture(Evas_Object *obj);
	virtual ~TGesture();

	void Create(Evas_Object *obj);
	void Attach(Evas_Object *obj);

private:
	 Evas_Object *gesture_layer;

public:
	 std::function<void(int,int)> FingerTapEvent = nullptr;

	 std::function<void(int,int)> MomentumStartEventHolder = nullptr;
	 std::function<void(int,int)> MomentumMoveEventHolder = nullptr;
	 std::function<void(int,int)> MomentumEndEventHolder = nullptr;

	 std::function<void(int,int)> LineStartEventHolder = nullptr;
	 std::function<void(int,int,int,int)> LineMoveEventHolder = nullptr;//(int x1, int y1, int x2, int y2)
	 std::function<void(int,int)> LineEndEventHolder = nullptr;
	 std::function<void(int,int)> LineAbortEventHolder = nullptr;

	 std::function<void()> ZoomStartEventHolder = nullptr;
	 std::function<void(double)> ZoomMoveEventHolder  = nullptr;
	 std::function<void()> ZoomEndEventHolder  = nullptr;
	 std::function<void()> ZoomAbortEventHolder  = nullptr;
};

#endif /* TGESTURE_H_ */
