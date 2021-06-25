#include<iostream>
#include "lex.hpp"

using namespace std;

class Lexer{
    public:
        string source;
        char curChar;
        int curPos;

        Lexer(string input){
            source = input + "\n";
            curChar = '.';
            curPos = -1;
            nextChar();
        }

        //process next character
        void nextChar(){
            curPos += 1;
            if (curPos >= source.size()){
                curChar = '\0';
            }
            else{
                curChar = source[curPos];
            }
        }

        //return lookahead character
        char peek(){
            if (curPos + 1 >= source.size()){
                return '\0';
            }
            return source[curPos + 1];
        }
        //print error message and exit
        void abort(string message){

        }

        //skip whitespace except newlines
        void skipWhiteSpace(){

        }

        //skip comments in the code
        void skipComment(){

        }

        //return the next token
        void getToken(){

        }
};