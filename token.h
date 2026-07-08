#pragma once

#include"token_type.h"
#include<string>
#include<variant>

using LiteralType = std::variant<std::monostate, std::string,double,bool>;

class Token{
    public:
    TokenType type;
    std::string lexeme;
    LiteralType literal;
    int line;
    Token(TokenType, std::string, LiteralType, int);
    std::string to_string();
};