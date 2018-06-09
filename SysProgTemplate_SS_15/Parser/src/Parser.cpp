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
	root = NULL;
}

Parser::~Parser() {

}

bool Parser::parse () {

	fprintf (stdout, "parsing...\n");
	PROG();
	return !error;
}

void Parser::PROG() {

	root = new TreeNode(NULL, Rules::ProgNode);
	DECLS(root);
	STATEMENTS(root);
}

void Parser::DECLS(TreeNode* parent) {

	if (!error && currentToken->getType() == State::intState) { //Token == int

		TreeNode* decls = new TreeNode(parent, Rules::DeclsNode);
		error = !parent->setChild(decls);
		DECL(decls);

		if (!error && currentToken->getType() == State::signSemiColon) { //Token == ;

			TreeNode* semicolon = new TreeNode(decls, currentToken);
			error = !decls->setChild(semicolon);
			currentToken = scanner->nextToken();
			DECLS(decls);

		} else if (!error) { //error

			errorMessage(currentToken->getType());
		}

	} else { //epsilon

		TreeNode* epsilon = new TreeNode(parent, Rules::Epsilon);
		error = !parent->setChild(epsilon);
	}
}

void Parser::DECL(TreeNode* parent) {


	TreeNode* decl = new TreeNode(parent, Rules::DeclNode);
	error = !parent->setChild(decl);

	TreeNode* intNode = new TreeNode(decl, currentToken);
	error = !decl->setChild(intNode);
	currentToken = scanner->nextToken();

	ARRAY(decl);

	if (!error && currentToken->getType() == State::Identifier) { //Token == identifier

		TreeNode* identifier = new TreeNode(decl, currentToken);
		error = !decl->setChild(identifier);
		currentToken = scanner->nextToken();

	} else if (!error) { //error
		errorMessage(currentToken->getType());
	}

}

void Parser::ARRAY(TreeNode* parent) {


	if (currentToken->getType() == State::signBracketOpen) { //Token == [

		TreeNode* array = new TreeNode(parent, Rules::ArrayNode);
		error = !parent->setChild(array);

		TreeNode* bracketOpen = new TreeNode(array, currentToken);
		error = !array->setChild(bracketOpen);
		currentToken = scanner->nextToken();

		if (currentToken->getType() == State::Integer) { // ==integer

			TreeNode* integer = new TreeNode(array, currentToken);
			error = !array->setChild(integer);
			currentToken = scanner->nextToken();

			if (currentToken->getType() == State::signBracketClose) { // == ]

				TreeNode* bracketClose = new TreeNode(array, currentToken);
				error = !array->setChild(bracketClose);
				currentToken = scanner->nextToken();

			} else if (!error){ //error
				errorMessage(currentToken->getType());
			}

		} else if (!error){ //error
			errorMessage(currentToken->getType());
		}

	} else { //epsilon

		TreeNode* epsilon = new TreeNode(parent, Rules::Epsilon);
		error = !parent->setChild(epsilon);
	}
}

void Parser::STATEMENTS(TreeNode* parent) {


	if (!error && (currentToken->getType() == State::Identifier ||
			currentToken->getType() == State::writeState ||
			currentToken->getType() == State::readState ||
			currentToken->getType() == State::signCurlyBracketOpen ||
			currentToken->getType() == State::ifState ||
			currentToken->getType() == State::whileState)) { // ==identifier | == write | == read | == { | == if | == while

		TreeNode* stats = new TreeNode (parent, Rules::StatsNode);
		error = !parent->setChild(stats);
		STATEMENT(stats);

		if(!error && currentToken->getType() == State::signSemiColon) { // == ;

			TreeNode* semicolon = new TreeNode(stats, currentToken);
			error = !stats->setChild(semicolon);
			currentToken = scanner->nextToken();
			STATEMENTS(stats);

		} else if (!error){ //error

			errorMessage(currentToken->getType());
		}

	} else if (!error) { //epsilon

		TreeNode* epsilon = new TreeNode(parent, Rules::Epsilon);
		error = !parent->setChild(epsilon);
	}
}

