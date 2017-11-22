/*
 * Automat.cpp
 *
 */

#include "../includes/Automat.h"

/**
 * TODO: Randfälle abdecken, sehr lange Bezeichner und so scheiss
 */

/**
 * Constructor, creates an new automat
 * Initializes all States and sets up the state matrix
*/
Automat::Automat() {

	currentState = State::Start;
	column = 1;
	line = 1;
	tokenColumn = 1;
	tokenLine = 1;
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

/**
 * Destructor
 */
Automat::~Automat() {

}

/**
 * Runs through the matrix to see which state is the new one.
 * @return: returns whether the char leads to a final state or not
 */
bool Automat::checkChar(char c) {

	bool finalState = false;

	//Empty input or space
	if (c == ' ' || c == '\t') {
		column++;
		currentState = State::Start;
	//new Line
	} else if (c == '\n') {
		line ++;
		column = 1;
		currentState = State::Start;
	//to reset the automat after the Scanner found a Token
	//e.g. if there's no space between this and the
	//next token
	} else if (c == '\0'){

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

/*
 * Returns the saved line number for the Token
 */
int Automat::getTokenLine() {
	return tokenLine;
}

/*
 * Returns current Line for scanner
 */
int Automat::getLine() {
	return line;
}

/*
 * Returns the saved column number for the Token
 */
int Automat::getTokenColumn() {
	return tokenColumn;
}

/*
 * Returns current column for Scanner
 */
int Automat::getColumn() {
	return column;
}

/*
 * Returns the Final state that was reached last
 */
State::Type Automat::getLastFinalState(){
	return lastFinalState;
}
