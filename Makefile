###############################################################
# Variables
CPP          = clang++
CPP_FLAGS    = -g -Werror -W -Wunused -Wuninitialized -Wshadow -std=c++11

###############################################################
# Compile plox 
#
Lox.o: Lox.hpp Lox.cpp
	$(CPP) -c $(CPP_FLAGS) Lox.cpp
Lox: Lox.hpp Lox.cpp
	$(CPP) -c $(CPP_FLAGS) Lox.cpp -o Lox.o


