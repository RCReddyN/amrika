#include<iostream>
#include<map>

enum TokenType{
    null,
    EOF_ = -1,
    NEWLINE = 0,
    NUMBER = 1,
    IDENT = 2,
    STRING = 3,

    rashey = 101,
    theesko = 102,
    okavela = 103,
    aithe = 104,
    ainappudu = 105,
    anuko = 106,
    
    EQ = 201,
    PLUS = 202,
    MINUS = 203,
    ASTERISK = 204,
    SLASH = 205,
    EQEQ = 206,
    NOTEQ = 207,
    LT  = 208,
    LTEQ = 209,
    GT = 210,
    GTEQ = 211,
    DOT = 212 
};

using namespace std;

class Token{
    public:
        string tokenText;
        TokenType tokenKind;
        Token(){}
        Token(string tText, TokenType tKind){
            tokenText = tText;
            tokenKind = tKind;
        }
};

class Lexer{
    public:
        string source;
        char curChar;
        int curPos;
        map<string, TokenType> keywords;

        Lexer(){
            
        }
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
        Token getToken();
};