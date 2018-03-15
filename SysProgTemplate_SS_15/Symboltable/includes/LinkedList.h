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

	/*
	 * Links the nodes together
	 */
	void setNext(Node* next);
	/*
	 * Returns the next node
	 */
	Node* getNext();
	/*
	 * Returns the key stored in the Node
	 */
	Key* getKey();

private:
	Node* next;
	Key* key;
};

class LinkedList {
public:

	LinkedList();
	virtual ~LinkedList();

	/*
	 * Initializes the list and fills the head node
	 */
	void initList(Key* key);

	/*
	 * Inserts a new node into the list
	 * with key stored in it
	 */
	void insert(Key* key);

	/*
	 * Checks whether a key is stored in
	 * this list and returns it if yes
	 */
	Key* contains(char* value);

	/*
	 * Checks whether the list is empty or not
	 */
	bool isEmpty();

private:
	Node *head;

};

#endif /* SYMBOLTABLE_INCLUDES_LINKEDLIST_H_ */
