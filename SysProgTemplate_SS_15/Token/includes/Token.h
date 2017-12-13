/*
 * Token.h
 *
 *  Created on: Nov 15, 2017
 *      Author: deme1013
 */

#ifndef TOKEN_H_
#define TOKEN_H_
#include <stdlib.h>
#include <stdio.h>
#include "../../Automat/includes/State.h"


class Token {
public:
	Token(char* value, int line, int column , State::Type type, int size);
	virtual ~Token();

	State::Type getType();
	char* getValue();
	int getValueInt();
	int getLine();
	int getColumn();

private:
	State::Type type;
	char* content;
	long int contentInt;
	int line;
	int column;

};

#endif /* TOKEN_H_ */
