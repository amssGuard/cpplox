#pragma once
#include<string>

class Lox{
    private:
    static bool hadError;
    public:
    void runFile(const std::string& path);
    void runPrompt();
    void run(const std::string& source);
    static void error(int line,std::string message);
    static void report(int line,std::string where,std::string message);
};