/*
 * TreeNode.cpp
 *
 *  Created on: 24.05.2018
 *      Author: mella
 */

#include "../includes/TreeNode.h"

TreeNode::TreeNode(TreeNode* parent, Rule rule) {
	this->parent = parent;
	this->rule = rule;
	this->childIndex = 0;

	setChildNumbers();
}

TreeNode::TreeNode(TreeNode* parent, Token* token) {
	this->parent = parent;
	this->token = token;
	this->rule = Rule::LeafNode;
	this->childIndex = 0;
	this->children = new TreeNode*[0];
}

TreeNode::~TreeNode() {
	delete(parent);
	delete(token);
	delete[] children;
}


void TreeNode::setChildNumbers() {

	switch ((int) rule) {
	case (int)Rule::ProgNode:
				children = new TreeNode*[2];
				break;
	case (int)Rule::DeclsNode:
				children = new TreeNode*[3];
				break;
	case (int)Rule::DeclNode:
				children = new TreeNode*[3];
				break;
	case (int)Rule::ArrayNode:
				children = new TreeNode*[3];
				break;
	case (int)Rule::StatsNode:
				children = new TreeNode*[3];
				break;
	case (int)Rule::StatAssignment:
				children = new TreeNode*[4];
				break;
	case (int)Rule::StatWrite:
				children = new TreeNode*[4];
				break;
	case (int)Rule::StatRead:
				children = new TreeNode*[5];
				break;
	case (int)Rule::StatStatements:
				children = new TreeNode*[3];
				break;
	case (int)Rule::StatIfElse:
				children = new TreeNode*[7];
				break;
	case (int)Rule::StatWhile:
				children = new TreeNode*[5];
				break;
	case (int)Rule::ExpNode:
				children = new TreeNode*[2];
				break;
	case (int)Rule::Exp2Brackets:
				children = new TreeNode*[3];
				break;
	case (int)Rule::Exp2Identifier:
				children = new TreeNode*[2];
				break;
	case (int)Rule::Exp2Integer:
				children = new TreeNode*[1];
				break;
	case (int)Rule::Exp2Minus:
				children = new TreeNode*[2];
				break;
	case (int)Rule::Exp2Exclamation:
				children = new TreeNode*[2];
				break;
	case (int)Rule::IndexNode:
				children = new TreeNode*[3];
				break;
	case (int)Rule::Op_ExpNode:
				children = new TreeNode*[2];
				break;
	case (int)Rule::OpNode:
				children = new TreeNode*[1];
				break;
	}
}

