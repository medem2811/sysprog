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
const int Buffer_Limit = 1024;

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

	next = &buffer1[0];
	activeBuffer = 1;

	//file
	inputFile.open(filename);

}

/*
 * Destructor: frees allocated memory and
 * closes file
 */
Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
	inputFile.close();
	free (buffer1);
	free (buffer2);

}

/*
 * fills Buffers and reads current char from
 * buffer. If one buffer is full it switches to the next one.
 *
 */
char Buffer::getChar() {

	char currentChar;

	inputFile.read(buffer1, Buffer_Limit - 1);

	inputFile.read(buffer2, Buffer_Limit - 1);

	if(next != '\0') {

	}



	return '\0';

}

/*
 * Goes a step back one step and
 * lets you read the same char again
 */
void Buffer::ungetChar() {

}


