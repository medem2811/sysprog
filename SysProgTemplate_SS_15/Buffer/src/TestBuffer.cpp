#include "../includes/Buffer.h"
#include <fstream>
#include <iostream>
using namespace std;


int main(int argc, char **argv) {

	Buffer*  buffer;

	buffer = new Buffer(argv[1]);


	if (argc > 1) {
			for (int i = 0; i < 7; i++) {
				cout << buffer->getChar();
			}

			for (int j = 0; j < 7; j++) {
				buffer->ungetChar();
			}

			for (int k = 0; k < 7; k++) {
				cout << buffer->getChar();
			}

			while (!buffer->eof()) {
				cout << buffer->getChar();
			}

	}

	return 0;
}
