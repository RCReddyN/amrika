#include <iostream>
#include <fstream>
#include <sstream>
#include "parse.hpp"
#include <string>

using namespace std;
int main(int argc, char **argv){
	if(argc != 2){
        	cout << "code rasina file edhi? argument laga pass chey!" << endl;
        	exit(0);
    	}
	string inFileName = argv[1];
	if(inFileName.substr(inFileName.length()-2,2).compare("rc") != 0){
		cout << "thappudu file pass cheshnav!" << endl;
	      	exit(0);
	}
	string outFileName = inFileName.substr(0, inFileName.length()-3);	
    	ifstream inputFile(inFileName);
    	stringstream input;
    	input << inputFile.rdbuf();
    	inputFile.close();
    	Lexer lexer(input.str());
    	Emitter emitter(outFileName);
    	Parser parser(lexer, emitter);

    	parser.program();
	return 0;
}
