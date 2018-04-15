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
		elseState,
		intState,
		writeState,
		readState,
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

		statew,
		statewh,
		statewhi,
		statewhil,
		stateW,
		stateWH,
		stateWHI,
		stateWHIL,
		statewr,
		statewri,
		statewrit,
		statei,
		stateI,
		statein,
		statee,
		stateel,
		stateels,
		stateE,
		stateEL,
		stateELS,
		stater,
		statere,
		staterea,


		stateEColon,
		stateSingleAnd,
		stateCommentStart,
		stateCommentStar,

		StateCount
		
	};

};

#endif
