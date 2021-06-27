#include<iostream>
#include<sstream>
#include "lex.hpp"

using namespace std;

string ctos(char ch){
    stringstream s;
    s << ch;
    return s.str();
}

Lexer::Lexer(string input){
    keywords.insert({"rashey", rashey});
    keywords.insert({"theesko", theesko});
    keywords.insert({"okavela", okavela});
    keywords.insert({"aithe", aithe});
    keywords.insert({"ainappudu", ainappudu});
    keywords.insert({"anuko", anuko});

    source = input + "\n";
    curChar = '.';
    curPos = -1;
    nextChar();
}

//process next character
void Lexer::nextChar(){
    curPos += 1;
    if (curPos >= source.size()){
        curChar = '\0';
    }
    else{
        curChar = source[curPos];
    }
}

//return lookahead character
char Lexer::peek(){
    if (curPos + 1 >= source.size()){
        return '\0';
    }
    return source[curPos + 1];
}
//print error message and exit
void Lexer::abort(string message){
    cout << "Lexing error. " << message << endl;
    exit(0);
}

//skip whitespace except newlines
void Lexer::skipWhiteSpace(){
    while(curChar == ' ' || curChar == '\t' || curChar == '\r'){
        nextChar();
    }
}

//skip comments in the code
void Lexer::skipComment(){
    if(curChar == '#'){
        while(curChar != '\n'){
            nextChar();
        }
    }
}

//return the next token
Token Lexer::getToken(){
    skipWhiteSpace();
    skipComment();
    Token token;
//Check the first character of this token to decide what it is.
//If it is a multiple character operator, number, identifier, or a keyword then we will process the rest.
    if(curChar == '+'){//Plus token
        token = Token(ctos(curChar), PLUS);
    }
    else if(curChar == '-'){//Minus token
        token = Token(ctos(curChar), MINUS);
    }
    else if(curChar == '*'){//Asterisk token
        token = Token(ctos(curChar), ASTERISK);
    }
    else if(curChar == '/'){//Slash token
        token = Token(ctos(curChar), SLASH);
    }
    else if(curChar == '='){
        //check if = or ==
        if(peek() == '='){
            char lastChar = curChar;
            nextChar();
            token = Token(ctos(lastChar) + ctos(curChar), EQEQ);
        }
        else{
            token = Token(ctos(curChar), EQ);
        }
    }

    else if(curChar == '>'){
        //check if > or >=
        if(peek() == '='){
            char lastChar = curChar;
            nextChar();
            token = Token(ctos(lastChar) + ctos(curChar), GTEQ);
        }
        else{
            token = Token(ctos(curChar), GT);
        }
    }

    else if(curChar == '<'){
        //check if < or <=
        if(peek() == '='){
            char lastChar = curChar;
            nextChar();
            token = Token(ctos(lastChar) + ctos(curChar), LTEQ);
        }
        else{
            token = Token(ctos(curChar), LT);
        }
    }

    else if(curChar == '!'){
        if(peek() == '='){
            char lastChar = curChar;
            nextChar();
            token = Token(ctos(lastChar) + ctos(curChar), NOTEQ);
        }
        else{
            stringstream s;
            s << "kavalsindi !=, kani unnademo !" << peek();
            abort(s.str());
        }
    }

    else if(curChar =='\"'){
        //Get characters between the quotations.
        nextChar();
        int startPos = curPos;
        while(curChar != '\"'){
            if (curChar == '\r' || curChar == '\n' || curChar == '\t' || curChar == '\\' || curChar == '%'){
                abort("ee string la unsupported character edho undi chusko."); 
            }
            nextChar();
            string tokText = source.substr(startPos, curPos-startPos+1);
            token = Token(tokText, STRING);
        }
    }

    else if(isdigit(curChar)){
        //leading character is a digit, this must be a number
        //get all consecutive digits and decimal if there is one.
        int startPos = curPos;
        while(isdigit(peek())){
            nextChar();
        }
        if(peek() == '.'){
            nextChar();
            if (!isdigit(peek())){
                abort("Number la digit kakunda vere character edho undi chusko.");
            }
            while(isdigit(peek())){
                nextChar();
            }
        }
        string tokText = source.substr(startPos, curPos-startPos+1);
        token = Token(tokText, NUMBER);
    }

    else if(isalpha(curChar)){
        //leading character is a letter, so this must be an identifier or a keyword.
        //get all consecutive alpha characters.

        int startPos = curPos;
        while(isalpha(peek())){
            nextChar();
        }
        //check if the token is in the list of keywords.
        string tokText = source.substr(startPos, curPos-startPos+1);
        auto itr = keywords.find(tokText);
        if(itr->second >= 100 && itr->second < 200){
            token = Token(tokText, itr->second);
        }
        else{
            token = Token(tokText, IDENT);
        }
    }

    else if(curChar == '.'){//Dot token
        token = Token(ctos(curChar), DOT);
    }

    else if(curChar == '\n'){//newline token
        token = Token(ctos(curChar), NEWLINE); 
    }
    else if(curChar == '\0'){//eof token
        token = Token(ctos(curChar), EOF_);
    }
    else{
        //Unknown token
        stringstream s;
        s << "ee thelvani token endho mari: \"" << curChar  <<"\"";
        abort(s.str());
    }
    nextChar();
    return token;
}