void Parser::STATEMENT(TreeNode* parent) {

	if (!error) {
	if (currentToken->getType() == State::Identifier) { //identifier

		TreeNode* stat = new TreeNode(parent, Rules::StatAssignment);
		error = !parent->setChild(stat);

		TreeNode* identifier = new TreeNode(stat, currentToken);
		error = !stat->setChild(identifier);
		currentToken = scanner->nextToken();
		INDEX(stat);

		if (currentToken->getType() == State::signCEquals) { // == :=

			TreeNode* cEquals = new TreeNode(stat, currentToken);
			error = !stat->setChild(cEquals);
			currentToken = scanner->nextToken();

			EXP(stat);

		} else if (!error){ // error

			errorMessage(currentToken->getType());
		}

	} else if (currentToken->getType() == State::writeState) { // write

		TreeNode* stat = new TreeNode(parent, Rules::StatWrite);
		error = !parent->setChild(stat);

		TreeNode* write = new TreeNode(stat, currentToken);
		error = !stat->setChild(write);
		currentToken = scanner->nextToken();

		if (currentToken->getType() == State::signRoundBracketOpen) { // (

			TreeNode* bracketOpen = new TreeNode(stat, currentToken);
			error = !stat->setChild(bracketOpen);
			currentToken = scanner->nextToken();

			EXP(stat);

			if (currentToken->getType() == State::signRoundBracketClose) { // )

				TreeNode* bracketClose = new TreeNode(stat, currentToken);
				error = !stat->setChild(bracketClose);
				currentToken = scanner->nextToken();

			} else if (!error){ //error
				errorMessage(currentToken->getType());
			}
		} else if (!error){ //error
			errorMessage(currentToken->getType());
		}

	} else if (currentToken->getType() == State::readState) { //read

		TreeNode* stat = new TreeNode(parent, Rules::StatRead);
		error = !parent->setChild(stat);

		TreeNode* read = new TreeNode(stat, currentToken);
		error = !stat->setChild(read);
		currentToken = scanner->nextToken();

		if (currentToken->getType() == State::signRoundBracketOpen) { // (

			TreeNode* bracketOpen = new TreeNode(stat, currentToken);
			error = !stat->setChild(bracketOpen);
			currentToken = scanner->nextToken();

			if (currentToken->getType() == State::Identifier) { // identifier

				TreeNode* identifier = new TreeNode(stat, currentToken);
				error = !stat->setChild(identifier);
				currentToken = scanner->nextToken();

				INDEX(stat);

				if (currentToken->getType() == State::signRoundBracketClose) { // )

					TreeNode* bracketClose = new TreeNode(stat, currentToken);
					error = !stat->setChild(bracketClose);
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

		TreeNode* stat = new TreeNode(parent, Rules::StatStatements);
		error = !parent->setChild(stat);

		TreeNode* bracketOpen = new TreeNode(stat, currentToken);
		error = !stat->setChild(bracketOpen);
		currentToken = scanner->nextToken();
		STATEMENTS(stat);

		if (currentToken->getType() == State::signCurlyBracketClose) { // }

			TreeNode* bracketClose = new TreeNode(stat, currentToken);
			error = !stat->setChild(bracketClose);
			currentToken = scanner->nextToken();

		} else if (!error){ //error
			errorMessage(currentToken->getType());
		}

	} else if (currentToken->getType() == State::ifState) { // if

		TreeNode* stat = new TreeNode(parent, Rules::StatIfElse);
		error = !parent->setChild(stat);

		TreeNode* ifNode = new TreeNode(stat, currentToken);
		error = !stat->setChild(ifNode);
		currentToken = scanner->nextToken();

		if (currentToken->getType() == State::signRoundBracketOpen) { // (

			TreeNode* bracketOpen = new TreeNode(stat, currentToken);
			error = !stat->setChild(bracketOpen);
			currentToken = scanner->nextToken();

			EXP(stat);

			if (currentToken->getType() == State::signRoundBracketClose) { // )

				TreeNode* bracketClose= new TreeNode(stat, currentToken);
				error = !stat->setChild(bracketClose);
				currentToken = scanner->nextToken();

				STATEMENT(stat);

				if (currentToken->getType() == State::elseState) { // else

					TreeNode* elseNode = new TreeNode(stat, currentToken);
					error = !stat->setChild(elseNode);
					currentToken = scanner->nextToken();

					STATEMENT(stat);

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

		TreeNode* stat = new TreeNode(parent, Rules::StatWhile);
		error = !parent->setChild(stat);

		TreeNode* whileNode = new TreeNode(stat, currentToken);
		error = !stat->setChild(whileNode);
		currentToken = scanner->nextToken();

		if (currentToken->getType() == State::signRoundBracketOpen) { // (
			TreeNode* bracketOpen = new TreeNode(stat, currentToken);
			error = !stat->setChild(bracketOpen);
			currentToken = scanner->nextToken();

			EXP(stat);

			if (currentToken->getType() == State::signRoundBracketClose) { // )

				TreeNode* bracketClose = new TreeNode(stat, currentToken);
				error = !stat->setChild(bracketClose);
				currentToken = scanner->nextToken();
				STATEMENT(stat);

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

void Parser::EXP(TreeNode* parent) {

	TreeNode* exp = new TreeNode(parent, Rules::ExpNode);
	error = !parent->setChild(exp);
	EXP2(exp);

	OP_EXP(exp);
}

void Parser::EXP2(TreeNode* parent) {

	if (currentToken->getType() == State::signRoundBracketOpen) { // (

		TreeNode* exp2 = new TreeNode(parent, Rules::Exp2Brackets);
		error = !parent->setChild(exp2);

		TreeNode* bracketOpen = new TreeNode(exp2, currentToken);
		error = !exp2->setChild(bracketOpen);

		currentToken = scanner->nextToken();
		EXP(exp2);

		if (currentToken->getType() == State::signRoundBracketClose) { // )

			TreeNode* bracketClose = new TreeNode(exp2, currentToken);
			error = !exp2->setChild(bracketClose);

			currentToken = scanner->nextToken();

		} else if (!error) { //error
			errorMessage(currentToken->getType());
		}
	} else if (currentToken->getType() == State::Identifier) { //identifier

		TreeNode* exp2 = new TreeNode(parent, Rules::Exp2Identifier);
		error = !parent->setChild(exp2);

		TreeNode* leaf = new TreeNode(exp2, currentToken);
		error = !exp2->setChild(leaf);

		currentToken = scanner->nextToken();
		INDEX(exp2);

	} else if (currentToken->getType() == State::Integer) { //integer

		TreeNode* exp2 = new TreeNode(parent, Rules::Exp2Integer);
		error = !parent->setChild(exp2);

		TreeNode* leaf = new TreeNode(exp2, currentToken);
		error = !exp2->setChild(leaf);

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signMinus) { //-

		TreeNode* exp2 = new TreeNode(parent, Rules::Exp2Minus);
		error = !parent->setChild(exp2);

		TreeNode* leaf = new TreeNode(exp2, currentToken);
		error = !exp2->setChild(leaf);

		currentToken = scanner->nextToken();
		EXP2(exp2);

	} else if (currentToken->getType() == State::signExclamation) { //!

		TreeNode* exp2 = new TreeNode(parent, Rules::Exp2Exclamation);
		error = !parent->setChild(exp2);

		TreeNode* leaf = new TreeNode(exp2, currentToken);
		error = !exp2->setChild(leaf);

		currentToken = scanner->nextToken();
		EXP2(exp2);
	} else if (!error) { //error
		errorMessage(currentToken->getType());
	}

}

void Parser::INDEX(TreeNode* parent) {

	if (currentToken->getType() == State::signBracketOpen) { // [

		TreeNode* index = new TreeNode(parent, Rules::IndexNode);
		error = !parent->setChild(index);

		TreeNode* bracketOpen = new TreeNode(index, currentToken);
		error = !index->setChild(bracketOpen);

		currentToken = scanner->nextToken();

		EXP(index);

		if (currentToken->getType() == State::signBracketClose) { // ]

			TreeNode* bracketClose = new TreeNode(index, currentToken);
			error = !index->setChild(bracketClose);

			currentToken = scanner->nextToken();
		} else if (!error) { //error
			errorMessage(currentToken->getType());
		}

	} else { //epsilon
		TreeNode* epsilon = new TreeNode(parent, Rules::Epsilon);
		error = !parent->setChild(epsilon);
	}

}

void Parser::OP_EXP(TreeNode* parent) {

	if (!error && (currentToken->getType() == State::signPlus ||
			currentToken->getType() == State::signMinus ||
			currentToken->getType() == State::signStar ||
			currentToken->getType() == State::signColon ||
			currentToken->getType() == State::signSmaller ||
			currentToken->getType() == State::signBigger ||
			currentToken->getType() == State::signEquals ||
			currentToken->getType() == State::signECEquals ||
			currentToken->getType() == State::signDoubleAnd)) { // + | - | * | : | < | > | = | =:= | &&

		TreeNode* opExp = new TreeNode (parent, Rules::Op_ExpNode);
		error = !parent->setChild(opExp);
		OP(opExp);

		EXP(opExp);

	} else { //epsilon

		TreeNode* epsilon = new TreeNode(parent, Rules::Epsilon);
		error = !parent->setChild(epsilon);
	}

}

void Parser::OP(TreeNode* parent) {

	if (currentToken->getType() == State::signPlus) { // +

		TreeNode* op = new TreeNode(parent, Rules::OpNode);
		error = !parent->setChild(op);

		TreeNode* leaf = new TreeNode(op, currentToken);
		error = !op->setChild(leaf);

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signMinus) { // -

		TreeNode* op = new TreeNode(parent, Rules::OpNode);
		error = !parent->setChild(op);

		TreeNode* leaf = new TreeNode(op, currentToken);
		error = !op->setChild(leaf);

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signStar) { // *

		TreeNode* op = new TreeNode(parent, Rules::OpNode);
		error = !parent->setChild(op);

		TreeNode* leaf = new TreeNode(op, currentToken);
		error = !op->setChild(leaf);

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signColon) { // :

		TreeNode* op = new TreeNode(parent, Rules::OpNode);
		error = !parent->setChild(op);

		TreeNode* leaf = new TreeNode(op, currentToken);
		error = !op->setChild(leaf);

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signSmaller) { // <

		TreeNode* op = new TreeNode(parent, Rules::OpNode);
		error = !parent->setChild(op);

		TreeNode* leaf = new TreeNode(op, currentToken);
		error = !op->setChild(leaf);

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signBigger) { // >

		TreeNode* op = new TreeNode(parent, Rules::OpNode);
		error = !parent->setChild(op);

		TreeNode* leaf = new TreeNode(op, currentToken);
		error = !op->setChild(leaf);

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signEquals) { // =

		TreeNode* op = new TreeNode(parent, Rules::OpNode);
		error = !parent->setChild(op);

		TreeNode* leaf = new TreeNode(op, currentToken);
		error = !op->setChild(leaf);

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signECEquals) { // =:=

		TreeNode* op = new TreeNode(parent, Rules::OpNode);
		error = !parent->setChild(op);

		TreeNode* leaf = new TreeNode(op, currentToken);
		error = !op->setChild(leaf);

		currentToken = scanner->nextToken();

	} else if (currentToken->getType() == State::signDoubleAnd) { // &&

		TreeNode* op = new TreeNode(parent, Rules::OpNode);
		error = !parent->setChild(op);

		TreeNode* leaf = new TreeNode(op, currentToken);
		error = !op->setChild(leaf);

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


