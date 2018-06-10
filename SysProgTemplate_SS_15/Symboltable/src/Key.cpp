/*
 * Key.cpp
 *
 *  Created on: 10.03.2018
 *      Author: mella
 */

#include "../includes/Key.h"

Key::Key(char* myPos, char* type) {

	this->key = myPos;
	this->type = type;
	this->typeCheck = TypeCheck::noType;

}

Key::~Key() {
	delete[] this;
}

char* Key::getPos() {
	return this->key;
}

char* Key::getType() {
	return this->type;
}

void Key::setTypeCheck(TypeCheck::Type type) {
	this->typeCheck = type;
}

TypeCheck::Type Key::getTypeCheck() {
	return this->typeCheck;
}
/*
 * Compares two Lexems with each other to see
 * if there already exists a key for this lexem
 */
bool Key::compareLexem(char* lexem) {

	char* p = this->key;
	char* k = lexem;


	while (*p != '\0') {
		if (*p != *k) {
			return false;
		}

		p++;
		k++;
	}

	if (*k != '\0') {
		return false;
	}

	return true;
}




