/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Buffer.h"
#include <fstream>
using namespace std;
#include <stdlib.h>


fstream inputFile;
const int Buffer_Limit = 1024;

Buffer::Buffer(char* filename) {
	// TODO Auto-generated constructor stub
	char* buffer1; //Pointer to the Buffers
	char* buffer2;

	//malloc allocates memory
	buffer1 = malloc(Buffer_Limit);
	buffer2 = malloc(Buffer_Limit);

	//Pointer that shows where user is
	char * next;

	//file
	fstream inputFile (filename);
}

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
	inputFile.close();
	free (buffer1);
	free (buffer2);

}

char Buffer::getChar() {

	return 'v';
}

void Buffer::ungetChar() {

}


