#include "../includes/Buffer.h"
#include <fstream>
#include <iostream>
using namespace std;


int main(int argc, char **argv) {

	Buffer*  buffer;

	buffer = new Buffer(argv[1]);

	if (argc > 1) {
		cout << buffer->getChar();
	}

	return 0;
}
