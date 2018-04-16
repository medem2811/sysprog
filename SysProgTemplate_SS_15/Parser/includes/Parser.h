/*
 * Parser.h
 *
 * The parser analyzes the Syntax of the file and
 * creates the parsetree
 *
 *  Created on: 15.04.2018
 *      Author: mella
 */
#include "../../Scanner/includes/Scanner.h"

#ifndef PARSER_INCLUDES_PARSER_H_
#define PARSER_INCLUDES_PARSER_H_

class Parser {

public:

	/**
	 * Constructor and Destructor
	 */
	Parser(char* filename);
	~Parser();

	bool parse();

private:

	Scanner* scanner;

	//functions for all the Grammarrules

	// PROG ::= DECLS STATEMENTS
	void PROG();

	// DECLS ::= DECL;DECLS | E
	void DECLS();

	// DECL ::= int ARRAY identifier
	void DECL();

	// ARRAY ::= [int] | E
	void ARRAY();

	// STATEMENTS ::= STATEMENT;STATEMENTS | E
	void STATEMENTS();

	// STATEMENT ::= identifier INDEX:=EXP | write(EXP) |
	// read(identifier INDEX) | {STATEMENTS} | if (EXP) STATEMENT else STATEMENT |
	// while (EXP) STATEMENT
	void STATEMENT();

	// EXP ::= EXP2 OP_EXP
	void EXP();

	// EXP2 ::= (EXP) | identifier INDEX | integer | -EXP2 | !EXP2
	void EXP2();

	// INDEX ::= [EXP] | E
	void INDEX();

	// OP_EXP ::= OP EXP | E
	void OP_EXP();

	// OP ::= + | - | * | : | < | > | = | =:= | &&
	void OP();

};



#endif /* PARSER_INCLUDES_PARSER_H_ */
