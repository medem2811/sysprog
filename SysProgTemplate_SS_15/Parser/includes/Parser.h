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
#include "TreeNode.h"
#include <iostream>
#include <cstdio>
using namespace std;


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
	Token* currentToken;
	Token* prevToken;
	bool error;
	TreeNode* root;

	//functions for all the Grammarrules

	// PROG ::= DECLS STATEMENTS
	void PROG();

	// DECLS ::= DECL;DECLS | E
	void DECLS(TreeNode* parent);

	// DECL ::= int ARRAY identifier
	void DECL(TreeNode* parent);

	// ARRAY ::= [int] | E
	void ARRAY(TreeNode* parent);

	// STATEMENTS ::= STATEMENT;STATEMENTS | E
	void STATEMENTS(TreeNode* parent);

	// STATEMENT ::= identifier INDEX:=EXP | write(EXP) |
	// read(identifier INDEX) | {STATEMENTS} | if (EXP) STATEMENT else STATEMENT |
	// while (EXP) STATEMENT
	void STATEMENT(TreeNode* parent);

	// EXP ::= EXP2 OP_EXP
	void EXP(TreeNode* parent);

	// EXP2 ::= (EXP) | identifier INDEX | integer | -EXP2 | !EXP2
	void EXP2(TreeNode* parent);

	// INDEX ::= [EXP] | E
	void INDEX(TreeNode* parent);

	// OP_EXP ::= OP EXP | E
	void OP_EXP(TreeNode* parent);

	// OP ::= + | - | * | : | < | > | = | =:= | &&
	void OP(TreeNode* parent);

	void errorMessage(State::Type type);

};



#endif /* PARSER_INCLUDES_PARSER_H_ */
