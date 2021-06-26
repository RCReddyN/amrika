#include <iostream>
#include <fstream>
#include <sstream>
#include "lex.hpp"

using namespace std;
int main(void){
    cout << "Amrika Compiler" << endl << endl;
    string input = "raayi enni numbers kavali theesko nums a = 0 b = 1 okavela nums > 0 ainappudu raayi a c = a + b a = b b = c nums = nums - 1.#fibonacci numbers generate cheshey code";
    Lexer lexer(input);

    Token token = lexer.getToken();
    while(token.tokenKind != EOF_){
        cout << token.tokenKind << " " << token.tokenText << endl;
        token = lexer.getToken();
    }
}