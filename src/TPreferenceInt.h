/*
 * TPreferenceInt.h
 *
 *  Created on: May 12, 2017
 *      Author: Alex
 */

#ifndef TPREFERENCEINT_H_
#define TPREFERENCEINT_H_

class TPreferenceInt {
public:
	TPreferenceInt(const char *key);
	virtual ~TPreferenceInt();
    int Value();
    void Add(int a);
private:
  char *myKey;
  int value;
};

#endif /* TPREFERENCEINT_H_ */
