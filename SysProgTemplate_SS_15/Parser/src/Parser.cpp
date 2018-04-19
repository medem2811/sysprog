/*
 * Parser.cpp
 *
 *  Created on: 15.04.2018
 *      Author: mella
 */


#include "../includes/Parser.h"

Parser::Parser(char* filename) {
	scanner = new Scanner(filename);
	currentToken = scanner->nextToken();
	prevToken = NULL;
	error = false;
}

Parser::~Parser() {

}

bool Parser::parse () {

	PROG();
	return !error;
}

void Parser::PROG() {
	DECLS();
	STATEMENTS();
}

void Parser::DECLS() {

	if (!error && currentToken->getType() == State::intState) { //Token == int

		DECL();

		if (!error && currentToken->getType() == State::signSemiColon) { //Token == ;

			currentToken = scanner->nextToken();
			DECLS();

		} else if (!error) { //error

			errorMessage(currentToken->getType());
		}

	} else { //epsilon

	}
}

void Parser::DECL() {


	currentToken = scanner->nextToken();

	ARRAY();

	if (!error && currentToken->getType() == State::Identifier) { //Token == identifier

		currentToken = scanner->nextToken();
	} else if (!error) { //error
		errorMessage(currentToken->getType());
	}

}

void Parser::ARRAY() {

	if (currentToken->getType() == State::signBracketOpen) { //Token == [

		currentToken = scanner->nextToken();

		if (currentToken->getType() == State::Integer) { // ==integer

			currentToken = scanner->nextToken();

			if (currentToken->getType() == State::signBracketClose) { // == ]

				currentToken = scanner->nextToken();

			} else if (!error){ //error
				errorMessage(currentToken->getType());
			}

		} else if (!error){ //error
			errorMessage(currentToken->getType());
		}

	} else { //epsilon

	}
}

void Parser::STATEMENTS() {

	if (!error && (currentToken->getType() == State::Identifier ||
			currentToken->getType() == State::writeState ||
			currentToken->getType() == State::readState ||
			currentToken->getType() == State::signCurlyBracketOpen ||
			currentToken->getType() == State::ifState ||
			currentToken->getType() == State::whileState)) { // ==identifier | == write | == read | == { | == if | == while

		STATEMENT();

		if(!error && currentToken->getType() == State::signSemiColon) { // == ;

			currentToken = scanner->nextToken();
			STATEMENTS();

		} else if (!error){ //error

			errorMessage(currentToken->getType());
		}

	} else if (!error) { //epsilon

	}
}

void Parser::STATEMENT() {

	if (!error) {
	if (currentToken->getType() == State::Identifier) { //identifier

		currentToken = scanner->nextToken();
		INDEX();

		if (currentToken->getType() == State::signCEquals) { // == :=

			currentToken = scanner->nextToken();

			EXP();

		} else if (!error){ // error

			errorMessage(currentToken->getType());
		}

	} else if (currentToken->getType() == State::writeState) { // write

		currentToken = scanner->nextToken();
		if (currentToken->getType() == State::signRoundBracketOpen) { // (

			currentToken = scanner->nextToken();

			EXP();

			if (currentToken->getType() == State::signRoundBracketClose) { // )

				currentToken = scanner->nextToken();

			} else if (!error){ //error
				errorMessage(currentToken->getType());
			}
		} else if (!error){ //error
			errorMessage(currentToken->getType());
		}

	} else if (currentToken->getType() == State::readState) { //read

		currentToken = scanner->nextToken();

		if (currentToken->getType() == State::signRoundBracketOpen) { // (

			currentToken = scanner->nextToken();

			if (currentToken->getType() == State::Identifier) { // identifier

				currentToken = scanner->nextToken();

				INDEX();

				if (currentToken->getType() == State::signRoundBracketClose) { // )

					currentToken = scanner->nextToken();

				} else if (!error){ //error
					errorMessage(currentToken->getType());
				}
			} else if (!error) { //error
				errorMessage(currentToken->getType());
			}
		} else if (!error) { //error
			errorMessage(currentToken->getType());
		}

	} else if (currentToken->getType() == State::signCurlyBracketOpen) { // {

		currentToken = scanner->nextToken();
		STATEMENTS();

		if (currentToken->getType() == State::signCurlyBracketClose) { // }

			currentToken = scanner->nextToken();

		} else if (!error){ //error
			errorMessage(currentToken->getType());
		}

	} else if (currentToken->getType() == State::ifState) { // if

		currentToken = scanner->nextToken();

		if (currentToken->getType() == State::signRoundBracketOpen) { // (

			currentToken = scanner->nextToken();

			EXP();

			if (currentToken->getType() == State::signRoundBracketClose) { // )

				currentToken = scanner->nextToken();

				STATEMENT();

				if (currentToken->getType() == State::elseState) { // else

					currentToken = scanner->nextToken();

					STATEMENT();

				} else if (!error){ //error
					errorMessage(currentToken->getType());
				}

			} else if (!error){ //error
				errorMessage(currentToken->getType());
			}

		} else if (!error) { //error
			errorMessage(currentToken->getType());
		}

	} else if (currentToken->getType() == State::whileState) { // while

		currentToken = scanner->nextToken();

		if (currentToken->getType() == State::signRoundBracketOpen) { // (

			currentToken = scanner->nextToken();

			EXP();

			if (currentToken->getType() == State::signRoundBracketClose) { // )

				currentToken = scanner->nextToken();
				STATEMENT();

			} else if (!error) { //error
				errorMessage(currentToken->getType());
			}

		} else if (!error) { //error
			errorMessage(currentToken->getType());
		}

	} else if (!error) { //error
		errorMessage(currentToken->getType());
	}
	}
}

