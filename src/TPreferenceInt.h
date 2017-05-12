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

	void update();

    friend TPreferenceInt& operator+=(TPreferenceInt& left, const int& right);

    operator int() const {
        return value;
    }


private:
  const char *myKey;
  int value;
};

#endif /* TPREFERENCEINT_H_ */
