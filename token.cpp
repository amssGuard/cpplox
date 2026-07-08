#include"token.h"

Token::Token(TokenType type,std::string lexeme,LiteralType literal,int line)
:type(type),lexeme(lexeme),literal(literal),line(line){}

std::string Token::to_string(){return lexeme;}

//std::string Token::to_string(){return std::string to_string(type)+" "+lexeme+" "+std::string to_string(literal);}

//std::string to_string(TokenType type){
//    switch(type){
//        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
//        default: return "UNKNOWN";
//    }
//}