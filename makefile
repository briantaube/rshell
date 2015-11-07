all: rshell.cpp
	g++ -g -Wall -Werror -ansi -pedantic rshell.cpp -o rshell

rshell: rshell.cpp
	g++ -g -Wall -Werror -ansi -pedantic rshell.cpp -o rshell
