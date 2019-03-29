/*
 * TBezel.h
 *
 *  Created on: Dec 11, 2017
 *      Author: Alex
 */

#ifndef TBEZEL_H_
#define TBEZEL_H_

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>

#include <functional>

class TBezel {
public:
	TBezel();
	virtual ~TBezel();

	void Attach(Evas_Object *obj);

	bool isSupportBezel;

public:

	 std::function<void(double)> OnValueChenged = nullptr;
private:
	 bool CheckSupportBezel();
};

#endif /* TBEZEL_H_ */
