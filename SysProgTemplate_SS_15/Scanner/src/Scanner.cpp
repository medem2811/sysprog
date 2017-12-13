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

	//saves the next Char from the buffer
	char c;
	//Token where all the information will be put
	Token* token;
	//decides whether the Token is finished or not
	bool isToken = false;
	//points to where the next char will be put in value
	char* p = value;
	//state that the new Token has
	State::Type tokenType = State::Start;
	//Token size
	int size = 0;

	do { //start reading from buffer until a token is found

		c = buffer->getChar();

		if (c == ' ') { //whitespace
			//skip until Token, automat counts lines etc up
			automat->checkChar(c);

			//if values is empty it means that the last Token has
			//already been created
			if (value[0] != '\0') {
				//chars stored in values up until this whitespace must belong
				//to a Token, so new Token is created
				isToken = true;
			}
		} else {
			//automat calculates the new active state
			//and returns whether the new state is a final state
			bool finalState = automat->checkChar(c);

			//if the new state is not a final state
			//it just saves the current char in values
			//p moves forward
			//and the loop continues
			if (finalState == false) {
				//add new char to value
				*p = c;
				p++;
				size++;
				isToken = false;

			} //a final state has been reached but it's an error
			//all previoulsy stored chars are a new Token --> like whitespace case
			else if (finalState && automat->getLastFinalState() == State::Undefined) {

				//if values is not empty error is new value
				if (value[0] != '\0') {
					//unget Char so that the error Token can be created in the
					//next round
					buffer->ungetChar();
					//set currentState back and reduce column by 1
					//so the column remains correct
					automat->reset(1);

				} else {
					//save error as value and state as error
					*p = c;
					p++;
					size++;
					tokenType = automat->getLastFinalState();
				}
				//either way the Token is finished
				//automat back to start
				automat->reset(0);
				isToken = true;

			} //if Token was in a final State but not sure if it was finished
			else {

				//see if previous states are incompatible like ifhello
				//TODO: different cases have to be evaluated like & is error and && is token
				if (tokenType != State::Start &&
					automat->getLastFinalState() != tokenType) {

					isToken = true;
					//ungetChar from buffer so that new Token can be created in new round
					buffer->ungetChar();
					//set automat back to start state and go a step back
					automat->reset(1);

				}//else if compatible like hello5 then continue
				//tokeType is only saved when the automat reached a final state that is compatible
				//with a previously reached final state
				else {
					*p = c;
					p++;
					size++;
					tokenType = automat->getLastFinalState();
					isToken = false;
				}
			}
		}

	} while (!isToken);


	token = createToken(value, automat->getTokenLine(), automat->getTokenColumn(), tokenType, size);

	//after creating Token, empty the value so that it won't be created twice
	//in case of multiple whitespaces or multiple Errors
	for (int i = 0; i < Buffer_Size; i++) {
		value[i] = '\0';
	}

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
Token* Scanner::createToken(char* value, int line, int column, State::Type type, int size) {

	Token* token = new Token(value, line, column, type, size);

	return token;
}