bool TreeNode::setChild(TreeNode* child) {

	//PROG := DECLS STATEMENTS
	if (rule == Rule::ProgNode) {
		if (childIndex == 0 && (child->getRule() == Rule::DeclNode ||
				child->getRule() == Rule::Epsilon)) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rule::StatsNode ||
			child->getRule() == Rule::Epsilon)) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //DECLS := DECL;DECLS | Epsilon
	else if (rule == Rule::DeclsNode) {
		if (childIndex == 0 && child->getRule() == Rule::DeclNode) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signSemiColon) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && (child->getRule() == Rule::DeclsNode ||
				child->getRule() == Rule::Epsilon)) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //DECL := int ARRAY identifier
	else if (rule == Rule::DeclNode) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::intState) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rule::ArrayNode ||
				child->getRule() == Rule::Epsilon)) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::Identifier) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //ARRAY := [integer] | Epsilon
	else if (rule == Rule::ArrayNode) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signBracketOpen) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::Integer) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signBracketClose) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //STATEMENTS := STATEMENT;STATEMENTS | Epsilon
	else if (rule == Rule::StatsNode) {
		if (childIndex == 0 && (child->getRule() == Rule::StatAssignment ||
				child->getRule() == Rule::StatWrite ||
				child->getRule() == Rule::StatRead ||
				child->getRule() == Rule::StatStatements ||
				child->getRule() == Rule::StatIfElse ||
				child->getRule() == Rule::StatWhile)) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signSemiColon) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && (child->getRule() == Rule::StatsNode ||
				child->getRule() == Rule::Epsilon)) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := identifier INDEX := EXP
	else if (rule == Rule::StatAssignment) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::Identifier) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rule::IndexNode ||
				child->getRule() == Rule::Epsilon)) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signCEquals) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 3 && child->getRule() == Rule::ExpNode) {
			children[3] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := write(EXP)
	else if (rule == Rule::StatWrite) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::writeState) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketOpen) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rule::ExpNode) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 3 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketClose) {
			children[3] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := read(identifier INDEX)
	else if (rule == Rule::StatRead) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::readState) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketOpen) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::Identifier) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 3 && (child->getRule() == Rule::IndexNode ||
				child->getRule() == Rule::Epsilon)) {
			children[3] = child;
			childIndex++;
			return true;
		} else if (childIndex == 4 && (child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketClose)) {
			children[4] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := {STATEMENTS}
	else if (rule == Rule::StatStatements) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType()== State::signCurlyBracketOpen) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rule::StatsNode ||
				child->getRule() == Rule::Epsilon)) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signCurlyBracketClose) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := if(EXP)STATEMENTelseSTATEMENT
	else if (rule == Rule::StatIfElse) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::ifState) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketOpen) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rule::ExpNode) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 3 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketClose) {
			children[3] = child;
			childIndex++;
			return true;
		} else if (childIndex == 4 && (child->getRule() == Rule::StatAssignment ||
				child->getRule() == Rule::StatWrite ||
				child->getRule() == Rule::StatRead ||
				child->getRule() == Rule::StatStatements ||
				child->getRule() == Rule::StatIfElse ||
				child->getRule() == Rule::StatWhile)) {
			children[4] = child;
			childIndex++;
			return true;
		} else if (childIndex == 5 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::elseState) {
			children[5] = child;
			childIndex++;
			return true;
		} else if (childIndex == 6 && (child->getRule() == Rule::StatAssignment ||
				child->getRule() == Rule::StatWrite ||
				child->getRule() == Rule::StatRead ||
				child->getRule() == Rule::StatStatements ||
				child->getRule() == Rule::StatIfElse ||
				child->getRule() == Rule::StatWhile)) {
			children[6] = child;
			childIndex++;
			return true;
		}
	} //STATEMENT := while(EXP)STATEMENT
	else if (rule == Rule::StatWhile) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::whileState) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketOpen) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rule::ExpNode) {
			children[2] = child;
			childIndex++;
			return true;
		} else if (childIndex == 3 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketClose) {
			children[3] = child;
			childIndex++;
			return true;
		} else if (childIndex == 4 && (child->getRule() == Rule::StatAssignment ||
				child->getRule() == Rule::StatWrite ||
				child->getRule() == Rule::StatRead ||
				child->getRule() == Rule::StatStatements ||
				child->getRule() == Rule::StatIfElse ||
				child->getRule() == Rule::StatWhile)) {
			children[4] = child;
			childIndex++;
			return true;
		}
	} //EXP := EXP2 OP_EXP
	else if (rule == Rule::ExpNode) {
		if (childIndex == 0 && (child->getRule() == Rule::Exp2Brackets ||
				child->getRule() == Rule::Exp2Identifier ||
				child->getRule() == Rule::Exp2Integer ||
				child->getRule() == Rule::Exp2Minus ||
				child->getRule() == Rule::Exp2Exclamation)) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rule::Op_ExpNode ||
				child->getRule() == Rule::Epsilon)) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //EXP2 := (EXP)
	else if (rule == Rule::Exp2Brackets) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketOpen) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rule::ExpNode) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signRoundBracketClose) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //EXP2 := identifier INDEX
	else if (rule == Rule::Exp2Identifier) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::Identifier) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && (child->getRule() == Rule::IndexNode ||
				child->getRule() == Rule::Epsilon)) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //EXP2 := integer
	else if (rule == Rule::Exp2Integer) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::Integer) {
			children[0] = child;
			childIndex++;
			return true;
		}
	} //EXP2 := -EXP2
	else if (rule == Rule::Exp2Minus) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signMinus) {
			children[0] = child;
			childIndex++;
			return true;
		}else if (childIndex == 1 && (child->getRule() == Rule::Exp2Brackets ||
				child->getRule() == Rule::Exp2Identifier ||
				child->getRule() == Rule::Exp2Integer ||
				child->getRule() == Rule::Exp2Minus ||
				child->getRule() == Rule::Exp2Exclamation)) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //EXP2 := !EXP2
	else if (rule == Rule::Exp2Exclamation) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signExclamation) {
			children[0] = child;
			childIndex++;
			return true;
		}else if (childIndex == 1 && (child->getRule() == Rule::Exp2Brackets ||
				child->getRule() == Rule::Exp2Identifier ||
				child->getRule() == Rule::Exp2Integer ||
				child->getRule() == Rule::Exp2Minus ||
				child->getRule() == Rule::Exp2Exclamation)) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //INDEX := [EXP] | Epsilon
	else if (rule == Rule::IndexNode) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signBracketOpen) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rule::ExpNode) {
			children[1] = child;
			childIndex++;
			return true;
		} else if (childIndex == 2 && child->getRule() == Rule::LeafNode &&
				child->getToken()->getType() == State::signBracketClose) {
			children[2] = child;
			childIndex++;
			return true;
		}
	} //OP_EXP := OP EXP | Epsilon
	else if (rule == Rule::Op_ExpNode) {
		if (childIndex == 0 && child->getRule() == Rule::OpNode) {
			children[0] = child;
			childIndex++;
			return true;
		} else if (childIndex == 1 && child->getRule() == Rule::ExpNode) {
			children[1] = child;
			childIndex++;
			return true;
		}
	} //OP := + | - | * | : | < | > | = | =:= | &&
	else if (rule == Rule::OpNode) {
		if (childIndex == 0 && child->getRule() == Rule::LeafNode &&
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

Rule TreeNode::getRule() {
	return rule;
}

TreeNode* TreeNode::getParent() {
	return parent;
}

Token* TreeNode::getToken() {
	if (rule == Rule::LeafNode) {
		return token;
	}

	return NULL;
}
