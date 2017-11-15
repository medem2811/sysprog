/*
 * Token.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: deme1013
 */

#include "../includes/Token.h"

/*
 * Constructor creates a new Token
 * @param value: content of the Token, might be converted to int
 * @param line : line in file of Token
 * @param column: column in file of Token
 * @param type: Tokentype
 */

Token::Token (char* value, int line, int column, State::Type type) {

	this->type = type;
	this->column = column;
	this->line = line;
	this->content = value;
	this->contentInt = 0;

	if (type == State::Number) {
		contentInt = strtol(value, NULL, 10);
	}

}

