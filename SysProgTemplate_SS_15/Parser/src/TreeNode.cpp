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

//	this->type = TypeCheck::noType;

	setChildNumbers();
}

TreeNode::TreeNode(TreeNode* parent, Token* token) {
	this->parent = parent;
	this->token = token;
	this->rule = Rules::LeafNode;
	this->childIndex = 0;
	this->children = new TreeNode*[0];

//	this->type = TypeCheck::noType;
}

TreeNode::~TreeNode() {
	delete(parent);
	delete(token);
	delete[] children;
}


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
			children[2] = child;
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
			children[2] = child;
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

/*
TypeCheck TreeNode::getType() {
	return this->type;
}

bool TreeNode::typeCheck(Symboltable* symTab) {

	bool check = true;

	if (rule == Rule::ProgNode) {

		//PROG := DECLS STATEMENTS

		check = children[0]->typeCheck(symTab);
		check = check & children[1]->typeCheck(symTab);
		this->type = TypeCheck::noType;
		return check;

	} else if (rule == Rule::DeclsNode) {

		//DECLS := DECL;DECLS

		check = children[0]->typeCheck(symTab);

		if (check && children[2] != NULL && children[2]->getRule() != Rule::Epsilon) {
			check = check && children[2]->typeCheck(symTab);
		}
		this->type = TypeCheck::noType;
		return check;

	} else if (rule == Rule::DeclNode) {

		//DECL := int ARRAY identifier

		check = children[1]->typeCheck(symTab);

		if (check) {
			if (children[2]->getType != noType ) {
				//Error
				this->type = errorType;
			} else {
				this->type = noType;

				if (children[1]->getType() == arrayType) {
					//Store in Symtab
					//children[2]->getToken()->
				}
			}
		}


	}



	return true;
}
*/
