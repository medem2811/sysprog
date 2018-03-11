/*
 * LinkedList.h
 *
 *  Created on: 11.03.2018
 *      Author: mella
 */

#ifndef SYMBOLTABLE_INCLUDES_LINKEDLIST_H_
#define SYMBOLTABLE_INCLUDES_LINKEDLIST_H_

#include "Key.h"

class Node {
public:
	Node(Key* key);
	virtual ~Node();

	Node* getNext();
	Key* getInfo();

private:
	Node* next;
	Key* key;
};

class LinkedList {
public:

	LinkedList();
	virtual ~LinkedList();

	void initList(Key* key);

	void insert(Key* key);

	Key* contains(char* value);

	bool isEmpty();

private:
	Node *head;

};

#endif /* SYMBOLTABLE_INCLUDES_LINKEDLIST_H_ */
