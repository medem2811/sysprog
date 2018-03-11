#include "../includes/Automat.h"
#include <iostream>
using namespace std;

int main (int argc, char* argv[]){

	Automat* automat;

	automat = new Automat();

	char test[] = {"99 9 t9t\t6\n99\n9"};

	for (int i = 0; i < sizeof(test); i++) {

		cout << test[i] << ": " << automat->checkChar(test[i]);
		cout << " l: " << automat->getTokenLine() << " c: " << automat->getTokenColumn();
		cout << endl;
	}



}
