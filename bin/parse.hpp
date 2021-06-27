#include<map>
#include<set>
class Parser{
    public:
        map<TokenType, string> tokens;
        Lexer lexer;
        Token curToken;
        Token peekToken;
        set<string> symbols;

        Parser(Lexer lexer);

        //return true if the current token matches
        bool checkToken(TokenType kind);

        //return true if the next token matches
        bool checkPeek(TokenType kind);

        //try to match current token. If not, error. Advances the current token
        void match(TokenType kind);

        //advances the current token
        void nextToken();

        void abort(string message);

        //Production rules

        // program ::= {statement}
        void program();

        //statement
        void statement();

        //newline
        void newline();

        //expression
        void expression();

        //dot
        void dot();

        //comparison
        void comparison();
        
        //check if comparison operator
        bool isComparisonOperator();
        
        //term
        void term();

        //unary
        void unary();

        //primary
        void primary();
};