/*
 * TreeNode.cpp
 *
 *  Created on: 24.05.2018
 *      Author: mella
 */

#include "../includes/TreeNode.h"

TreeNode::TreeNode(TreeNode* parent, Rules::Rule rule) {
	this->parent = parent;
	this->rule = rule;
	this->childIndex = 0;

	this->type = TypeCheck::noType;

	setChildNumbers();
}

TreeNode::TreeNode(TreeNode* parent, Token* token) {
	this->parent = parent;
	this->token = token;
	this->rule = Rules::LeafNode;
	this->childIndex = 0;
	this->children = new TreeNode*[0];

	this->type = TypeCheck::noType;
}

TreeNode::~TreeNode() {
	delete(parent);
	delete(token);
	delete[] children;
}


/**
 * initializes how many children a node can have tops
 * not all nodes have to be filled
 */
void TreeNode::setChildNumbers() {

	switch ((int) rule) {
	case (int)Rules::ProgNode:
				children = new TreeNode*[2];
				break;
	case (int)Rules::DeclsNode:
				children = new TreeNode*[3];
				break;
	case (int)Rules::DeclNode:
				children = new TreeNode*[3];
				break;
	case (int)Rules::ArrayNode:
				children = new TreeNode*[3];
				break;
	case (int)Rules::StatsNode:
				children = new TreeNode*[3];
				break;
	case (int)Rules::StatAssignment:
				children = new TreeNode*[4];
				break;
	case (int)Rules::StatWrite:
				children = new TreeNode*[4];
				break;
	case (int)Rules::StatRead:
				children = new TreeNode*[5];
				break;
	case (int)Rules::StatStatements:
				children = new TreeNode*[3];
				break;
	case (int)Rules::StatIfElse:
				children = new TreeNode*[7];
				break;
	case (int)Rules::StatWhile:
				children = new TreeNode*[5];
				break;
	case (int)Rules::ExpNode:
				children = new TreeNode*[2];
				break;
	case (int)Rules::Exp2Brackets:
				children = new TreeNode*[3];
				break;
	case (int)Rules::Exp2Identifier:
				children = new TreeNode*[2];
				break;
	case (int)Rules::Exp2Integer:
				children = new TreeNode*[1];
				break;
	case (int)Rules::Exp2Minus:
				children = new TreeNode*[2];
				break;
	case (int)Rules::Exp2Exclamation:
				children = new TreeNode*[2];
				break;
	case (int)Rules::IndexNode:
				children = new TreeNode*[3];
				break;
	case (int)Rules::Op_ExpNode:
				children = new TreeNode*[2];
				break;
	case (int)Rules::OpNode:
				children = new TreeNode*[1];
				break;
	}
}

/*
 * sets a child node at the right index
 */
