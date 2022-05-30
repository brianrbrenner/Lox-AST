#ifndef LOX
#define LOX

#include <string>

#define PLOX_VERSION "0.0.1"

namespace Lox {
    class Token;
    class RuntimeError;

    class Lox {
    public:
        Lox() {};
        static void Error(int line, const std::string&);
        static void Error(Token token, const std::string&);
        static void ReportRuntimeError(const RuntimeError&);
        static void runPrompt();
        static void Report(int, const std::string&, const std::string&);
        static void runFile(const char*);
        static void run(const std::string&);

        static bool HadError;
        static bool HadRuntimeError;
    private:
};

}

#endif
