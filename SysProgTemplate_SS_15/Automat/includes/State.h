/*
 * State.h
 *
 * June 14, 2017
 * deme1013
 */

#ifndef AUTOMAT_INCLUDES_STATE_H_
#define AUTOMAT_INCLUDES_STATE_H_

class State {
public:
	enum Type {
		Start,
		Undefined,
		Error,
		//Final States
		Integer,
		Identifier,
		ifState,
		whileState,
		signPlus,
		signMinus,
		signColon,
		signStar,
		signSmaller,
		signBigger,
		signEquals,
		signCEquals,
		signECEquals,
		signExclamation,
		signDoubleAnd,
		signSemiColon,
		stateComment,
		signRoundBracketOpen,
		signRoundBracketClose,
		signCurlyBracketOpen,
		signCurlyBracketClose,
		signBracketOpen,
		signBracketClose,

		//nonFinalStates
		statew,
		statewh,
		statewhi,
		statewhil,
		stateW,
		stateWH,
		stateWHI,
		stateWHIL,
		statei,
		stateI,
		stateSingleAnd,
		stateEColon,
		stateCommentStart,
		stateCommentStar,

		StateCount
		
	};

};

#endif
