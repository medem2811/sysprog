/*
 * Token.h
 *
 *  Created on: Nov 15, 2017
 *      Author: deme1013
 */

#ifndef TOKEN_H_
#define TOKEN_H_
#


class Token {
public:
	Token(char* value, int line, int column, State::Type type);
	virtual ~Token();

	State::Type getType();
	char* getValue();
	int getValue();
	int getLine();
	int getColumn();

private:
	State::Type type;
	char* content;
	long int contentInt;
	int line;
	int column;

};

#endif /* TOKEN_H_ */
