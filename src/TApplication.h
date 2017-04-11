/*
 * TApplication.h
 *
 *  Created on: Apr 11, 2017
 *      Author: Alex
 */

#ifndef TAPPLICATION_H_
#define TAPPLICATION_H_

class TApplication {
public:
	TApplication();
	virtual ~TApplication();

public:
	static TApplication *Instance;
	void Initialize();

};

#endif /* TAPPLICATION_H_ */
