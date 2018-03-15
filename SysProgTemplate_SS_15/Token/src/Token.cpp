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
	this->key = NULL;

	if (type == State::Integer) {
		contentInt = strtol(value, NULL, 10);
		if (errno == ERANGE) {
			this->type = State::Error;
		}
	}
	int i = 0;
	while (value[i] != '\0') {
	content [i] = value[i];
	i++;
	}

	content[size] = '\0';


	if(type == State::Undefined || type == State::Start) {
		this->type = State::Error;

	}

}

Token::~Token() {
}

/*
 * GETTER
 */

State::Type Token::getType() {
	return this->type;
}

char* Token::getValue(){
	return this->content;
}
int Token::getValueInt(){
	return this->contentInt;
}
int Token::getLine() {
	return this->line;
}
int Token::getColumn() {
	return this->column;
}

Key* Token::getKey() {
	return this->key;
}

void Token::setKey(Key* newKey) {
	this->key = newKey;
}

