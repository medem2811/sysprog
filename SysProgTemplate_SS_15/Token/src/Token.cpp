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

Token::Token (char* value, int line, int column, State::Type type, int size) {

	this->type = type;
	this->column = column;
	this->line = line;
	this->contentInt = 0;
	this->content = new char[size + 1];

	if (type == State::Integer) {
		contentInt = strtol(value, NULL, 10);
	} else {
		int i = 0;
		while (value[i] != '\0') {
			content [i] = value[i];
			i++;

		}
		content[size] = '\0';

	}

	if(contentInt == -1) {
		type = State::Undefined;

		//ERROR PRINT OUT
	}

}

Token::~Token() {
}

/*
 * GETTER
 */

State::Type Token::getType() {
	return type;
}

char* Token::getValue(){
	return content;
}
int Token::getValueInt(){
	return contentInt;
}
int Token::getLine() {
	return line;
}
int Token::getColumn() {
	return column;
}

