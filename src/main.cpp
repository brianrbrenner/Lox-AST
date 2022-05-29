#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include "../include/lox/Lox.hpp"

int main(int argc, char * argv[]) {
    if (std::strlen(argv[0]) > 1) {
        std::cout << "Usage: jlox [script]";
    } else if (std::strlen(argv[0]) == 1) {
        // maybe make a runFile(argv[0]) somewhere else?
        std::ofstream file (argv[0]);
    } else {
        Lox::Lox::runPrompt();
    }
}
