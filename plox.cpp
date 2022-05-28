#include <iostream>
#include <cstring>
#include <fstream>
#include <sysexits.h>

int main(int argc, char * argv[]) {
    if (std::strlen(argv[0]) > 1) {
        std::cout << "Usage: jlox [script]";
        EX_DATAERR;
    } else if (std::strlen(argv[0]) == 1) {
        // maybe make a runFile(argv[0]) somewhere else?
        std::ofstream file (argv[0]);
    } else {
        // runPrompt();
    }
}
