#include"lox.h"
#include"scanner.h"
#include<iostream>
#include<sstream>
#include<fstream>

bool Lox::hadError = false;

void Lox::runFile(const std::string& path){
    std::ifstream file(path);
    if(!file.is_open()){
        std::cerr<<"Couldn't open file "<<path<<std::endl;
        return;
    }
    std::stringstream buffer;
    buffer<<file.rdbuf();
    run(buffer.str());
    if(hadError) exit(64);
}

void Lox::runPrompt(){
    std::string line;
    while(true){
        std::cout<<"cpplox > ";
        if(!std::getline(std::cin,line)){
            break;
        }
        run(line);
        hadError=false;
    }
}

void Lox::run(const std::string& source){
    Scanner scanner(source);
    std::cout<<source<<std::endl;
}

void Lox::error(int line,std::string message){
    report(line,"",message);
}

void Lox::report(int line,std::string where,std::string message){
    std::cerr<<"[line"+std::to_string(line)+"] Error "+where+" : "+message;
}