#include "../includes/Buffer.h"
#include <fstream>
#include <iostream>
using namespace std;


int main(int argc, char **argv) {

	Buffer*  buffer;

	buffer = new Buffer(argv[1]);


	if (argc > 1) {
			for (int i = 0; i < 100; i++) {
				cout << buffer->getChar();
			}

			for (int j = 0; j < 10; j++) {
				buffer->ungetChar();
			}

			for (int k = 0; k < 10; k++) {
				cout << buffer->getChar();
			}

			while (!buffer->eof()) {
				buffer->getChar();
			}

	}

	return 0;
}
