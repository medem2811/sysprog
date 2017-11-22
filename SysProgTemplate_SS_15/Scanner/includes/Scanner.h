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

class Scanner {
public:
	Scanner(char* filename);
	virtual ~Scanner();

	Token* nextToken();
	bool eof();

private:
	Automat* automat;
	Buffer* buffer;

	int Buffer_Size;

	char* value;
	State::Type type;

	char* tempChars;

	Token* createToken(char* value, int line, int column, State::Type type);
	void resetTemp();


};

#endif /* SCANNER_H_ */
