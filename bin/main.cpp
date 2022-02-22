// code for main driver for the compiler
#include <iostream>
#include <fstream>
#include <sstream>
#include "parse.hpp"
#include <string>

using namespace std;
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		// insists that an input file be passed
		cout << "code rasina file edhi? argument laga pass chey!" << endl;
		exit(0);
	}
	string inFileName = argv[1];
	if (inFileName.substr(inFileName.length() - 2, 2).compare("rc") != 0)
	{
		// insists that the input file is of correct extension
		cout << "thappudu file pass cheshnav!" << endl;
		exit(0);
	}
	string outFileName = inFileName.substr(0, inFileName.length() - 3);
	ifstream inputFile(inFileName);
	stringstream input;
	input << inputFile.rdbuf();
	inputFile.close();
	Lexer lexer(input.str());	   // object of lexer
	Emitter emitter(outFileName);  // object of emitter
	Parser parser(lexer, emitter); // object of parser
	parser.program();			   // entry point for the code
	return 0;
}
