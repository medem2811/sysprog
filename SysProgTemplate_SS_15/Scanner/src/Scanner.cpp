/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Scanner.h"
#include <iostream>
using namespace std;

/*
 * Constructor: Creates a new Automat and a Buffer for the run
 *
 *
 *
 * @param filename is the name of the testfile
 */
Scanner::Scanner(char* filename) {

	Buffer_Size = 1024;

	automat = new Automat();
	buffer = new Buffer(filename, Buffer_Size);

	//to save Chars actually belonging to the Token
	value = new char [Buffer_Size];
	type = State::Start;

	//to save a decent amount of chars until the next Token
	//is found
	tempChars = new char [Buffer_Size];


}

/*
 * Destructor
 */
Scanner::~Scanner() {
	delete buffer;
	delete automat;
}

Token* Scanner::nextToken() {

	//reset tempChars to fill it up with the new Token
	resetTemp();
	//saves the next Char from the buffer
	char c;
	//Token where all the information will be put
	Token* token;
	//decides whether the Token is finished or not
	bool isToken = false;

	do { //start reading from buffer until a token is found

		c = buffer->getChar();

		if (c == 't') { //undefined
			//make error Token
			automat->checkChar('\0');
			value[0] = c;
			token = createToken(value, automat->getLine(), automat->getColumn(), State::Error);
			isToken = true;

		} else if (c == 0) { //empty Char
			//TODO

		} else { //if actual readable Char

		}

	} while (!isToken);

	//check if eof is the next symbol
	//if yes then the eof flag has been switched in buffer
	buffer->getChar();
	buffer->ungetChar();

	return token;
}

/*
 * checks with buffer if end of file is reached
 */
bool Scanner::eof() {
	return buffer->eof();
}

/**
 * creates a Token and fills it with values
 * also calculates Key and stuff TODO
 */
Token* Scanner::createToken(char* value, int line, int column, State::Type type) {

	Token* token = new Token(value, line, column, type);

	return token;
}

/**
 * resets the temporary Chars (empties it)
 * after every found Token
 */
void Scanner::resetTemp() {

}

