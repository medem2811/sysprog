
#include "../includes/Writer.h"
#include "../includes/Parser.h"


int main (int argc, char **argv) {

	if (argc < 1) return EXIT_FAILURE;

	Parser* parser = new Parser(argv[1]);

	bool exit = parser->parse();

	if (exit) {
		cout << "Parsing successful!" << endl;
	} else {
		cout << "stop" << endl;
	}

	TreeNode* tree = parser->getRoot();

	exit = tree->typeCheck();

	if (exit) {
		cout << "TypeCheck successful!" << endl;
	} else {
		cout << "stop" << endl;
	}

	Writer* write = new Writer(argv[2]);
	write->makeCode(tree);


}
