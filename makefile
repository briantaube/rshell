all: directory rshell

directory:
	mkdir -p bin

rshell: src/rshell.cpp
	g++ -g -Wall -Wcomment -Werror -ansi -pedantic src/rshell.cpp -o bin/rshell
