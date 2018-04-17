#include "../includes/Parser.h"


int main (int argc, char **argv) {

	if (argc < 1) return EXIT_FAILURE;

	Parser* parser = new Parser(argv[1]);

	bool exit = parser->parse();

	if (exit) {
		cout << "Parsing successful!" << endl;
	}
}
