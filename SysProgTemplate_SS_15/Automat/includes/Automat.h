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
	State::Type getLastFinalState();
	State::Type reset(int steps, int lines);
	bool isComment();
	bool isCompatible(State::Type type1, State::Type type2);

private:
	State::Type stateMatrix[(State::StateCount)][128];
	bool finalStates [(State::StateCount)];

	State::Type currentState;
	State::Type lastFinalState;
	State::Type lookBackState;

	int column;
	int prevColumn;
	int line;
	int tokenColumn;
	int tokenLine;
};

#endif /* Automat_H_ */
