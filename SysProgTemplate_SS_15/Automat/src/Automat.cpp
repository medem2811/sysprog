/*
 * Automat.cpp
 *
 */

#include "../includes/Automat.h"


Automat::Automat() {

	currentState = State::Start;
	column = 1;
	line = 1;

	//fill matrix with undefined states
	for (int i = 0; i < (int) State::StateCount; i++)  {
		for (int j = 0; j < 256; j++) {
			stateMatrix[i][j] = State::Undefined;
		}
	}

	//fill in States for numbers
	for (int i = '0'; i <= '9'; i++) {
		stateMatrix[(int)State::Start][i] = State::Number;
		stateMatrix[(int)State::Number][i] = State::Number;
	}

	//set all final states
	finalStates[(int)State::Start] = false;
	finalStates[(int)State::Undefined] = true;
	finalStates[(int)State::Number] = true;

}

Automat::~Automat() {

}

bool Automat::checkChar(char c) {

	//Case StartState:
	if (currentState == State::Start) {
		stateMatrix[1][2] = State::Undefined;

	}
	return false;
}
