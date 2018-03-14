#include "../includes/Token.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

	Token* token;
	char* value = (char*)"boobies";
	int line = 1;
	int column = 5;
	State::Type type = State::Undefined;

	token = new Token(value, line, column, type, sizeof(value));

	cout << "Token 1:" << endl;
	cout << token->getValue() << endl;
	cout << token->getLine() << endl;
	cout << token->getColumn() << endl;
	cout << token->getType() << endl;

	Token* token2;
	token2 = new Token ((char*)"1", 7, 45, State::Integer, 1);

	cout << "Token 2:" << endl;
	cout << token2->getValueInt() << endl;
	cout << token2->getLine() << endl;
	cout << token2->getColumn() << endl;
	cout << token2->getType() << endl;

}
