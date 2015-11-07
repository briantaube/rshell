all: rshell

rshell: src/rshell.cpp
	g++ -g -Wall -Werror -ansi -pedantic src/rshell.cpp -o rshell
