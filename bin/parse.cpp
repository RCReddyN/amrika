#include<iterator>
#include<sstream>

#include "parse.hpp"

Parser::Parser(Lexer tlexer, Emitter temitter){
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
    tokens.insert({chudu, "chudu"});

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
    emitter = temitter;

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
    emitter.headerLine("#include <stdio.h>");
    emitter.headerLine("int main(void){");
    
    //consume newlines in the begining
    while(checkToken(TokenType::NEWLINE)){
        nextToken();
    }

    //parse all the statements in the program
    while(!checkToken(TokenType::EOF_)){
        Parser::statement();
    }

    emitter.emitLine("return 0;");
    emitter.emitLine("}");
    emitter.writeFile();
}

void Parser::statement(){
    //statement ::= "rashey" (expression | STRING) nl
    if(checkToken(TokenType::rashey)){
        nextToken();

        if (Parser::checkToken(TokenType::STRING)){
            //simple string
            stringstream s;
            s << "printf(\"";
            s << curToken.tokenText;
            s << "\\n\");";
            emitter.emitLine(s.str());
            nextToken();
        }
        else{
            //expect an expression
            stringstream s;
            s << "printf(\"%";
            s << ".7f\\n\", (float)(";
            emitter.emit(s.str());
            expression();
            emitter.emitLine("));");
        }
    }

    else if(checkToken(TokenType::chudu)){
        nextToken();
        emitter.emit("if(");
        comparison();
        
        match(TokenType::aithe);
        newline();
        emitter.emitLine("){");
        while(!checkToken(TokenType::DOT)){
            statement();
        }

        match(TokenType::DOT);
        emitter.emitLine("}");
    }

    else if(checkToken(TokenType::okavela)){
        nextToken();
        emitter.emit("while(");
        comparison();
    
        match(TokenType::ainappudu);
        newline();
        emitter.emitLine("){");
        while(!checkToken(TokenType::DOT)){
            statement();
        }
        match(TokenType::DOT);
        emitter.emitLine("}");
    }

    else if(checkToken(TokenType::anuko)){
        nextToken();

        if(symbols.count(curToken.tokenText) == 0){
            symbols.insert(curToken.tokenText);
            stringstream s;
            s << "float ";
            s << curToken.tokenText;
            s << ";";
            emitter.headerLine(s.str());
        }
        emitter.emit(curToken.tokenText);
        emitter.emit(" = ");
        match(TokenType::IDENT);
        match(TokenType::EQ);
        expression();
        emitter.emitLine(";");
    }

    else if(checkToken(TokenType::theesko)){
        nextToken();
        if(symbols.count(curToken.tokenText) == 0){
            symbols.insert(curToken.tokenText);
            stringstream s;
            s << "float ";
            s << curToken.tokenText;
            s << ";";
            emitter.headerLine(s.str());
        }
        emitter.emit("if(0 == scanf(\"%");
        emitter.emit("f\", &");
        emitter.emit(curToken.tokenText);
        emitter.emitLine(")) {");

        emitter.emit(curToken.tokenText);
        emitter.emitLine(" = 0;");

        emitter.emit("scanf(\"%");
        emitter.emitLine("*s\");");

        emitter.emitLine("}");
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
    //require at least one newline
    match(TokenType::NEWLINE);

    //check for extra newlines too.
    while(checkToken(TokenType::NEWLINE)){
        nextToken();
    }
}

void Parser::dot(){
    match(TokenType::DOT);
}

void Parser::comparison(){
    expression();

    //must be at least one comparison operator and another expression
    if(isComparisonOperator()){
        emitter.emit(curToken.tokenText);
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
        emitter.emit(curToken.tokenText);
        nextToken();
        expression();
    }
}

bool Parser::isComparisonOperator(){
    return checkToken(TokenType::GT) || checkToken(TokenType::GTEQ) || checkToken(TokenType::EQEQ) || checkToken(TokenType::LTEQ) || checkToken(TokenType::LT) || checkToken(TokenType::NOTEQ); 
}

void Parser::expression(){
    term();
    while(checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS)){
        emitter.emit(curToken.tokenText);
        nextToken();
        term();
    }
}

void Parser::term(){
    unary();

    while(checkToken(TokenType::ASTERISK) || checkToken(TokenType::SLASH)){
        emitter.emit(curToken.tokenText);
        nextToken();
        unary();    
    }
}

void Parser::unary(){
    if(checkToken(TokenType::PLUS) || checkToken(TokenType::MINUS)){
        emitter.emit(curToken.tokenText);
        nextToken();
    }
    primary();
}

void Parser::primary(){
    if(checkToken(TokenType::NUMBER)){
        emitter.emit(curToken.tokenText);
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
        emitter.emit(curToken.tokenText);
        nextToken();
    }
    else{
        stringstream s;
        s << "Unexpected token at ";
        s << curToken.tokenText;
        abort(s.str());
    }
}