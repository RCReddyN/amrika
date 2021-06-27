#include<iterator>
#include<map>
#include<set>
#include<sstream>
#include "lex.hpp"
#include "parse.hpp"

Parser::Parser(Lexer tlexer){
    tokens.insert({EOF_, "EOF"});
    tokens.insert({NEWLINE, "NEWLINE"});
    tokens.insert({NUMBER, "NUMBER"});
    tokens.insert({IDENT, "IDENT"});
    tokens.insert({STRING, "STRING"});
    
    tokens.insert({rashey, "rashey"});
    tokens.insert({theesko, "theesko"});
    tokens.insert({okavela, "okavela"});
    tokens.insert({aithe, "aithe"});
    tokens.insert({ainappudu, "ainappudu"});
    tokens.insert({anuko, "anuko"});

    tokens.insert({EQ, "EQ"});
    tokens.insert({PLUS, "PLUS"});
    tokens.insert({MINUS, "MINUS"});
    tokens.insert({ASTERISK, "ASTERISK"});
    tokens.insert({SLASH, "SLASH"});
    tokens.insert({EQEQ, "EQEQ"});
    tokens.insert({NOTEQ, "NOTEQ"});
    tokens.insert({LT, "LT"});
    tokens.insert({LTEQ, "LTEQ"});
    tokens.insert({GT, "GT"});
    tokens.insert({GTEQ, "GTEQ"});
    tokens.insert({DOT, "DOT"});
    
    lexer = tlexer;
    
    nextToken();
    nextToken(); //called twice to initialize current and peek
}

//return true if the current token matches
bool Parser::checkToken(TokenType kind){
    return kind == curToken.tokenKind;
}

//return true if the next token matches
bool Parser::checkPeek(TokenType kind){
    return kind == peekToken.tokenKind;
}

//try to match current token. If not, error. Advances the current token
void Parser::match(TokenType kind){
    if(!checkToken(kind)){
        stringstream s;
        s << "Expected ";
        s << tokens.find(kind)->second;
        s << ", got ";
        s << curToken.tokenText;
        abort(s.str());
    }
    nextToken();
}

//advances the current token
void Parser::nextToken(){
    curToken = peekToken;
    peekToken = lexer.getToken();
}

void Parser::abort(string message){
    cout << "Error. " << message << endl;
    exit(0);
}

void Parser::program(){
    cout << "PROGRAM" << endl;

    //consume newlines in the begining
    while(checkToken(TokenType::NEWLINE)){
        nextToken();
    }

    //parse all the statements in the program
    while(!checkToken(TokenType::EOF_)){
        Parser::statement();
    }
}

void Parser::statement(){
    //statement ::= "rashey" (expression | STRING) nl
    if(checkToken(TokenType::rashey)){
        cout << "STATEMENT - rashey" << endl;
        nextToken();

        if (Parser::checkToken(TokenType::STRING)){
            //simple string
            nextToken();
        }
        else{
            //expect an expression
            expression();
        }
    }

    else if(checkToken(TokenType::okavela)){
        cout << "STATEMENT - okavela" << endl;
        nextToken();
        comparison();
        
        if(checkToken(TokenType::aithe)){
            cout << "STATEMENT - aithe" << endl;
            match(TokenType::aithe);
            newline();

            while(!checkToken(TokenType::DOT)){
                statement();
            }

            match(TokenType::DOT);
        }

        else if(checkToken(TokenType::ainappudu)){
            cout << "STATEMENT - ainappudu" << endl;
            match(TokenType::ainappudu);
            newline();

            while(!checkToken(TokenType::DOT)){
                statement();
            }

            match(TokenType::DOT);
        }
    }

    else if(checkToken(TokenType::anuko)){
        cout << "STATEMENT - anuko" << endl;

        nextToken();

        if(symbols.count(curToken.tokenText) == 0){
            symbols.insert(curToken.tokenText);
        }

        match(TokenType::IDENT);
        match(TokenType::EQ);
        expression();
    }

    else if(checkToken(TokenType::theesko)){
        cout << "SATEMENT - theesko" << endl;
        nextToken();
        if(symbols.count(curToken.tokenText) == 0){
            symbols.insert(curToken.tokenText);
        }
        match(TokenType::IDENT);
    }

    else{
        stringstream s;
        s << "Invalid statement at ";
        s << curToken.tokenText;
        abort(s.str());
    }

    newline();
}

void Parser::newline(){
    cout << "NEWLINE" << endl;

    //require at least one newline
    match(TokenType::NEWLINE);

    //check for extra newlines too.
    while(checkToken(TokenType::NEWLINE)){
        nextToken();
    }
}

void Parser::dot(){
    cout << "DOT" << endl;

    match(TokenType::DOT);
}

void Parser::comparison(){
    cout << "COMPARISON" << endl;

    expression();

    //must be at least one comparison operator and another expression
    if(isComparisonOperator()){
        nextToken();
        expression();
    }
    else{
        stringstream s;
        s << "Expected comparison operator at: ";
        s << curToken.tokenText;
        abort(s.str());
    }

    while(isComparisonOperator()){
        nextToken();
        expression();
    }
}

bool Parser::isComparisonOperator(){
    return checkToken(TokenType::GT) || checkToken(TokenType::GTEQ) || checkToken(TokenType::EQEQ) || checkToken(TokenType::LTEQ) || checkToken(TokenType::LT) || checkToken(TokenType::NOTEQ); 
}

void Parser::expression(){
    cout << "EXPRESSION" << endl;

    term();
    while(checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS)){
        nextToken();
        term();
    }
}

void Parser::term(){
    cout << "TERM" << endl;

    unary();

    while(checkToken(TokenType::ASTERISK) || checkToken(TokenType::SLASH)){
        nextToken();
        unary();    
    }
}

void Parser::unary(){
    cout << "UNARY" << endl;

    if(checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS)){
        nextToken();
    }
    primary();
}

void Parser::primary(){
    cout << "PRIMARY (" << curToken.tokenText << ")" << endl;

    if(checkToken(TokenType::NUMBER)){
        nextToken();
    }
    else if(checkToken(TokenType::IDENT)){
        //ensure variable already exists
        if(symbols.count(curToken.tokenText) == 0){
            stringstream s;
            s << "Referencing variable before assignment: ";
            s << curToken.tokenText;
            abort(s.str());    
        }
        nextToken();
    }
    else{
        stringstream s;
        s << "Unexpected token at ";
        s << curToken.tokenText;
        abort(s.str());
    }
}