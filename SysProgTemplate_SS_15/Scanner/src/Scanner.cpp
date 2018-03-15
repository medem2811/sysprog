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
 * @param filename is the name of the testfile
 */
Scanner::Scanner(char* filename) {

	Buffer_Size = 1024;

	automat = new Automat();
	buffer = new Buffer(filename, Buffer_Size);
	table = new Symboltable();

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

/**
 * reads the next Token out of the Chars given by the
 * buffer
 */
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
	//to check if it's =:
	bool eColon = false;

	do { //start reading from buffer until a token is found

		c = buffer->getChar();

		if (eof()) {
			tokenType = automat->getLastFinalState();
			isToken = true;

		} else if (automat->isComment()) {
			automat->checkChar(c);
			isToken = false;
		}else {
			if (c == ' ' || c == '\t' || c == '\n') { //whitespace
				//to keep automat counting
				automat->checkChar(c);

				//if values is empty it means that the last Token has
				//already been created
				if (value[0] != '\0') {

					if (eColon) {
						buffer->ungetChar();
						buffer->ungetChar();
						if (c == '\n') {
							automat->reset(1, 1);
						} else {
							automat->reset(2, 0);
						}
						value[1] = '\0';
						size--;
					}
					//chars stored in values up until this whitespace must belong
					//to a Token, so new Token is created
					tokenType = automat->getLastFinalState();
					isToken = true;
				}
			} else {
				//automat calculates the new active state
				//and returns whether the new state is a final state
				bool finalState = automat->checkChar(c);
				State::Type lastFinalState = automat->getLastFinalState();

				//checks if a comment just started
				if (automat->isComment()) {
					value[0] = '\0';
					value[1] = '\0';
					size = 0;
					p = value;
					tokenType = State::Start;

				}
				//if the new state is not a final state
				//it just saves the current char in values
				//p moves forward
				//and the loop continues
				else if (!finalState) {
					//add new char to value
					*p = c;
					p++;
					size++;
					isToken = false;
					eColon = c == ':';


				} //a final state has been reached but it's an error
				//all previoulsy stored chars are a new Token --> like whitespace case
				else if (finalState && lastFinalState == State::Undefined) {

					//if values is not empty error is new value
					if (value[0] != '\0') {
						//unget Char so that the error Token can be created in the
						//next round
						buffer->ungetChar();

						//set currentState back and reduce column by 1
						//so the column remains correct
						tokenType = automat->reset(1, 0);

						if (eColon && c != '=') {
							buffer->ungetChar();
							automat->reset(1, 0);

							value[1] = '\0';
							size--;
							tokenType = State::signEquals;
						}
						isToken = true;

					} else {
						//save error as value and state as error
						eColon = false;
						*p = c;
						p++;
						size++;
						tokenType = lastFinalState;
						automat->reset(0, 0);
					}
					//either way the Token is finished
					isToken = true;

				}
				//if Token was in a final State but not sure if it was finished
				else {

					//see if previous states are incompatible like ifhello
					if (tokenType != State::Start && !automat->isCompatible(tokenType, lastFinalState)) {

						isToken = true;
						tokenType = lastFinalState;
						//ungetChar from buffer so that new Token can be created in new round
						buffer->ungetChar();
						//set automat back to start state and go a step back
						automat->reset(1, 0);

					}//else if compatible like hello5 then continue
					//tokeType is only saved when the automat reached a final state that is compatible
					//with a previously reached final state
					else {
						eColon = false;
						*p = c;
						p++;
						size++;
						tokenType = lastFinalState;
						isToken = false;
					}
				}
			}
		}

	} while (!isToken);

	if ((int)tokenType <= (int)State::stateI && (int)tokenType >= (int)State::statew) {
		tokenType = State::Identifier;
	}

	token = createToken(value, automat->getTokenLine(), automat->getTokenColumn(), tokenType, size);

	//after creating Token, empty the value so that it won't be created twice
	//in case of multiple whitespaces or multiple Errors
	for (int i = 0; i < size; i++) {
		value[i] = '\0';
	}

	//check if eof is the next symbol
	//if yes then the eof flag has been switched in buffer
	if (!eof()) {
		buffer->getChar();
		buffer->ungetChar();
	}

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
 * also calculates Key and stuff
 */
Token* Scanner::createToken(char* value, int line, int column, State::Type type, int size) {

	Token* token = new Token(value, line, column, type, size);

	if (type == State::Identifier) {
		token->setKey(table->insert(value, size, (char*)"Identifier"));
	}


	return token;
}


