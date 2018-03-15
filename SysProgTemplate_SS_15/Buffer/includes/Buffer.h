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
	Buffer(char* file, int size);
	virtual ~Buffer();

	/**
	 * Reads a char from the file
	 * and returns it
	 */
	char getChar();
	/*
	 * Goes a step back and lets
	 * the buffer read the char again
	 */
	void ungetChar();
	/*
	 * Checks if the end of the file
	 * was reached yet
	 */
	bool eof();

private:
	char* buffer1;
	char* buffer2;
	char* next;
	int size;
	bool endOfFile;

	void emptyBuffer();

	int activeBuffer;

};

#endif /* BUFFER_H_ */
