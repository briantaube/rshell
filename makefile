all: rshell

rshell: src/rshell.cpp
	g++ -g -Wall -Werror -ansi -pedantic rshell.cpp -o
