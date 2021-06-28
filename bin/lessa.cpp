#include <iostream>
#include <fstream>
#include <sstream>
#include "parse.hpp"

using namespace std;
int main(int argc, char **argv){
    if(argc != 2){
        cout << "code rasina file edhi? argument laga pass chey!";
        exit(0);
    }
    ifstream inputFile(argv[1]);
    stringstream input;
    input << inputFile.rdbuf();
    inputFile.close();

    Lexer lexer(input.str());
    Emitter emitter("out.c");
    Parser parser(lexer, emitter);

    parser.program();
    cout << "Compiling aipoindi" << endl;
}