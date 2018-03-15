/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */
#include "State.h"

#ifndef Automat_H_
#define Automat_H_

class Automat {
public:
	Automat();
	virtual ~Automat();

	/*
	 * Changes the state
	 * @Param c: new char
	 * @Return: Whether c leads to a final state or not
	 */
	bool checkChar(char c);

	/*
	 * Returns the Line the Token is on
	 */
	int getTokenLine();
	/*
	 * Returns the Column the Token starts on
	 */
	int getTokenColumn();
	/*
	 * Returns the final state that was reached last
	 */
	State::Type getLastFinalState();
	/*
	 * Sets the Automat back to the start State
	 * @Param steps: how many chars it should trace back
	 * @Param lines: how many lines it should get back
	 * @Return: State before the reset
	 */
	State::Type reset(int steps, int lines);
	/*
	 * Checks whether or not a comment was started
	 */
	bool isComment();
	/*
	 * Checks whether or not two final states could lead
	 * to one another (like = leading to =:=)
	 */
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
