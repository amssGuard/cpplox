#pragma once
#include"token.h"
#include<string>
#include<vector>
#include<unordered_map>

class Scanner{
    private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType);
    void addToken(TokenType,LiteralType);
    bool match(char);
    char peek();
    void string();
    bool isDigit(char);
    void number();
    char peekNext();

    public:
    Scanner(std::string source);
    std::vector<Token> scanTokens();
};