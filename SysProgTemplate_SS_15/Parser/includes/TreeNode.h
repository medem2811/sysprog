/*
 * ParseTree.h
 *
 *  Created on: 24.05.2018
 *      Author: mella
 */

#ifndef PARSER_INCLUDES_TREENODE_H_
#define PARSER_INCLUDES_TREENODE_H_

#include "../../Token/includes/Token.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "Rules.h"
#include "TypeCheck.h"
#include <iostream>
#include <cstdio>
using namespace std;

/*
 * A TreeNode is a node in a ParseTree. It always has a parentnode
 * and one or several childnodes. Except if it's a leaf, then it has
 * no child nodes
 */
class TreeNode {

private:

	TreeNode* parent;
	Rules::Rule rule;
	Token* token;
	TreeNode** children;

	TypeCheck::Type type;

	int childIndex;

	void setChildNumbers();

public:

	/**
	 * creates a new Node
	 */
	TreeNode(TreeNode* parent, Rules::Rule rule);

	/**
	 * creates a new Leaf
	 */
	TreeNode(TreeNode* parent, Token* token);

	~TreeNode();

	Rules::Rule getRule();

	TreeNode* getParent();

	Token* getToken();

	TreeNode* getChild(int index);

	TypeCheck::Type getType();

	/*
	 * assigns a child node to the current node
	 */
	bool setChild(TreeNode* child);

	bool typeCheck();


};




#endif /* PARSER_INCLUDES_TREENODE_H_ */
