/*
 * TestLinkedList.cpp
 *
 *  Created on: 11.03.2018
 *      Author: mella
 */

#include "../includes/LinkedList.h"
#include <iostream>
using namespace std;

int main (int argc, char **argv) {

	LinkedList* ll = new LinkedList();
	StringTab* st = new StringTab;
	Key* k = new Key(st->insert((char*)"KeytoTheWorld", 13), (char*)"Identifier");
	Key* k2 = new Key(st->insert((char*)"KeytoTheEarth", 13), (char*)"Identifier");
	Key* k3 = new Key(st->insert((char*)"KeytoHeaven", 11), (char*)"Identifier");

	if (ll->isEmpty()) {
		ll->initList(k);
	}

	ll->insert(k2);
	ll->insert(k3);

	cout << "KeytoTheWorld in List? "<<ll->contains((char*)"KeytoTheWorld")<<endl;
	cout << "KeytoTheEarth in List? "<<ll->contains((char*)"KeytoTheEarth")<<endl;
	cout << "KeytoHeaven in List? "<<ll->contains((char*)"KeytoHeaven")<<endl;
	cout << "KeytoHell in List? "<<ll->contains((char*)"KeytoHell")<<endl;



}

