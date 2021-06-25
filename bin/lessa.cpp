#include <iostream>
#include <fstream>
#include <sstream>
#include "lex.hpp"

using namespace std;
int main(void){
    cout << "Lessa Compiler" << endl << endl;
    string input = "foobar = 123";
    Lexer lexer(input);
    while(lexer.peek() != '\0'){
        cout << lexer.curChar << endl;
        lexer.nextChar();
    }
}