bool TreeNode::setChild(TreeNode* child) {

	//PROG := DECLS STATEMENTS
	if (rule == Rules::ProgNode) {
		if (childIndex == 0 && (child->getRule() == Rules::DeclsNode ||
				child->getRule() == Rules::Epsilon)) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rules::StatsNode ||
			child->getRule() == Rules::Epsilon)) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //DECLS := DECL;DECLS | Epsilon
	else if (rule == Rules::DeclsNode) {
		if (childIndex == 0 && child->getRule() == Rules::DeclNode) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signSemiColon) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && (child->getRule() == Rules::DeclsNode ||
				child->getRule() == Rules::Epsilon)) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //DECL := int ARRAY identifier
	else if (rule == Rules::DeclNode) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::intState) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rules::ArrayNode ||
				child->getRule() == Rules::Epsilon)) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::Identifier) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //ARRAY := [integer] | Epsilon
	else if (rule == Rules::ArrayNode) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signBracketOpen) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::Integer) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signBracketClose) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //STATEMENTS := STATEMENT;STATEMENTS | Epsilon
	else if (rule == Rules::StatsNode) {
		if (childIndex == 0 && (child->getRule() == Rules::StatAssignment ||
				child->getRule() == Rules::StatWrite ||
				child->getRule() == Rules::StatRead ||
				child->getRule() == Rules::StatStatements ||
				child->getRule() == Rules::StatIfElse ||
				child->getRule() == Rules::StatWhile)) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signSemiColon) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && (child->getRule() == Rules::StatsNode ||
				child->getRule() == Rules::Epsilon)) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := identifier INDEX := EXP
	else if (rule == Rules::StatAssignment) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::Identifier) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rules::IndexNode ||
				child->getRule() == Rules::Epsilon)) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signCEquals) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 3 && child->getRule() == Rules::ExpNode) {
			children[3] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := write(EXP)
	else if (rule == Rules::StatWrite) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::writeState) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketOpen) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rules::ExpNode) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 3 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketClose) {
			children[3] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := read(identifier INDEX)
	else if (rule == Rules::StatRead) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::readState) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketOpen) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::Identifier) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 3 && (child->getRule() == Rules::IndexNode ||
				child->getRule() == Rules::Epsilon)) {
			children[3] = child;
			childIndex++;
			return true;
		} else if (childIndex == 4 && (child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketClose)) {
			children[4] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := {STATEMENTS}
	else if (rule == Rules::StatStatements) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType()== State::signCurlyBracketOpen) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rules::StatsNode ||
				child->getRule() == Rules::Epsilon)) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signCurlyBracketClose) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := if(EXP)STATEMENTelseSTATEMENT
	else if (rule == Rules::StatIfElse) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::ifState) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketOpen) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rules::ExpNode) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 3 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketClose) {
			children[3] = child;
			childIndex++;
			return true;
		} else if (childIndex == 4 && (child->getRule() == Rules::StatAssignment ||
				child->getRule() == Rules::StatWrite ||
				child->getRule() == Rules::StatRead ||
				child->getRule() == Rules::StatStatements ||
				child->getRule() == Rules::StatIfElse ||
				child->getRule() == Rules::StatWhile)) {
			children[4] = child;
			childIndex++;
			return true;
		} else if (childIndex == 5 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::elseState) {
			children[5] = child;
			childIndex++;
			return true;
		} else if (childIndex == 6 && (child->getRule() == Rules::StatAssignment ||
				child->getRule() == Rules::StatWrite ||
				child->getRule() == Rules::StatRead ||
				child->getRule() == Rules::StatStatements ||
				child->getRule() == Rules::StatIfElse ||
				child->getRule() == Rules::StatWhile)) {
			children[6] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := while(EXP)STATEMENT
	else if (rule == Rules::StatWhile) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::whileState) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketOpen) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rules::ExpNode) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 3 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketClose) {
			children[3] = child;
			childIndex++;
			return true;
		} else if (childIndex == 4 && (child->getRule() == Rules::StatAssignment ||
				child->getRule() == Rules::StatWrite ||
				child->getRule() == Rules::StatRead ||
				child->getRule() == Rules::StatStatements ||
				child->getRule() == Rules::StatIfElse ||
				child->getRule() == Rules::StatWhile)) {
			children[4] = child;
			childIndex++;
			return true;
		}
	} //EXP := EXP2 OP_EXP
	else if (rule == Rules::ExpNode) {
		if (childIndex == 0 && (child->getRule() == Rules::Exp2Brackets ||
				child->getRule() == Rules::Exp2Identifier ||
				child->getRule() == Rules::Exp2Integer ||
				child->getRule() == Rules::Exp2Minus ||
				child->getRule() == Rules::Exp2Exclamation)) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rules::Op_ExpNode ||
				child->getRule() == Rules::Epsilon)) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //EXP2 := (EXP)
	else if (rule == Rules::Exp2Brackets) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketOpen) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rules::ExpNode) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketClose) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //EXP2 := identifier INDEX
	else if (rule == Rules::Exp2Identifier) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::Identifier) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rules::IndexNode ||
				child->getRule() == Rules::Epsilon)) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //EXP2 := integer
	else if (rule == Rules::Exp2Integer) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::Integer) {
			children[0] = child;
			childIndex++;
			return true;
		}
	} //EXP2 := -EXP2
	else if (rule == Rules::Exp2Minus) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signMinus) {
			children[0] = child;
			childIndex++;
			return true;
		}else if (childIndex == 1 && (child->getRule() == Rules::Exp2Brackets ||
				child->getRule() == Rules::Exp2Identifier ||
				child->getRule() == Rules::Exp2Integer ||
				child->getRule() == Rules::Exp2Minus ||
				child->getRule() == Rules::Exp2Exclamation)) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //EXP2 := !EXP2
	else if (rule == Rules::Exp2Exclamation) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signExclamation) {
			children[0] = child;
			childIndex++;
			return true;
		}else if (childIndex == 1 && (child->getRule() == Rules::Exp2Brackets ||
				child->getRule() == Rules::Exp2Identifier ||
				child->getRule() == Rules::Exp2Integer ||
				child->getRule() == Rules::Exp2Minus ||
				child->getRule() == Rules::Exp2Exclamation)) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //INDEX := [EXP] | Epsilon
	else if (rule == Rules::IndexNode) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signBracketOpen) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rules::ExpNode) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rules::LeafNode &&
				child->getToken()->getType() == State::signBracketClose) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //OP_EXP := OP EXP | Epsilon
	else if (rule == Rules::Op_ExpNode) {
		if (childIndex == 0 && child->getRule() == Rules::OpNode) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rules::ExpNode) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //OP := + | - | * | : | < | > | = | =:= | &&
	else if (rule == Rules::OpNode) {
		if (childIndex == 0 && child->getRule() == Rules::LeafNode &&
				(child->getToken()->getType() == State::signPlus ||
				child->getToken()->getType() == State::signMinus ||
				child->getToken()->getType() == State::signStar ||
				child->getToken()->getType() == State::signColon ||
				child->getToken()->getType() == State::signSmaller ||
				child->getToken()->getType() == State::signBigger ||
				child->getToken()->getType() == State::signEquals ||
				child->getToken()->getType() == State::signECEquals ||
				child->getToken()->getType() == State::signDoubleAnd)) {
			children[0] = child;
			childIndex++;
			return true;
		}
	}

	fprintf(stderr, "Error building parseTree at Token: %s /t Line: %d /t Column: %d",
			this->token->getValue(), this->token->getLine(), this->token->getColumn());
	return false;
}

