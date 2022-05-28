#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>

#define LOX_VERSION "0.0.1"

typedef unsigned char BYTE;

void run(const std::string &source) {
    // run scanner
    // run parser
    // parse statements
    // interpret statements
}

void runFile(const char* filename) {
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
    // make some file for failures and error checking
}

// allows you to add args after running
void runPrompt() {
    std::printf("Lox Version >> %s \n", LOX_VERSION);

    std::string code;
    while(true) {
        std::cout << "> ";
        if (std::getline(std::cin, code)) {
            run(code);
            // set errors to false here
        } else {
            std::cout << std::endl;
            break;
        }
    }
}

int main(int argc, char * argv[]) {
    if (std::strlen(argv[0]) > 1) {

        std::cout << "Usage: jlox [script]";
    } else if (std::strlen(argv[0]) == 1) {
        // maybe make a runFile(argv[0]) somewhere else?
        std::ofstream file (argv[0]);
    } else {
        // runPrompt();
    }
}