void Parser::EXP() {

	EXP2();

	OP_EXP();
}

void Parser::EXP2() {

	if (currentToken->getType() == State::signRoundBracketOpen) { // (

		currentToken = scanner->nextToken();
		EXP();

		if (currentToken->getType() == State::signRoundBracketClose) { // )

			currentToken = scanner->nextToken();

		} else if (!error) { //error
			errorMessage(currentToken->getType());
		}
	} else if (currentToken->getType() == State::Identifier) { //identifier

		currentToken = scanner->nextToken();
		INDEX();

	} else if (currentToken->getType() == State::Integer) { //integer

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signMinus) { //-

		currentToken = scanner->nextToken();
		EXP2();

	} else if (currentToken->getType() == State::signExclamation) { //!

		currentToken = scanner->nextToken();
		EXP2();
	} else if (!error) { //error
		errorMessage(currentToken->getType());
	}

}

void Parser::INDEX() {

	if (currentToken->getType() == State::signBracketOpen) { // [

		currentToken = scanner->nextToken();

		EXP();

		if (currentToken->getType() == State::signBracketClose) { // ]

			currentToken = scanner->nextToken();
		} else if (!error) { //error
			errorMessage(currentToken->getType());
		}

	} else { //epsilon

	}

}

void Parser::OP_EXP() {

	if (!error && (currentToken->getType() == State::signPlus ||
			currentToken->getType() == State::signMinus ||
			currentToken->getType() == State::signStar ||
			currentToken->getType() == State::signColon ||
			currentToken->getType() == State::signSmaller ||
			currentToken->getType() == State::signBigger ||
			currentToken->getType() == State::signEquals ||
			currentToken->getType() == State::signECEquals ||
			currentToken->getType() == State::signDoubleAnd)) { // + | - | * | : | < | > | = | =:= | &&

		OP();

		EXP();

	} else { //epsilon

	}

}

void Parser::OP() {

	if (currentToken->getType() == State::signPlus) { // +

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signMinus) { // -

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signStar) { // *

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signColon) { // :

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signSmaller) { // <

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signBigger) { // >

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signEquals) { // =

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signECEquals) { // =:=

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signDoubleAnd) { // &&

		currentToken = scanner->nextToken();

	} else if (!error) { //error

		errorMessage(currentToken->getType());
	}
}

void Parser::errorMessage(State::Type type) {

	char* StrType;

	switch ((int)type) {
	case (int)State::Integer: 		StrType = (char*)"Integer";
									break;
	case (int)State::Identifier: 	StrType = (char*)"Identifier";
									break;
	case (int)State::ifState: 		StrType = (char*)"if Statement";
									break;
	case (int)State::whileState:	StrType = (char*)"while Statement";
									break;
	case (int)State::elseState: 	StrType = (char*)"else Statement";
									break;
	case (int)State::intState: 		StrType = (char*)"int Declaration";
									break;
	case (int)State::writeState:	StrType = (char*)"write Statement";
									break;
	case (int)State::readState: 	StrType = (char*)"read Statement";
									break;
	case (int)State::signPlus: 		StrType = (char*)"+ Token";
									break;
	case (int)State::signMinus: 	StrType = (char*)"- Token";
									break;
	case (int)State::signColon: 	StrType = (char*)": Token";
									break;
	case (int)State::signStar: 		StrType = (char*)"* Token";
									break;
	case (int)State::signSmaller: 	StrType = (char*)"< Token";
									break;
	case (int)State::signBigger: 	StrType = (char*)"> Token";
									break;
	case (int)State::signEquals: 	StrType = (char*)"= Token";
									break;
	case (int)State::signCEquals: 	StrType = (char*)":= Token";
									break;
	case (int)State::signECEquals: 	StrType = (char*)"=:= Token";
									break;
	case (int)State::signExclamation: StrType = (char*)"! Token";
									break;
	case (int)State::signDoubleAnd:	StrType = (char*)"&& Token";
									break;
	case (int)State::signSemiColon:	StrType = (char*)"; Token";
									break;
	case (int)State::signRoundBracketOpen: StrType = (char*)"( Token";
									break;
	case (int)State::signRoundBracketClose: StrType = (char*)") Token";
									break;
	case (int)State::signCurlyBracketOpen: StrType = (char*)"{ Token";
									break;
	case (int)State::signCurlyBracketClose: StrType = (char*)"} Token";
									break;
	case (int)State::signBracketOpen: StrType = (char*)"[ Token";
									break;
	case (int)State::signBracketClose: StrType = (char*)"] Token";
									break;
	case (int)State::Error: 		StrType = (char*) "Error Token";
									break;
	}

	fprintf(stderr, "Error: unexpected Token in Line: %d \t Column: %d \t %s \n",
			currentToken->getLine(), currentToken->getColumn(), StrType);
	error = true;
}



