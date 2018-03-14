#include "../includes/Symboltable.h"
#include <iostream>
using namespace std;



int main(int argc, char **argv) {

	Symboltable* st;

	st = new Symboltable();

	st->insert((char*)"MUNA", 4, (char*)"Identifier");
	st->insert((char*)"PVRIS", 5, (char*)"Identifier");
	st->insert((char*)"Halsey", 5, (char*)"Identifier");
	Key* key = st->insert((char*)"CHVRCHES", 8, (char*)"Identifier");
	Key* key2 = st->insert((char*)"CHVRCHES", 8, (char*)"Identifier");

	cout << "Key the same? " << (key == key2) << endl;;
	cout << "Find MUNA " << st->lookup((char*)"MUNA") << endl;
	cout << "Find PVRIS " << st->lookup((char*) "PVRIS") << endl;
	cout << "Find LANY " << st->lookup((char*) "LANY") << endl;







	return 0;
}
