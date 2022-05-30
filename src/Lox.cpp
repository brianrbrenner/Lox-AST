#include "Lox.hpp"
#include "Scanner.hpp"

#include <iostream>
#include <fstream>

namespace Lox {
bool Lox::HadError = false;
bool Lox::HadRuntimeError = false;

void Lox::Report(int line, const std::string &location, const std::string &message) {
    std::cout << "[line " << "] Error" << location << ": " << message;
    HadError = true;
};

void Lox::Error(int line, const std::string &message) {
    Report(line, "", message);
}

void Lox::run(const std::string &source) {
    // run scanner
    Scanner scanner{source};
    scanner.scanTokens();
    // run parser
    // parse statements
    // interpret statements
}

void Lox::runFile(const char* filename) {
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
    if (HadError) {
        exit(1);
    }
    if (HadRuntimeError) {
        exit(2);
    }
}

void Lox::runPrompt() {
    std::printf("Lox Version >> %s \n", PLOX_VERSION);

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
}
