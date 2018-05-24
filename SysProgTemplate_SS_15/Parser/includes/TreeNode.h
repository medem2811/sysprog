/*
 * ParseTree.h
 *
 *  Created on: 24.05.2018
 *      Author: mella
 */

#ifndef PARSER_INCLUDES_TREENODE_H_
#define PARSER_INCLUDES_TREENODE_H_

#include "../../Token/includes/Token.h"

/*
 * Types of rules for the Node
 */
typedef enum {

	ProgNode,
	DeclsNode,
	DeclNode,
	ArrayNode,
	StatsNode,
	StatAssignment,
	StatWrite,
	StatRead,
	StatStatements,
	StatIfElse,
	StatWhile,
	ExpNode,
	Exp2Brackets,
	Exp2Identifier,
	Exp2Integer,
	Exp2Minus,
	Exp2Exclamation,
	IndexNode,
	Op_ExpNode,
	OpNode,
	Epsilon,
	LeafNode
} Rule;


/*
 * A TreeNode is a node in a ParseTree. It always has a parentnode
 * and one or several childnodes. Except if it's a leaf, then it has
 * no child nodes
 */
class TreeNode {
public:

	/**
	 * creates a new Node
	 */
	TreeNode(TreeNode* parent, Rule rule);

	/**
	 * creates a new Leaf
	 */
	TreeNode(TreeNode* parent, Token* token);

	~TreeNode();

	Rule getRule();

	TreeNode* getParent();

	Token* getToken();

	bool setChild(TreeNode* child);

private:

	TreeNode* parent;
	Rule rule;
	Token* token;
	TreeNode** children;
	int childIndex;

	void setChildNumbers();
};




#endif /* PARSER_INCLUDES_TREENODE_H_ */
