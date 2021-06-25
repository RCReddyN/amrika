#include<iostream>

using namespace std;

class Lexer{
    public:
        string source;
        char curChar;
        int curPos;

        Lexer(string input);

        //process next character
        void nextChar();

        //return lookahead character
        char peek();

        //print error message and exit
        void abort(string message);

        //skip whitespace except newlines
        void skipWhiteSpace();

        //skip comments in the code
        void skipComment();

        //return the next token
        void getToken();
};