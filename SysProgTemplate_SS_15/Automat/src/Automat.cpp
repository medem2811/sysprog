/*
 * Automat.cpp
 *
 */

#include "../includes/Automat.h"


Automat::Automat() {

	currentState = State::Start;
	column = 1;
	line = 1;
	tokenColumn = 1;
	lastFinalState = State::Undefined;

	//fill matrix with undefined states
	for (int i = 0; i < (int) State::StateCount; i++)  {
		for (int j = 0; j < 128; j++) {
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

	bool finalState = false;

	//Empty input or space
	if (c == ' ' || c == '\t') {
		column++;
		currentState = State::Start;
	} else if (c == '\n') {
		line ++;
		column = 1;
		currentState = State::Start;
	//actual chars as input
	} else {
		//save the start column of token or error
		if(currentState == State::Start) {
			tokenColumn = column;
		}

		//move forward in automat
		currentState = stateMatrix[currentState][(int)c];
		column++;

		//check if state is a final state
		if (finalStates[(int)currentState]) {
			finalState = true;
			lastFinalState = currentState;
		}

		//Reset the Automat
		if(currentState == State::Undefined) {
					currentState = State::Start;
		}
	}


	return finalState;
}

int Automat::getLine() {
	return line;
}

int Automat::getColumn() {
	return tokenColumn;
}

State::Type Automat::getLastFinalState(){
	return lastFinalState;
}
