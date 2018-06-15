/*
 * Writer.cpp
 *
 *  Created on: 10.06.2018
 *      Author: mella
 */
#include "../includes/Writer.h"

Writer::Writer(char* filename) {

	code.open(filename);
	labels = 1;

}

Writer::~Writer() {

	code.close();
}


bool Writer::makeCode(TreeNode* root) {

	bool check = true;
	if (root->getRule() == Rules::ProgNode) {
		//PROG := DECLS STATEMENTS

		fprintf (stdout, "making Code...");
		check = makeCode(root->getChild(0));
		check &= makeCode(root->getChild(1));

		code << "STP\n";
		code.close();
	} else if (root->getRule() == Rules::DeclsNode) {
		//DECLS := DECL; DECLS
		check = makeCode(root->getChild(0));
		if (check && root->getChild(2) != NULL) {
			check &= makeCode(root->getChild(2));
		}

	} else if (root->getRule() == Rules::DeclNode) {
		//DECL := int ARRAY identifier

		code << "DS " << "$";
		code << root->getChild(2)->getToken()->getValue();

		if (root->getChild(1)->getRule() == Rules::Epsilon) {
			code << " 1\n";
		} else {
			check = makeCode(root->getChild(1));
		}
	} else if (root->getRule() == Rules::ArrayNode) {
		//ARRAY := [integer]

		code << " ";
		code << root->getChild(1)->getToken()->getValue();
		code << "\n";

	} else if (root->getRule() == Rules::StatsNode) {
		//STATEMENTS := STATEMENT; STATEMENTS

		if (root->getChild(0)->getRule() == Rules::Epsilon) {
			code << "NOP\n";
		} else {
			check = makeCode(root->getChild(0));
			check &= makeCode(root->getChild(2));
		}
	} else if (root->getRule() == Rules::StatAssignment) {
		//STAT := identifier INDEX := EXP

		check = makeCode(root->getChild(3));
		code << "LA " << "$";
		code << root->getChild(0)->getToken()->getValue();
		code << "\n";

		check &= makeCode(root->getChild(1));
		code << "STR\n";

	} else if (root->getRule() == Rules::StatWrite) {
		//STAT := write(EXP)

		check = makeCode(root->getChild(2));
		code << "PRI\n";

	} else if (root->getRule() == Rules::StatRead) {
		//STAT := read(identifier INDEX)

		code << "REA\n";
		code << "LA $";
		code << root->getChild(2)->getToken()->getValue();
		code << "\n";

		check = makeCode(root->getChild(3));
		code << "STR\n";

	} else if (root->getRule() == Rules::StatStatements) {
		//STAT := {STATEMENTS}
		check = makeCode(root->getChild(1));

	} else if (root->getRule() == Rules::StatIfElse) {
		//STAT := if (EXP) STATEMENT else STATEMENT

		int label1 = getLabels();
		int label2 = getLabels();

		check = makeCode(root->getChild(2));

		code << "JIN " << "#";
		code << "label" << label1;
		code << "\n";

		check &= makeCode(root->getChild(4));

		code << "JMP " << "#";
		code << "label" << label2;
		code << "\n";
		code << "#";
		code << "label" << label1;
		code << "\nNOP\n";

		check &= makeCode(root->getChild(6));

		code << "#";
		code << "label" << label2;
		code << "\nNOP\n";

	} else if (root->getRule() == Rules::StatWhile) {
		//STAT := while (EXP) Statement

		int label1 = getLabels();
		int label2 = getLabels();

		code << "#";
		code << "label" << label1;
		code << "\nNOP\n";

		check = makeCode(root->getChild(2));

		code << "JIN ";
		code << "#";
		code << "label" << label2;
		code << "\n";

		check &= makeCode(root->getChild(4));

		code << "JMP " << "#";
		code << "label" << label1;
		code << "\n#";
		code << "label" << label2;
		code << "\nNOP\n";

	} else if (root->getRule() == Rules::ExpNode) {
		//EXP := EXP2 OP_EXP

		if (root->getChild(1)->getType() == TypeCheck::noType) {
			check = makeCode(root->getChild(0));
		} else if (root->getChild(1)->getChild(0)->getType() == TypeCheck::opGreater) {
			check = makeCode(root->getChild(1));
			check &= makeCode(root->getChild(0));
			code << "LES\n";
		} else if (root->getChild(1)->getChild(0)->getType() == TypeCheck::opUnEqual) {
			check = makeCode(root->getChild(0));
			check &= makeCode(root->getChild(1));
			code << "NOT\n";
		} else {
			check = makeCode(root->getChild(0));
			check &= makeCode(root->getChild(1));
		}

	} else if (root->getRule() == Rules::IndexNode) {
		//INDEX := [EXP]

		if (root->getChild(0)->getRule() != Rules::Epsilon) {
			check = makeCode(root->getChild(1));
			code << "ADD\n";
		}

	} else if (root->getRule() == Rules::Exp2Brackets) {
		//EXP2 := (EXP)

		check = makeCode(root->getChild(1));

	} else if (root->getRule() == Rules::Exp2Identifier) {
		//EXP2 := identifier INDEX

		code << "LA " << "$";
		code << root->getChild(0)->getToken()->getValue();
		code << "\n";

		check = makeCode(root->getChild(1));

		code << "LV\n";

	} else if (root->getRule() == Rules::Exp2Integer) {
		//EXP2 := integer

		code << "LC ";
		code << root->getChild(0)->getToken()->getValue();
		code << "\n";

	} else if (root->getRule() == Rules::Exp2Minus) {
		//EXP2 := -EXP
		code << "LC " << "0\n";
		check = makeCode(root->getChild(1));
		code << "SUB\n";

	} else if (root->getRule() == Rules::Exp2Exclamation) {
		//EXP := !EXP

		check = makeCode(root->getChild(1));
		code << "NOT\n";

	} else if (root->getRule() == Rules::Op_ExpNode) {
		//OP_EXP := OP EXP

		if (root->getChild(0)->getRule() != Rules::Epsilon) {
			check = makeCode(root->getChild(1));
			check &= makeCode(root->getChild(0));
		}

	} else if (root->getRule() == Rules::OpNode) {

		if (root->getType() == TypeCheck::opPlus) {
			code << "ADD\n";
		} else if (root->getType() == TypeCheck::opMinus) {
			code << "SUB\n";
		} else if (root->getType() == TypeCheck::opMulti) {
			code << "MUL\n";
		} else if (root->getType() == TypeCheck::opDiv) {
			code << "DIV\n";
		} else if (root->getType() == TypeCheck::opLess) {
			code << "LES\n";
		} else if (root->getType() == TypeCheck::opEqual) {
			code << "EQU\n";
		} else if (root->getType() == TypeCheck::opUnEqual) {
			code << "EQU\n";
		} else if (root->getType() == TypeCheck::opAnd) {
			code << "AND\n";
		}
	}

	return check;

}

int Writer::getLabels() {

	return ++labels;
}
