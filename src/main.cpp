#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include "Lox.hpp"

int main(int argc, char * argv[]) {
    if (argc > 2) {
        std::cout << "Usage: jlox [script]";
        exit(1);
    } else if (argc == 2) {
        Lox::Lox::runFile(argv[1]);
    } else {
        Lox::Lox::runPrompt();
    }
}
