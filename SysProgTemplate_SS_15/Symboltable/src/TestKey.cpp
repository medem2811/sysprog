/*
 * TestKey.cpp
 *
 *  Created on: 10.03.2018
 *      Author: mella
 */
#include "../includes/Key.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {

	StringTab* strTab = new StringTab();
	Key* key1 = new Key(strTab->insert((char*)"Clexa", 5), (char*)"Identifier");

	cout << "Key 1: Clexa and Clexa - " << key1->compareLexem((char*)"Clexa") << endl;
	cout << "Key 1: Clexa and Sanvers - " << key1->compareLexem((char*)"Sanvers") << endl;

	Key* key2 = new Key(strTab->insert((char*)"Wayhaught", 9), (char*)"Identifier");

	cout << *key2->getPos() << endl;

	cout << "Key 2: Wayhaught and Wayhaught - " << key1->compareLexem((char*)"Wayhaught") << endl;
	cout << "Key 2: Wayhaught and Sanvers - " << key1->compareLexem((char*)"Sanvers") << endl;

	Key* key3 = new Key(strTab->insert((char*)"Hollstein", 9), (char*)"Identifier");

	cout << "Key 3: Hollstein and Hollstein - " << key1->compareLexem((char*)"Hollstein") << endl;
	cout << "Key 3: Hollstein and Sanvers - " << key1->compareLexem((char*)"Sanvers") << endl;



	return 0;
}




