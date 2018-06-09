/*
 * TypeCheck.h
 *
 *  Created on: 09.06.2018
 *      Author: mella
 */

#ifndef PARSER_INCLUDES_TYPECHECK_H_
#define PARSER_INCLUDES_TYPECHECK_H_

class TypeCheck {
public:
	enum Type {
		intType,
		intArrayType,
		arrayType,
		noType,
		errorType,
		opPlus,
		opMinus,
		opMulti,
		opDiv,
		opLess,
		opGreater,
		opEqual,
		opUnEqual,
		opAnd,
		undefined
	};

};



#endif /* PARSER_INCLUDES_TYPECHECK_H_ */
