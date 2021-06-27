#include <iostream>
#include <fstream>
#include <sstream>
#include "lex.hpp"
#include "parse.hpp"

using namespace std;
int main(int argc, char **argv){
    cout << "Amrika Compiler" << endl << endl;
    if(argc != 2){
        cout << "code rasina file edhi? argument laga pass chey!";
        exit(0);
    }
    ifstream inputFile(argv[1]);
    stringstream input;
    input << inputFile.rdbuf();

    Lexer lexer(input.str());
    Parser parser(lexer);

    parser.program();

    cout << "Parsing done." << endl;
}