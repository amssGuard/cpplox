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
    std::unordered_map<std::string, TokenType> keywords{
        {"and",TokenType::AND},
        {"class",TokenType::CLASS},
        {"else",TokenType::ELSE},
        {"for",TokenType::FALSE},
        {"fun",TokenType::FUN},
        {"if",TokenType::IF},
        {"nil",TokenType::NIL},
        {"or",TokenType::OR},
        {"print",TokenType::PRINT},
        {"return",TokenType::RETURN},
        {"super",TokenType::SUPER},
        {"this",TokenType::THIS},
        {"true",TokenType::TRUE},
        {"var",TokenType::VAR},
        {"while",TokenType::WHILE}
    };

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
    bool isAlpha(char);
    bool isAlphaNumeric(char);
    void identifier();

    public:
    Scanner(std::string source);
    std::vector<Token> scanTokens();
};