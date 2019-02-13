/*
 * TAnimator.h
 *
 *  Created on: Feb 13, 2019
 *      Author: Alex
 */

#ifndef TANIMATOR_H_
#define TANIMATOR_H_
#include "TImage.h"

class TAnimator {
public:
	TAnimator();
	virtual ~TAnimator();

	Ecore_Animator *animator;

	TImage *image;

	void Initialize(TImage *img);
	void Freeze();
	void Thaw();

	void StartJumpingBall(int x, int y);
};

#endif /* TANIMATOR_H_ */
