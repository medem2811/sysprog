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

Buffer::Buffer(char* filename) {
	// TODO Auto-generated constructor stub

	//malloc allocates memory
	buffer1 = (char*) malloc(Buffer_Limit);
	buffer2 = (char*) malloc(Buffer_Limit);

	next = buffer1;
	//file
	inputFile.open(filename);
}

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
	inputFile.close();
	free (buffer1);
	free (buffer2);

}

void Buffer::fillBuffer (char* buffer) {

	inputFile.read(buffer, Buffer_Limit - 1);
	cout << inputFile.gcount() << " charcaters read.";
}


char Buffer::getChar() {

	inputFile.read(buffer1, Buffer_Limit - 1);
	cout << inputFile.gcount() << " charcaters read.";


	return buffer1[0];

}

void Buffer::ungetChar() {

}


