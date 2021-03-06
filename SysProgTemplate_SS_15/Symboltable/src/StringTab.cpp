/*
 * StringTab.cpp
 *
 *  Created on: 10.03.2018
 *      Author: mella
 */
#include "../includes/StringTab.h"
#include <stdlib.h>

StringTab::StringTab() {

	this->size = 65536;
	//this->size = 50;
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

		//inserts the lexem into the table
		for (int i = 0; i < size; i++) {
			freeP[i] = lexem[i];
		}
		//sets a NULL value after each lexem
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

	//makes more space for new Lexems

	//char* p = (char*)realloc(this->table, (this->size + n));
	char* p = (char*) calloc(this->size, sizeof(char*));
	this->table = p;
	this->freeP = this->table;

}

char* StringTab::getTable() {
	return this->table;
}


