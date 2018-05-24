#include "../includes/Scanner.h"
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

int main(int argc, char **argv) {

	if (argc < 1) return EXIT_FAILURE;

	ofstream out;

	Scanner* s = new Scanner (argv[1]);
	Token* t;

	out.open(argv[2]);

	while (!s->eof()){
		t = s->nextToken();
		if (t != NULL) {
		if(t->getType() == State::Error) {

			cerr << "Error\t Line: " << t->getLine() << " \t";
			cerr << "Column: " << t->getColumn() << " \t";
			cerr << "Value: " << t->getValue() << endl;
		} else {


			out << "Token ";
			switch((int)t-> getType()) {
			case (int)State::Identifier : 	out << "Identifier\t";
											break;
			case (int)State::Integer :		out << "Integer\t\t";
											break;
			case (int)State::ifState :		out << "If\t\t";
											break;
			case (int)State::whileState :	out << "While\t\t";
											break;
			case (int)State::elseState :	out << "Else\t\t";
											break;
			case (int)State::intState :		out << "Int\t\t";
											break;
			case (int)State::readState :	out << "Read\t\t";
											break;
			case (int)State::writeState :	out << "Write\t\t";
											break;
			case (int)State::signPlus :		out << "+ \t\t";
											break;
			case (int)State::signMinus : 	out << "- \t\t";
											break;
			case (int)State::signColon : 	out << ": \t\t";
											break;
			case (int)State::signStar : 		out << "* \t\t";
											break;
			case (int)State::signSmaller : 	out << "< \t\t";
											break;
			case (int)State::signBigger : 	out << "> \t\t";
											break;
			case (int)State::signEquals : 	out << "= \t\t";
											break;
			case (int)State::signCEquals : 	out << ":= \t\t";
											break;
			case (int)State::signECEquals : 	out << "=:= \t\t";
											break;
			case (int)State::signExclamation : out << "! \t\t";
											break;
			case (int)State::signDoubleAnd : out << "&& \t\t";
											break;
			case (int)State::signSemiColon : out << "; \t\t";
											break;
			case (int)State::signBracketOpen : out << "[ \t\t";
											break;
			case (int)State::signBracketClose : out << "] \t\t";
											break;
			case (int)State::signCurlyBracketOpen : out << "{ \t\t";
											break;
			case (int)State::signCurlyBracketClose: out << "} \t\t";
											break;
			case (int)State::signRoundBracketOpen : out << "( \t\t";
											break;
			case (int)State::signRoundBracketClose : out << ") \t\t";
											break;
			}
			out << "Line: " << t-> getLine() << " \t";
			out << "Column: " << t-> getColumn() << " \t";
			if(t->getType() == State::Integer) {
				out << "Value: " << t-> getValueInt();
			} else if (t->getType() == State::Identifier) {
				out << "Lexem: " << t-> getValue();

			}
			out << endl;
		}
	}

	}
	out.close();



	return EXIT_SUCCESS;
}

