#include "../includes/Buffer.h"
#include <fstream>
#include <iostream>
using namespace std;


int main(int argc, char **argv) {

	Buffer*  buffer;

	buffer = new Buffer();

	if (argc > 1) {
		ifstream file (argv[1]);

		char c;
		int a = 0;
		if (file.is_open()) {
			cout << "it's britney, bitch"<<endl;
			while (file.get(c)) {
				cout << c;
			}
		} else {
			cout << "shit." <<endl;
		}

		file.close();
	}

	return 0;
}
