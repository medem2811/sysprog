/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Buffer.h"
#include <fstream>
#include <iostream>
using namespace std;
#include <stdlib.h>


ifstream inputFile;

/*
 * Constructor: allocates memory for the buffer and opens
 * inputFile
 */
Buffer::Buffer(char* filename, int size) {

	//malloc allocates memory
	this->size = size;
	buffer1 = (char*) malloc(size);
	buffer2 = (char*) malloc(size);

	for (int n=0; n<=size; n++) {
		buffer1[n] = '\0';
		buffer2[n] = '\0';
	}

	//file
	inputFile.open(filename);

	//fills Buffer1 so that getChar can work
	inputFile.read(buffer1, size - 1);

	next = &buffer1[0];
	activeBuffer = 1;

	endOfFile = false;

}

/*
 * Destructor: frees allocated memory and
 * closes file
 */
Buffer::~Buffer() {
	free (buffer1);
	free (buffer2);

}

bool Buffer::eof() {
	return endOfFile;
}

void Buffer::emptyBuffer () {

	if (activeBuffer == 1) {
		for (int n=0; n<=size; n++) {
					buffer2[n] = '\0';
			}
	} else {
		for (int n=0; n<=size; n++) {
					buffer1[n] = '\0';
			}
	}

}

/*
 * fills Buffers and reads current char from
 * buffer. If one buffer is full it switches to the next one.
 *
 */
char Buffer::getChar() {

	char currentChar = *next;

	//checks if end-of-Flag flag was set in last read
	//if not then the next pointer moves forward normally
	if(currentChar != '\0') {
		next++;

	} else if (currentChar == '\0' && !inputFile.eof()) {
		if (activeBuffer == 1) {
			emptyBuffer();
			inputFile.read(buffer2, size - 1);
			activeBuffer = 2;

			next = &buffer2[0];
			return getChar();
		} else {
			emptyBuffer();
			inputFile.read(buffer1, size - 1);
			activeBuffer = 1;

			next = &buffer1[0];
			return getChar();
		}
	}else {
		endOfFile = true;
		inputFile.close();
	}


	return currentChar;

}

/*
 * Goes a step back one step and
 * lets you read the same char again
 */
void Buffer::ungetChar() {

	if (next != &buffer1[0] && next != &buffer2[0]) {
		next--;
	} else if (next == &buffer1[0]) {
		next = &buffer2[size - 2];
	} else {
		next = &buffer1[size - 2];
	}


}


