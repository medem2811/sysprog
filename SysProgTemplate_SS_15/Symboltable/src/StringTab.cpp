/*
 * StringTab.cpp
 *
 *  Created on: 10.03.2018
 *      Author: mella
 */
#include "../includes/StringTab.h"

StringTab::StringTab() {

	this->size = 1024;
	this->freeSpace = this->size;
	this->table = (char*) malloc(this->freeSpace);
	this->freeP = table;

}

StringTab::~StringTab() {

	free(table);
}

char* StringTab::insert(char* lexem, int size) {

	char* p = this->freeP;

	if (size < this->freeSpace) {

		for (int i = 0; i < size; i++) {
			this->freeP[i] = lexem[i];
		}
		this->freeP[size] = '\0';
		this->freeP += size + 1;
		this->freeSpace -= size + 1;


	} else {
		resize(1024);
		return insert (lexem, size);
	}

	return p;
}

void StringTab::resize(int n) {

	char* newTable = (char*)malloc(this->size + n);

	for (int i = 0; i < this->size; i++) {
		newTable[i] = this->table[i];
	}

	free(this->table);

	this->freeP = newTable + this->size;

	this->size += n;
	this->freeSpace = n;
	this->table = newTable;

}


