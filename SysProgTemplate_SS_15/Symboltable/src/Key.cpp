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




