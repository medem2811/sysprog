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
	this->key = NULL;
	this->next = NULL;
}
Node::~Node() {

}

Node* Node::getNext() {
	return NULL;
}
Key* Node::getInfo() {
	return NULL;
}



LinkedList::LinkedList() {
	this->head = new Node(NULL);
}

LinkedList::~LinkedList() {

}

void LinkedList::initList(Key* key) {

}

void LinkedList::insert(Key* key) {

}

Key* LinkedList::contains(char* value) {

	return NULL;
}

bool LinkedList::isEmpty() {

	return false;
}




