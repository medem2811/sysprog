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

	void resize();
};



#endif /* SYMBOLTABLE_INCLUDES_STRINGTAB_H_ */
