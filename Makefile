###############################################################
# Variables
CPP          = clang++
CPP_FLAGS    = -g -Werror -W -Wunused -Wuninitialized -Wshadow -std=c++11

###############################################################
# Compile plox 
#
plox: plox.cpp
	$(CPP) -c $(OPTIONS) plox.cpp -o plox.o

plox.o: plox.cpp
	$(CPP) -c $(OPTIONS) plox.cpp -o plox.o

