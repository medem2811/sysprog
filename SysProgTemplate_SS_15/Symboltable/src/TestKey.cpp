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

	cout << "Key 2: Wayhaught and Wayhaught - " << key2->compareLexem((char*)"Wayhaught") << endl;
	cout << "Key 2: Wayhaught and Sanvers - " << key2->compareLexem((char*)"Sanvers") << endl;

	Key* key3 = new Key(strTab->insert((char*)"Hollstein", 9), (char*)"Identifier");

	cout << "Key 3: Hollstein and Hollstein - " << key3->compareLexem((char*)"Hollstein") << endl;
	cout << "Key 3: Hollstein and Sanvers - " << key3->compareLexem((char*)"Sanvers") << endl;

	Key* key4 = new Key(strTab->insert((char*)"Makoann", 7), (char*)"Identifier");

	cout << "Key 4: Makoann and Makoann - " << key4->compareLexem((char*)"Makoann") << endl;
	cout << "Key 4: Makoann and Sanvers - " << key4->compareLexem((char*)"Sanvers") << endl;

	Key* key5 = new Key(strTab->insert((char*)"Supercorp", 9), (char*)"Identifier");

	cout << "Key 5: Supercorp and Supercorp - " << key5->compareLexem((char*)"Supercorp") << endl;
	cout << "Key 5: Supercorp and Sanvers - " << key5->compareLexem((char*)"Sanvers") << endl;

	Key* key6 = new Key(strTab->insert((char*)"+-?whart()[]{}&&!<>_", 20), (char*)"Identifier");

	cout << "Key 6: +-?whart()[]{}&&!<>_ and Supercorp - " << key6->compareLexem((char*)"+-?whart()[]{}&&!<>_") << endl;
	cout << "Key 6: +-?whart()[]{}&&!<>_ and Sanvers - " << key6->compareLexem((char*)"Sanvers") << endl;


	Key* oldKey = new Key(strTab->insert((char*)"asdfghjkluztr5678()&%cfwungtrd§$+#*kjrfj,.;:ht", 47), (char*)"Identifier");
	Key* secondKey = new Key(strTab->insert((char*)"MehrAls5", 8),(char*)"Identifier");

	cout << "Old - " << oldKey->compareLexem((char*)"asdfghjkluztr5678()&%cfwungtrd§$+#*kjrfj,.;:ht") << endl;
	cout << "New - " << secondKey->compareLexem((char*)"MehrAls5") << endl;


	return 0;
}




