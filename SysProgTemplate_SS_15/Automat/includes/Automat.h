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

	int getTokenLine();
	int getTokenColumn();
	int getLine();
	int getColumn();
	State::Type getLastFinalState();

private:
	State::Type stateMatrix[(State::StateCount)][128];
	bool finalStates [(State::StateCount)];

	State::Type currentState;
	State::Type lastFinalState;

	int column;
	int line;
	int tokenColumn;
	int tokenLine;
};

#endif /* Automat_H_ */
