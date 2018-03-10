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




