/*
 * Writer.h
 *
 *  Created on: 10.06.2018
 *      Author: mella
 */
#include "TreeNode.h"
#include <fstream>
using namespace std;


#ifndef PARSER_INCLUDES_WRITER_H_
#define PARSER_INCLUDES_WRITER_H_

class Writer {

public:
	Writer(char* filename);
	~Writer();

	bool makeCode(TreeNode* root);

private:
	ofstream code;
	int labels;

	int getLabels();
};



#endif /* PARSER_INCLUDES_WRITER_H_ */
