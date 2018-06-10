/*
 * Token.h
 *
 *  Created on: Nov 15, 2017
 *      Author: deme1013
 */

#ifndef TOKEN_H_
#define TOKEN_H_
#include <stdlib.h>
#include <cerrno>
#include <stdio.h>
#include "../../Automat/includes/State.h"
#include "../../Symboltable/includes/Key.h"
#include "../../Parser/includes/TypeCheck.h"

class Token {
public:
	Token(char* value, int line, int column , State::Type type, int size);
	virtual ~Token();

	State::Type getType();
	char* getValue();
	int getValueInt();
	int getLine();
	int getColumn();
	Key* getKey();
	void setKey(Key* newKey);

private:
	State::Type type;
	char* content;
	long int contentInt;
	int line;
	int column;
	Key* key;



};

#endif /* TOKEN_H_ */
