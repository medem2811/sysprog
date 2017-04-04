/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer {
public:
	Buffer(char* file);
	virtual ~Buffer();

	char getChar();
	void ungetChar();

private:
	char* buffer1;
	char* buffer2;
	char* next;

	int activeBuffer;

};

#endif /* BUFFER_H_ */