Rules::Rule TreeNode::getRule() {
	return rule;
}

TreeNode* TreeNode::getParent() {
	return parent;
}

Token* TreeNode::getToken() {
	if (rule == Rules::LeafNode) {
		return token;
	}

	return NULL;
}

TypeCheck::Type TreeNode::getType() {

	if (this->rule == Rules::LeafNode && this->token->getType() == State::Identifier) {
		return this->token->getKey()->getTypeCheck();
	}
	return this->type;
}


bool TreeNode::typeCheck() {

	bool check = true;

	if (rule == Rules::ProgNode) {

		//PROG := DECLS STATEMENTS

		fprintf (stdout, "Begin typecheck...\n");

		check = children[0]->typeCheck();
		check = check && children[1]->typeCheck();
		this->type = TypeCheck::noType;
		return check;

	} else if (rule == Rules::DeclsNode) {

		//DECLS := DECL;DECLS

		check = children[0]->typeCheck();

		if (check && children[2] != NULL && children[2]->getRule() != Rules::Epsilon) {
			check = check && children[2]->typeCheck();
		}
		this->type = TypeCheck::noType;
		return check;

	} else if (rule == Rules::DeclNode) {

		//DECL := int ARRAY identifier

		check = children[1]->typeCheck();

		if (check) {
			if (children[2]->getType() != TypeCheck::noType) {

				Token* error = children[2]->getToken();
				fprintf(stderr, "ERROR Identifier already defined Line: %d\t Column: %d\t Token: %s\n",
						error->getLine(), error->getColumn(), error->getValue());
				this->type = TypeCheck::errorType;
				return false;
			} else {
				this->type = TypeCheck::noType;

				if (children[1]->getType() == TypeCheck::arrayType) {
					children[2]->getToken()->getKey()->setTypeCheck(TypeCheck::intArrayType);
				} else {
					children[2]->getToken()->getKey()->setTypeCheck(TypeCheck::intType);
				}
			}
		} else {
			this->type = TypeCheck::errorType;
			return false;
		}

		return check;

	} else if (rule == Rules::ArrayNode) {

		//ARRAY := [integer] | Epsilon

		if (children[1]->getToken()->getValueInt() > 0) {
			this->type = TypeCheck::arrayType;
		} else {
			Token* error = children[1]->getToken();
			fprintf(stderr, "ERROR: no valid dimension Line: %d\t Column: %d\t Token: %s\n",
					error->getLine(), error->getColumn(), error->getValue());
			this->type = TypeCheck::errorType;
			return false;
		}
		return check;
	} else if (rule == Rules::StatsNode) {

		//STATEMENTS := STATEMENT; STATEMENTS | Epsilon

		check = children[0]->typeCheck();

		if (check && children[2] != NULL && children[2]->getRule() != Rules::Epsilon) {
			check &= children[2]->typeCheck();
		}

		this->type = TypeCheck::noType;
		return check;
	} else if (rule == Rules::StatAssignment) {

		//STATEMENT := identifier INDEX := EXP

		check = children[1]->typeCheck();
		check &= children[3]->typeCheck();

		if (check) {
			if (children[0]->getType() == TypeCheck::noType) {
				Token* error = children[0]->getToken();
				fprintf(stderr, "ERROR: Identifier not defined Line: %d\t Column: %d\t Token: %s\n",
						error->getLine(), error->getColumn(), error->getValue());
				return false;
			} else if (children[3]->getType() == TypeCheck::intType && (
				(children[0]->getType() == TypeCheck::intType && children[1]->getType() == TypeCheck::noType)
				|| (children[0]->getType() == TypeCheck::intArrayType && children[1]->getType() == TypeCheck::arrayType)))
			{
				this->type = TypeCheck::noType;
			} else {
				Token* error = children[0]->getToken();
				fprintf(stderr, "ERROR: incompatible types Line: %d\t Column: %d\t Token: %s\n",
						error->getLine(), error->getColumn(), error->getValue());
				this->type = TypeCheck::errorType;
				return false;
			}
		}
		return check;
	} else if (rule == Rules::StatWrite) {

		//STATEMENT := write(EXP)
		check = children[2]->typeCheck();
		this->type = TypeCheck::noType;

		return check;
	} else if (rule == Rules::StatRead) {

		//STATEMENT := read(identifier INDEX)
		check = children[3]->typeCheck();

		if (check) {
			if (children[2]->getType() == TypeCheck::noType) {
				Token* error = children[2]->getToken();
				fprintf(stderr, "ERROR: Identifier not defined Line: %d\t Column: %d\t Token: %s\n",
						error->getLine(), error->getColumn(),error->getValue());
				return false;
			} else if (
					(children[2]->getType() == TypeCheck::intType && children[3]->getType() == TypeCheck::noType)
					|| (children[2]->getType() == TypeCheck::intArrayType && children[3]->getType() == TypeCheck::arrayType))
			{
				this->type = TypeCheck::noType;
			} else {
				Token* error = children[2]->getToken();
				fprintf(stderr, "ERROR: incompatible types Line: %d\t Column: %d\t Token: %s\n",
						error->getLine(), error->getColumn(), error->getValue());
				this->type = TypeCheck::errorType;
				return false;
			}
		}
		return check;

	} else if (rule == Rules::StatStatements) {

		//STATEMENT := {STATEMENTS}

		check = children[1]->typeCheck();
		this->type = TypeCheck::noType;

		return check;
	} else if (rule == Rules::StatIfElse) {

		//STATEMENT := if (EXP) STATEMENT else STATEMENT

		check = children[2]->typeCheck();
		check &= children[4]->typeCheck();
		check &= children[6]->typeCheck();

		if (!check || children[2]->getType() == TypeCheck::errorType) {
			this->type = TypeCheck::errorType;
			return false;
		} else {
			this->type = TypeCheck::noType;
		}
		return check;
	} else if (rule == Rules::StatWhile) {

		//STATEMENT := while (EXP) STATEMENT

		check = children[2]->typeCheck();
		check &= children[4]->typeCheck();

		if (!check || children[2]->getType() == TypeCheck::errorType) {
			this->type = TypeCheck::errorType;
			return false;
		} else {
			this->type = TypeCheck::noType;
		}
		return check;
	} else if (rule == Rules::IndexNode) {

		//INDEX := [EXP]

		check = children[1]->typeCheck();
		if (!check || children[1]->getType() == TypeCheck::errorType) {
			this->type = TypeCheck::errorType;
			return false;
		} else {
			this->type = TypeCheck::arrayType;
		}
		return check;
	} else if (rule == Rules::ExpNode) {

		//EXP := EXP2 OP_EXP

		check = children[0]->typeCheck();
		check &= children[1]->typeCheck();

		if (check && children[1]->getType() == TypeCheck::noType) {
			this->type = children[0]->getType();
		} else if (children[0]->getType() != children[1]->getType()) {
			this->type = TypeCheck::errorType;
			return false;
		} else {
			this->type = children[0]->getType();
		}
		return check;
	} else if (rule == Rules::Exp2Brackets) {

		//EXP := (EXP)

		check = children[1]->typeCheck();
		this->type = children[1]->getType();
		return check;
	} else if (rule == Rules::Exp2Identifier) {

		//EXP := identifier INDEX

		check = children[1]->typeCheck();

		if(check) {
			if (children[1]->getType() == TypeCheck::noType) {
				Token* error = children[0]->getToken();
				fprintf(stderr, "ERROR: identifier not defined Line: %d\t Column: %d\t Token: %s\n",
						error->getLine(), error->getColumn(), error->getValue());
				this->type = TypeCheck::errorType;
				return false;
			} else if (children[0]->getType() == TypeCheck::intType &&
					children[1]->getType() == TypeCheck::noType) {
				this->type = children[0]->getType();
			} else if (children[0]->getType() == TypeCheck::intArrayType &&
					children[1]->getType() == TypeCheck::arrayType) {
				this->type = TypeCheck::intType;
			} else {
				Token* error = children[0]->getToken();
				fprintf(stderr, "ERROR: no primitive Type Line: %d\t Column: %d\t Token: %s\n",
						error->getLine(), error->getColumn(), error->getValue());
				this->type = TypeCheck::errorType;
				return false;
			}
		}
		return check;
	} else if (rule == Rules::Exp2Integer) {
		this->type = TypeCheck::intType;
		return check;
	} else if (rule == Rules::Exp2Minus) {
		check = children[1]->typeCheck();
		this->type = children[1]->getType();
		return check;
	} else if (rule == Rules::Exp2Exclamation) {
		check = children[1]->typeCheck();
		if (children[1]->getType() != TypeCheck::intType) {
			this->type = TypeCheck::errorType;
			return false;
		} else {
			this->type = TypeCheck::intType;
		}

		return check;
	} else if (rule == Rules::Op_ExpNode) {

		//OP_EXP := OP EXP

		check = children[0]->typeCheck();
		check &= children[1]->typeCheck();

		this->type = children[1]->getType();

		return check;
	} else if (rule == Rules::OpNode) {

		TreeNode* child = children[0];
		if (child->getToken()->getType() == State::signPlus) {
			this->type = TypeCheck::opPlus;
		} else if (child->getToken()->getType() == State::signMinus) {
			this->type = TypeCheck::opMinus;
		} else if (child->getToken()->getType() == State::signStar) {
			this->type = TypeCheck::opMulti;
		} else if (child->getToken()->getType() == State::signColon) {
			this->type = TypeCheck::opDiv;
		} else if (child->getToken()->getType() == State::signSmaller) {
			this->type = TypeCheck::opLess;
		} else if (child->getToken()->getType() == State::signBigger) {
			this->type = TypeCheck::opGreater;
		} else if (child->getToken()->getType() == State::signEquals) {
			this->type = TypeCheck::opEqual;
		} else if (child->getToken()->getType() == State::signECEquals) {
			this->type = TypeCheck::opUnEqual;
		} else if (child->getToken()->getType() == State::signDoubleAnd) {
			this->type = TypeCheck::opAnd;
		}
	}

	return check;
}

TreeNode* TreeNode::getChild(int index) {
	return children[index];
}

