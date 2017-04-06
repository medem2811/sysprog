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
const int Buffer_Limit = 8;

/*
 * Constructor: allocates memory for the buffer and opens
 * inputFile
 */
Buffer::Buffer(char* filename) {

	//malloc allocates memory
	buffer1 = (char*) malloc(Buffer_Limit);
	buffer2 = (char*) malloc(Buffer_Limit);

	for (int n=0; n<=Buffer_Limit; n++) {
		buffer1[n] = '\0';
		buffer2[n] = '\0';
	}

	//file
	inputFile.open(filename);

	//fills Buffer1 so that getChar can work
	inputFile.read(buffer1, Buffer_Limit - 1);

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

/*
 * fills Buffers and reads current char from
 * buffer. If one buffer is full it switches to the next one.
 *
 */
char Buffer::getChar() {

	char currentChar = *next;

	//checks if end-of-Flag flag was set in last read
	//if not then the next pointer moves forward normally
	if(*next != '\0' && !inputFile.eof() ) {
		next++;

	} else if (*next == '\0' && !inputFile.eof()) {
		if (activeBuffer == 1) {
			inputFile.read(buffer2, Buffer_Limit - 1);
			activeBuffer = 2;
			cout << endl << "Buffer switch." << endl;

			next = &buffer2[0];
			currentChar = *next;
		} else {
			inputFile.read(buffer1, Buffer_Limit - 1);
			activeBuffer = 1;

			cout << endl << "Buffer switch." << endl;
			next = &buffer1[0];
			currentChar = *next;
		}
	} else {
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

}


