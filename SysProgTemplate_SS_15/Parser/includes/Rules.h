/*
 * Rules.h
 *
 *  Created on: 09.06.2018
 *      Author: mella
 */

#ifndef PARSER_INCLUDES_RULES_H_
#define PARSER_INCLUDES_RULES_H_

class Rules {

public:
	/*
	 * Types of rules for the Node
	 */
	enum Rule {

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
	};
};



#endif /* PARSER_INCLUDES_RULES_H_ */
