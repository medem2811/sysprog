/*
 * TestStringTab.cpp
 *
 *  Created on: 10.03.2018
 *      Author: mella
 */

#include "../includes/StringTab.h"
#include <iostream>
using namespace std;

void print (char* p, int n) {
	for (int i = 0; i < n; i++) {
			if (p[i] == '\0') {
				cout << "-";
			} else {
				cout << p[i];
			}
		}
	cout<<endl;
}


int main(int argc, char **argv) {


 	StringTab* strTab = new StringTab();
	char* p;

	for (int i = 0; i < 800; i++) {
		cout << i << ": ";
		p = strTab->insert((char*) "foo", 3);

		print (p, 4);

		if (i % 25 == 0) {
			strTab->insert((char*)"\n", 1);
		}
	}





}



