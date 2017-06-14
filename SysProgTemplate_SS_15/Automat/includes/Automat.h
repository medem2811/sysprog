/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */
#include "State.h"
using namespace std;

#ifndef Automat_H_
#define Automat_H_

class Automat {
public:
	Automat();
	virtual ~Automat();
	bool checkChar(char c);

	int column;
	int line;

private:
	State::Type stateMatrix[(State::StateCount)][256];
	bool finalStates [(State::StateCount)];
	State::Type currentState;
};

#endif /* Automat_H_ */
