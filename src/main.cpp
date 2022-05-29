#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include "Lox.hpp"

int main(int argc, char * argv[]) {
    if (std::strlen(argv[0]) > 1) {
        std::cout << "Usage: jlox [script]";
    } else if (std::strlen(argv[0]) == 1) {
        Lox::Lox::runFile(argv[0]);
        std::ofstream file (argv[0]);
    } else {
        Lox::Lox::runPrompt();
    }
}
