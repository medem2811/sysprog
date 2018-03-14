#include "../includes/Scanner.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {

	if (argc < 1) return EXIT_FAILURE;

	Scanner* s = new Scanner (argv[1]);
	Token* t;

	while (!s->eof()){
		t = s->nextToken();

		cout << "TokenType: " << t-> getType();
		cout << " line: " << t-> getLine();
		cout << " column: " << t-> getColumn();
		if(t->getType() == State::Integer) {
			cout << " value: " << t-> getValueInt();
		} else {
			cout << " value: " << t-> getValue();

		}
		if(t->getType() == State::Identifier) {
			cout << " key: " << t->getKey()->getPos();
		}
		cout << endl;

	}


	return EXIT_SUCCESS;
}

