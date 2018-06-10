/*
 * Writer.h
 *
 *  Created on: 10.06.2018
 *      Author: mella
 */
#include <fstream>
using namespace std;


#ifndef PARSER_INCLUDES_WRITER_H_
#define PARSER_INCLUDES_WRITER_H_

class Writer {

public:
	Writer(char* filename) {
		out.open(filename);
	}
	~Writer();

	void write(char* text) {
		out << text;
	}

private:
	ofstream out;
};



#endif /* PARSER_INCLUDES_WRITER_H_ */
