/*
 * Parser.cpp
 *
 *  Created on: 15.04.2018
 *      Author: mella
 */


#include "../includes/Parser.h"

Parser::Parser(char* filename) {
	scanner = new Scanner(filename);
}

Parser::~Parser() {

}

bool parse () {

	return true;
}

void Parser::PROG() {
	DECLS();
	STATEMENTS();
}

void Parser::DECLS() {

	if (1 == 1) { //Token == int

		DECL();

		if (1) { //Token == ;

			DECLS();

		} else { //error

		}


	} else { //epsilon

	}
}

void Parser::DECL() {

	if (1) { //Token == int

		ARRAY();

		if (1) { //Token == identifier

		}
	} else { //error

	}
}

void Parser::ARRAY() {

	if (1) { //Token == [

		if (1) { // ==integer

			if (1) { // == ]

			} else { //error

			}

		} else { //error

		}

	} else { //epsilon

	}
}

void Parser::STATEMENTS() {

	if (1) { // ==identifier | == write | == read | == { | == if | == while

		STATEMENT();

		if(1) { // == ;

			STATEMENTS();

		} else { //error

		}

	} else { //epsilon

	}
}

void Parser::STATEMENT() {

	if (1) { //identifier


		INDEX();

		if (1) { // == :=


			EXP();

		} else { // error

		}

	} else if (1) { // write

		if (1) { // (

			EXP();

			if (1) { // )

			} else { //error

			}
		} else { //error

		}

	} else if (1) { //read

		if (1) { // (

			if (1) { // identifier

				INDEX();

				if (1) { // )

				} else { //error

				}
			} else { //error

			}
		} else { //error

		}

	} else if (1) { // {

		STATEMENTS();

		if (1) { // }

		} else { //error

		}

	} else if (1) { // if

		if (1) { // (

			EXP();

			if (1) { // )

				STATEMENT();

				if (1) { // else

					STATEMENT();

				} else { //error

				}

			} else { //error

			}

		} else { //error

		}

	} else if (1) { // while

		if (1) { // (

			EXP();

			if (1) { // )

				STATEMENT();

			} else { //error

			}

		} else { //error

		}

	} else { //error

	}
}

void Parser::EXP() {

	EXP2();

	OP_EXP();
}

void Parser::EXP2() {

	if (1) { // (

		EXP();

		if (1) { // )

		} else { //error

		}
	} else if (1) { //identifier

		INDEX();
	} else if (1) { //integer

	} else if (1) { //-

		EXP2();
	} else if (1) { //!

		EXP2();
	} else { //error

	}

}

void Parser::INDEX() {

	if (1) { // [

		EXP();

		if (1) { // ]

		} else { //error

		}

	} else { //epsilon

	}

}

void Parser::OP_EXP() {

	if (1) { // + | - | * | : | < | > | = | =:= | &&

		OP();

		EXP();

	} else { //epsilon

	}

}

void Parser::OP() {

	if (1) { // +

	} else if (1) { // -

	} else if (1) { // *

	} else if (1) { // :

	} else if (1) { // <

	} else if (1) { // >

	} else if (1) { // =

	} else if (1) { // =:=

	} else if (1) { // &&

	} else { //error

	}

}




