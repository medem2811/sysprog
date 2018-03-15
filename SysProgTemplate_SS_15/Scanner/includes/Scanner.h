/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include "../../Automat/includes/Automat.h"
#include "../../Buffer/includes/Buffer.h"
#include "../../Token/includes/Token.h"
#include "../../Symboltable/includes/Symboltable.h"

class Scanner {
public:
	Scanner(char* filename);
	virtual ~Scanner();

	/**
	 * Reads a Token and returns it
	 */
	Token* nextToken();
	/*
	 * Checks if the end of the file
	 * was reached yet
	 */
	bool eof();

private:
	Automat* automat;
	Buffer* buffer;
	Symboltable* table;

	int Buffer_Size;

	char* value;
	State::Type type;

	char* tempChars;

	Token* createToken(char* value, int line, int column, State::Type type, int size);


};

#endif /* SCANNER_H_ */
