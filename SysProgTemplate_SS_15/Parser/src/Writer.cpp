/*
 * Writer.cpp
 *
 *  Created on: 10.06.2018
 *      Author: mella
 */
#include "../includes/Writer.h"

Writer::Writer(char* filename) {

	out.open(filename);

}

Writer::~Writer() {

}


bool Writer::write(char* text) {

	out << text;

	return true;
}


