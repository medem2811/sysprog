/*
 * StringTab.cpp
 *
 *  Created on: 10.03.2018
 *      Author: mella
 */
#include "../includes/StringTab.h"
#include <stdlib.h>

StringTab::StringTab() {

	this->size = 16384;
	//this->size = 200;
	this->freeSpace = this->size;
	this->table = (char*) calloc(this->freeSpace, sizeof(char*));
	this->freeP = table;

}

StringTab::~StringTab() {

	free(this->table);
	delete[] freeP;
}

char* StringTab::insert(char* lexem, int size) {

	char* p = this->freeP;

	if (size < this->freeSpace) {

		for (int i = 0; i < size; i++) {
			freeP[i] = lexem[i];
		}
		this->freeP += size + 1;
		this->freeSpace -= size + 1;


	} else {
		resize(this->size);
		return insert (lexem, size);
	}

	return p;
}

void StringTab::resize(int n) {

	this->freeSpace = n;
	//char* p = (char*)realloc(this->table, (this->size + n));
	char* p = (char*) malloc(this->size);
	this->table = p;
	this->freeP = this->table;

}

char* StringTab::getTable() {
	return this->table;
}


