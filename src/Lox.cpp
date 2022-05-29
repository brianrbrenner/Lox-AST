#include "Lox.hpp"
#include <iostream>
#include <fstream>

void Lox::Lox::Report(int line, const std::string &location, const std::string &message) {
    std::cout << "[line " << "] Error" << location << ": " << message;
    HadError = true;
};

void Lox::Lox::Error(int line, const std::string &message) {
    Report(line, "", message);
}

void Lox::Lox::run(const std::string &source) {
    // run scanner
    // run parser
    // parse statements
    // interpret statements
}

void Lox::Lox::runFile(const char* filename) {
    std::ifstream file{filename};
    if (!file.good()) {
       std::printf("Could not open file %s, ", filename);
       exit(1);
    }

    std::string line;
    std::string source;
    while (std::getline(file, line)) {
        source += line + "\n";
    }

    run(source);
    if (HadError)
        exit(1);
}

void Lox::Lox::runPrompt() {
    std::printf("Lox Version >> %s \n", LOX_VERSION);

    std::string code;
    while(true) {
        std::cout << "> ";
        if (std::getline(std::cin, code)) {
            run(code);
            HadError = false;
        } else {
            std::cout << std::endl;
            break;
        }
    }
}
