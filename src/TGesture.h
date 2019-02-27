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

class TGesture {
public:
	TGesture();
	virtual ~TGesture();

	void Create(Evas_Object *obj);
	void Attach(Evas_Object *obj);

private:
	 Evas_Object *gesture_layer;

public:
		virtual void OnFingerTap(int x, int y) {};

		virtual void OnMomentumStart(int x, int y) {};
		virtual void OnMomentumMove(int x1, int y1) {};
		virtual void OnMomentumEnd(int x, int y) {};

		virtual void OnLineStart(int x, int y) {};
		virtual void OnLineMove(int x1, int y1, int x2, int y2) {};
		virtual void OnLineEnd(int x, int y) {};
		virtual void OnLineAbort(int x, int y) {};

		virtual void OnZoomStart() = 0;
		virtual void OnZoomMove(double z) = 0;
		virtual void OnZoomEnd() = 0;
		virtual void OnZoomAbort() = 0;
};

#endif /* TGESTURE_H_ */
