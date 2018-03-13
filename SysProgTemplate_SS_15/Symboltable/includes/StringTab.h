/*
 * StringTab.h
 *
 *  Created on: 10.03.2018
 *      Author: mella
 */

#ifndef SYMBOLTABLE_INCLUDES_STRINGTAB_H_
#define SYMBOLTABLE_INCLUDES_STRINGTAB_H_

class StringTab {
public:

	StringTab();
	virtual ~StringTab();

	char* insert(char* lexem, int size);

	char* getTable();

private:

	void resize(int n);

	char* freeP;

	int freeSpace;

	char* table;

	int size;

};



#endif /* SYMBOLTABLE_INCLUDES_STRINGTAB_H_ */
