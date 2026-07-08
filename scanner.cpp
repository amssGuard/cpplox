#include"scanner.h"
#include"lox.h"

Scanner::Scanner(std::string source):source(source){}

std::vector<Token> Scanner::scanTokens(){
    while(!isAtEnd()){
        start = current;
        scanToken();
    }
    tokens.push_back(Token(TokenType::EOF_TOKEN,"",std::monostate{},line));
}

bool Scanner::isAtEnd(){
    return current >= source.length();
}

bool Scanner::match(char ch){
    if(isAtEnd()) return false;
    if(source.at(current)!=ch) return false;
    current++;
    return true;
}

char Scanner::advance(){
    current++;
    return source.at(current-1);
}

void Scanner::addToken(TokenType type, LiteralType literal){
    std::string text = source.substr(start, current-start);
    tokens.push_back(Token(type,text,literal,line));
}

void Scanner::addToken(TokenType type){
    addToken(type,std::monostate{});
}

char Scanner::peek(){
    if(isAtEnd()) return '\0';
    return source.at(current);
}

void Scanner::string(){
    while(peek()!='"'&&!isAtEnd()){
        if(peek()=='\n') line++;
        advance();
    }
    if(isAtEnd()){
        Lox::error(line,"Unterminated string");
        return;
    }
    advance();
    std::string value = source.substr(start+1,current-start-2);
    addToken(TokenType::STRING,value);
}

bool Scanner::isDigit(char c){
    return (c>=0&&c<=9);
}

char Scanner::peekNext(){
    return current+1>= source.length()?'\0':source.at(current+1);
}

void Scanner::number(){
    while(isDigit(peek())) advance();
    if(peek()=='.'&&isDigit(peekNext())){
        advance();
        while(isDigit(peek())) advance();
    }
    addToken(TokenType::NUMBER,std::stod(source.substr(start,current-start)));
}

bool Scanner::isAlpha(char c){
    return (c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_';
}

bool Scanner::isAlphaNumeric(char c){
    return isDigit(c)||isAlpha(c);
}

void Scanner::identifier(){
    while(isAlphaNumeric(peek())) advance();

    std::string text = source.substr(start, current-start);
    auto it = keywords.find(text);
    if(it==keywords.end())
        addToken(TokenType::IDENTIFIER);
    else
        addToken(it->second);
}

void Scanner::scanToken(){
    char c = advance();
    switch(c){
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        case '!': addToken(match('=')?TokenType::BANG_EQUAL:TokenType::BANG); break;
        case '<': addToken(match('=')?TokenType::LESS_EQUAL:TokenType::LESS); break;
        case '>': addToken(match('=')?TokenType::GREATER_EQUAL:TokenType::GREATER); break;
        case '=': addToken(match('=')?TokenType::EQUAL_EQUAL:TokenType::EQUAL); break;
        case '/': if(match('/')){
            while(peek()!='\n'&&!isAtEnd()) advance();
        }else{
            addToken(TokenType::SLASH);
        }
        break;
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n': line++; break;
        case '"':string();break;

        default:
        if(isDigit(c)){
            number();
        }else if(isAlpha(c)){
            identifier();
        }else{
            Lox::error(line,"Unexpected Character");
        }
        break;
    }
}

