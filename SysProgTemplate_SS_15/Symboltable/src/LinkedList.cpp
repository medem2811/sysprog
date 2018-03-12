/*
 * LinkedList.cpp
 *
 *  Created on: 11.03.2018
 *      Author: mella
 */

#include "../includes/LinkedList.h"
#include <iostream>
using namespace std;

Node::Node(Key* key) {
	this->key = key;
	this->next = NULL;
}
Node::~Node() {
	delete [] key;
	delete [] next;
}

Node* Node::getNext() {
	return this->next;
}
Key* Node::getKey() {
	return this->key;
}

void Node::setNext(Node* next) {
	this->next = next;
}



LinkedList::LinkedList() {
	this->head = new Node(NULL);
}

LinkedList::~LinkedList() {
	delete [] head;
}

void LinkedList::initList(Key* key) {

	this->head = new Node(key);
}

void LinkedList::insert(Key* key) {

	Node* node = new Node (key);

	Node* active = this->head;

	while (active) {
		if (active->getNext() == NULL) {
			active->setNext(node);
			return;
		}

		active = active->getNext();
	}
}

Key* LinkedList::contains(char* value) {

	Node* active = this->head;

	while(active) {

		Key* comp = active->getKey();

		if (comp->compareLexem(value)) {
			return comp;
		}
		active = active->getNext();
	}

	return NULL;
}

bool LinkedList::isEmpty() {

	if (this->head->getKey() == NULL) {
		return true;
	}
	return false;
}




