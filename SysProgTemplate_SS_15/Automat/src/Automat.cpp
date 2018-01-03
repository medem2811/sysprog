/*
 * Automat.cpp
 *
 */

#include "../includes/Automat.h"

/**
 * Constructor, creates an new automat
 * Initializes all States and sets up the state matrix
*/
Automat::Automat() {

	currentState = State::Start;
	column = 1;
	prevColumn = column;
	line = 1;
	tokenColumn = 1;
	tokenLine = 1;
	lastFinalState = State::Undefined;
	lookBackState = State::Undefined;

	//fill matrix with undefined states
	for (int i = 0; i < (int) State::StateCount; i++)  {
		for (int j = 0; j < 128; j++) {
			stateMatrix[i][j] = State::Undefined;
		}
	}

	//to ignore all comments
	for (int j = 0; j < 128; j++) {
		stateMatrix[(int) State::stateCommentStart][j] = State::stateCommentStart;
		stateMatrix[(int)State::stateCommentStar][j] = State::stateCommentStart;
	}

	//fill in States for numbers
	for (int i = 48; i <= 57; i++) {
		stateMatrix[(int)State::Start][i] = State::Integer;
		stateMatrix[(int)State::Integer][i] = State::Integer;
		stateMatrix[(int)State::Identifier][i] = State::Identifier;
		stateMatrix[(int) State::stateCommentStart][i] = State::stateCommentStart;

		stateMatrix[(int)State::statei][i] = State::Identifier;
		stateMatrix[(int)State::stateI][i] = State::Identifier;
		stateMatrix[(int)State::statew][i] = State::Identifier;
		stateMatrix[(int)State::stateW][i] = State::Identifier;
		stateMatrix[(int)State::statewh][i] = State::Identifier;
		stateMatrix[(int)State::stateWH][i] = State::Identifier;
		stateMatrix[(int)State::statewhi][i] = State::Identifier;
		stateMatrix[(int)State::stateWHI][i] = State::Identifier;
		stateMatrix[(int)State::statewhil][i] = State::Identifier;
		stateMatrix[(int)State::stateWHIL][i] = State::Identifier;
	}

	//state for identifier a-z
	for (int i = 97; i <= 122; i++) {
		stateMatrix[(int)State::Start][i] = State::Identifier;
		stateMatrix[(int)State::Identifier][i] = State::Identifier;

		stateMatrix[(int)State::statei][i] = State::Identifier;
		stateMatrix[(int)State::stateI][i] = State::Identifier;
		stateMatrix[(int)State::statew][i] = State::Identifier;
		stateMatrix[(int)State::stateW][i] = State::Identifier;
		stateMatrix[(int)State::statewh][i] = State::Identifier;
		stateMatrix[(int)State::stateWH][i] = State::Identifier;
		stateMatrix[(int)State::statewhi][i] = State::Identifier;
		stateMatrix[(int)State::stateWHI][i] = State::Identifier;
		stateMatrix[(int)State::statewhil][i] = State::Identifier;
		stateMatrix[(int)State::stateWHIL][i] = State::Identifier;
	}

	//state for identifier A-Z
	for (int i = 65; i <= 90; i++) {
		stateMatrix[(int)State::Start][i] = State::Identifier;
		stateMatrix[(int)State::Identifier][i] = State::Identifier;

		stateMatrix[(int)State::statei][i] = State::Identifier;
		stateMatrix[(int)State::stateI][i] = State::Identifier;
		stateMatrix[(int)State::statew][i] = State::Identifier;
		stateMatrix[(int)State::stateW][i] = State::Identifier;
		stateMatrix[(int)State::statewh][i] = State::Identifier;
		stateMatrix[(int)State::stateWH][i] = State::Identifier;
		stateMatrix[(int)State::statewhi][i] = State::Identifier;
		stateMatrix[(int)State::stateWHI][i] = State::Identifier;
		stateMatrix[(int)State::statewhil][i] = State::Identifier;
		stateMatrix[(int)State::stateWHIL][i] = State::Identifier;
	}

	//signStates:
	//plus - 43
	stateMatrix[(int)State::Start][43] = State::signPlus;
	//minus - 45
	stateMatrix[(int)State::Start][45] = State::signMinus;
	//colon - 58
	stateMatrix[(int)State::Start][58] = State::signColon;
	stateMatrix[(int)State::signEquals][58] = State::stateEColon;
	stateMatrix[(int)State::stateCommentStar][58] = State::stateComment;
	//star - 42
	stateMatrix[(int)State::Start][42] = State::signStar;
	stateMatrix[(int)State::signColon][42] = State::stateCommentStart;
	stateMatrix[(int)State::stateCommentStart][42] = State::stateCommentStar;
	//smaller - 60
	stateMatrix[(int)State::Start][60] = State::signSmaller;
	//bigger - 62
	stateMatrix[(int)State::Start][62] = State::signBigger;
	//equals - 61
	stateMatrix[(int)State::Start][61] = State::signEquals;
	stateMatrix[(int)State::stateEColon][61] = State::signECEquals;
	stateMatrix[(int)State::signColon][61] = State::signCEquals;
	//Exclamation - 33
	stateMatrix[(int)State::Start][33] = State::signExclamation;
	//ampersand - 38
	stateMatrix[(int)State::Start][38] = State::stateSingleAnd;
	stateMatrix[(int)State::stateSingleAnd][38] = State::signDoubleAnd;
	//Semicolon - 59
	stateMatrix[(int)State::Start][59] = State::signSemiColon;
	//roundBracketOpen - 40
	stateMatrix[(int)State::Start][40] = State::signRoundBracketOpen;
	//roundBracketClose - 41
	stateMatrix[(int)State::Start][41] = State::signRoundBracketClose;
	//curlyBracketOpen - 123
	stateMatrix[(int)State::Start][123] = State::signCurlyBracketOpen;
	//curlyBracketClose - 125
	stateMatrix[(int)State::Start][125] = State::signCurlyBracketClose;
	//bracketOpen - 91
	stateMatrix[(int)State::Start][91] = State::signBracketOpen;
	//bracketClose - 93
	stateMatrix[(int)State::Start][93] = State::signBracketClose;

	//ifStates 105-102; 73-70
	stateMatrix[(int)State::Start][105] = State::statei;
	stateMatrix[(int)State::statei][102] = State::ifState;

	stateMatrix[(int)State::Start][73] = State::stateI;
	stateMatrix[(int)State::stateI][70] = State::ifState;

	//WhileStates 119-104-105-108-101; 87-72-73-76-69
	stateMatrix[(int)State::Start][119] = State::statew;
	stateMatrix[(int)State::statew][104] = State::statewh;
	stateMatrix[(int)State::statewh][105] = State::statewhi;
	stateMatrix[(int)State::statewhi][108] = State::statewhil;
	stateMatrix[(int)State::statewhil][101] = State::whileState;

	stateMatrix[(int)State::Start][87] = State::stateW;
	stateMatrix[(int)State::stateW][72] = State::stateWH;
	stateMatrix[(int)State::stateWH][73] = State::stateWHI;
	stateMatrix[(int)State::stateWHI][76] = State::stateWHIL;
	stateMatrix[(int)State::stateWHIL][69] = State::whileState;

	//set all final states
	finalStates[(int)State::Start] = false;
	for (int i = (int) State::Undefined; i <= State::signBracketClose; i++) {
		finalStates[i] = true;
	}
	for (int i = (int) State::statew; i < State::StateCount; i++) {
		finalStates[i] = false;
	}

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
		if (!isComment()) {
			currentState = State::Start;
		}
	//new Line
	} else if (c == '\n') {
		line ++;
		prevColumn = column;
		column = 1;
		if (!isComment()) {
			currentState = State::Start;
		}
	//actual chars as input
	} else {
		//save the start column of token or error
		if(currentState == State::Start) {
			tokenLine = line;
			tokenColumn = column;
		}

		//move forward in automat
		currentState = stateMatrix[currentState][(int)c];
		column++;

		if (currentState != State::Undefined) {
			lookBackState = currentState;
		}

		//check if state is a final state
		if (finalStates[(int)currentState]) {
			finalState = true;
			lastFinalState = currentState;
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
 * Returns the saved column number for the Token
 */
int Automat::getTokenColumn() {
	return tokenColumn;
}

/*
 * Returns the Final state that was reached last
 */
State::Type Automat::getLastFinalState(){

	return lastFinalState;
}

/*
 * sets currentStat back to start and
 * reduces column by 1 to not mess with counting
 *
 * @return: recovers the state before it hit the currentState
 */
State::Type Automat::reset(int steps, int lines) {

	currentState = State::Start;
	if (lines > 0) {
		line -= lines;
		column = prevColumn;
	}
	column -= steps;

	return lookBackState;

}

/*
 * Checks if the scanner reads a comment
 */
bool Automat::isComment() {

	return (currentState == State::stateCommentStart || currentState == State::stateCommentStar);
}

/*
 * checks if 2 States belong to one Token or have to be separated
 */
bool Automat::isCompatible(State::Type type1, State::Type type2) {

	if (type1 == State::signEquals && type2 == State::signECEquals) {
		return true;
	} else if (type1 == State::signColon && type2 == State::signCEquals) {
		return true;
	} else if (type1 == type2) {
		return true;
	}

	return false;
}
