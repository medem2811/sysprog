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
}

Parser::~Parser() {

}

bool Parser::parse () {

	PROG();
	return true;
}

void Parser::PROG() {
	DECLS();
	STATEMENTS();
}

void Parser::DECLS() {

	if (currentToken->getType() == State::intState) { //Token == int

		currentToken = scanner->nextToken();
		//DECL();

		if (currentToken->getType() == State::signSemiColon) { //Token == ;

			currentToken = scanner->nextToken();
			DECLS();

		} else { //error

			cerr << "Error: missing Token in line " << currentToken->getLine()
					<< ": ;" << endl;
		}


	} else { //epsilon

	}
}

void Parser::DECL() {

	if (currentToken->getType() == State::intState) { //Token == int

		currentToken = scanner->nextToken();

		ARRAY();

		if (currentToken->getType() == State::Identifier) { //Token == identifier

			currentToken = scanner->nextToken();
		}
	} else { //error
		cerr << "Error: Syntax Error in line " << currentToken->getLine()
							<< endl;
	}
}

void Parser::ARRAY() {

	if (currentToken->getType() == State::signBracketOpen) { //Token == [

		currentToken = scanner->nextToken();

		if (currentToken->getType() == State::Integer) { // ==integer

			currentToken = scanner->nextToken();

			if (currentToken->getType() == State::signBracketClose) { // == ]

				currentToken = scanner->nextToken();

			} else { //error
				cerr << "Error: Unexpected Token in line " << currentToken->getLine()
											<< endl;
			}

		} else { //error
			cerr << "Error: Unexpected Token in line " << currentToken->getLine()
														<< endl;
		}

	} else { //epsilon
		cerr << "Error: Unexpected Token in line " << currentToken->getLine()
													<< endl;
	}
}

void Parser::STATEMENTS() {

	if (currentToken->getType() == State::Identifier ||
			currentToken->getType() == State::writeState ||
			currentToken->getType() == State::readState ||
			currentToken->getType() == State::signCurlyBracketOpen ||
			currentToken->getType() == State::ifState ||
			currentToken->getType() == State::whileState) { // ==identifier | == write | == read | == { | == if | == while

		STATEMENT();

		if(currentToken->getType() == State::signSemiColon) { // == ;

			currentToken = scanner->nextToken();
			STATEMENTS();

		} else { //error

			cerr << "Error: missing Token in line " << currentToken->getLine()
					<< ": ;" << endl;
		}

	} else { //epsilon

	}
}

void Parser::STATEMENT() {

	if (currentToken->getType() == State::Identifier) { //identifier

		currentToken = scanner->nextToken();
		INDEX();

		if (currentToken->getType() == State::signCEquals) { // == :=

			currentToken = scanner->nextToken();

			EXP();

		} else { // error

			cerr << "Error: missing Token in line " << currentToken->getLine()
								<< ": :=" << endl;
		}

	} else if (currentToken->getType() == State::writeState) { // write

		currentToken = scanner->nextToken();
		if (currentToken->getType() == State::signRoundBracketOpen) { // (

			currentToken = scanner->nextToken();

			EXP();

			if (currentToken->getType() == State::signRoundBracketClose) { // )

				currentToken = scanner->nextToken();

			} else { //error
				cerr << "Error: missing Token in line " << currentToken->getLine()
									<< ": )" << endl;
			}
		} else { //error
			cerr << "Error: missing Token in line " << currentToken->getLine()
								<< ": (" << endl;
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

				} else { //error
					cerr << "Error: missing Token in line " << currentToken->getLine()
										<< ": )" << endl;
				}
			} else { //error
				cerr << "Error: wrong Token in line " << currentToken->getLine()
									<< endl;
			}
		} else { //error
			cerr << "Error: missing Token in line " << currentToken->getLine()
								<< ": (" << endl;
		}

	} else if (currentToken->getType() == State::signCurlyBracketOpen) { // {

		currentToken = scanner->nextToken();
		STATEMENTS();

		if (currentToken->getType() == State::signCurlyBracketClose) { // }

			currentToken = scanner->nextToken();

		} else { //error
			cerr << "Error: missing Token in line " << currentToken->getLine()
								<< ": }" << endl;
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

				} else { //error
					cerr << "Error: missing Else-Statement in line " << currentToken->getLine()
										<< endl;
				}

			} else { //error
				cerr << "Error: missing Token in line " << currentToken->getLine()
									<< ": )" << endl;
			}

		} else { //error
			cerr << "Error: missing Token in line " << currentToken->getLine()
								<< ": (" << endl;
		}

	} else if (currentToken->getType() == State::whileState) { // while

		currentToken = scanner->nextToken();

		if (currentToken->getType() == State::signRoundBracketOpen) { // (

			currentToken = scanner->nextToken();

			EXP();

			if (currentToken->getType() == State::signRoundBracketClose) { // )

				currentToken = scanner->nextToken();
				STATEMENT();

			} else { //error
				cerr << "Error: missing Token in line " << currentToken->getLine()
									<< ": )" << endl;
			}

		} else { //error
			cerr << "Error: missing Token in line " << currentToken->getLine()
								<< ": (" << endl;
		}

	} else { //error
		cerr << "Error: Syntax Error in line " << currentToken->getLine()
							<< endl;
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

		} else { //error
			cerr << "Error: missing Token in line " << currentToken->getLine()
								<< ": )" << endl;
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
	} else { //error
		cerr << "Error: unexpected Token in line " << currentToken->getLine()
						 << endl;
	}

}

void Parser::INDEX() {

	if (currentToken->getType() == State::signBracketOpen) { // [

		currentToken = scanner->nextToken();

		EXP();

		if (currentToken->getType() == State::signBracketClose) { // ]

			currentToken = scanner->nextToken();
		} else { //error
			cerr << "Error: missing Token in line " << currentToken->getLine()
								<< ": ]" << endl;
		}

	} else { //epsilon

	}

}

void Parser::OP_EXP() {

	if (currentToken->getType() == State::signPlus ||
			currentToken->getType() == State::signMinus ||
			currentToken->getType() == State::signStar ||
			currentToken->getType() == State::signColon ||
			currentToken->getType() == State::signSmaller ||
			currentToken->getType() == State::signBigger ||
			currentToken->getType() == State::signEquals ||
			currentToken->getType() == State::signECEquals ||
			currentToken->getType() == State::signDoubleAnd) { // + | - | * | : | < | > | = | =:= | &&

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

	} else { //error

		cerr << "Error: Unexpected Token in line " << currentToken->getLine()
				<<endl;
	}

}




