#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <fstream>

int main()
{
pid_t p_pid, c_pid;
int status;
int success = 0;    //retval for execvp
std::fstream fOut;
fOut.open("pass", std::ios::out | std::ios::trunc);
fOut << success;
fOut.close();
char* com[64];
for(int i = 0; i < 63; i++)
com[i] = NULL;
std::string coms[10][10];
std::string input;
char tokens[10][10];

std::string user;
char host[20];

user = getlogin();
int tmp = gethostname(host, 255);

if (tmp < 0)
    std::cout << "error getting host name" << std::endl;


for(size_t i = 0; i < 10; i++)
for(size_t j = 0; j < 10; j++)
tokens[i][j]='\0';

do
{

    std::cout << user << "@" << host << "$";
    std::getline(std::cin, input);

    //parse string

    size_t prev = 0;
    size_t next = 0;
    size_t count = 0;
    size_t count2[10] = {0};

    //seperate ; commands which are always executed
    while (next != std::string::npos)
    {
        next = input.find(";", prev); 
        if(next == std::string::npos)
            break;
        coms[count][0] = input.substr(prev, next-prev);
        count++;
        prev = next + 1;
    }
    coms[count][0] = input.substr(prev, input.length() - prev);

    //strip comments
    for(size_t j = 0; j <= count; j++)
    {
        next = coms[j][0].find("#", 0);
        if(next != std::string::npos)
            coms[j][0] = coms[j][0].substr(0, next);
    }

    //parse individual commands and save execution conditions
    size_t next2;
    for(size_t j = 0; j <= count; j++)
    {
        next = prev = next2 = 0;
        size_t i =1;
        while(next != std::string::npos && next2 != std::string::npos)
        {
            next = coms[j][0].find("&&", prev);
            next2 = coms[j][0].find("||", prev);

            if(next == std::string::npos && next2 == std::string::npos)
                break;

            if(next > next2)
            {
                coms[j][i] = coms[j][0].substr(prev, next2-prev);
                prev = next2+2;
                tokens[j][i-1]='|';
            }
            else
            {
                coms[j][i] = coms[j][0].substr(prev, next-prev);
                prev = next+2;
                tokens[j][i-1]='&';
                //strcpy(tokens[j][i-1], '&');
            }
            i++;
            count2[j]++;
        }
        coms[j][i] = coms[j][0].substr(prev, coms[j][0].length() - prev);

    }


    //iterate through each command
    for(size_t j = 0; j <= count; j++)
    {

        
        for(size_t i = 1; i <= count2[j] + 1; i++)
        {
            char* tmp = new char[input.length() + 1];
            std::copy(coms[j][i].begin(), coms[j][i].end(), tmp);
            tmp[coms[j][i].length() + 1] = '\0';    

            com[0] = strtok(tmp, " ");
            size_t counter = 0;
            do
            {
                counter++;
                com[counter] = strtok(NULL, " ");
            } while (com[counter] != NULL);

            if(strcmp(com[0], "exit") == 0)
                return 0;

            c_pid = fork();
            if (c_pid < 0)
            {
                perror("fork failed");
                exit(1);
            }

            if (c_pid > 0)
            {
                if((p_pid = wait(&status)) < 0)
                {
                    perror("wait");
                    exit(1);
                }

            }

            else if (c_pid == 0)
            {
                std::fstream pass;
                pass.open("pass", std::ios::in);
                pass >> success;
                pass.close();

                if(success == -1 && i > 1 && tokens[j][i-2] == '|')
                {
                    success = 0;
                    pass.open("pass", std::ios::out | std::ios::trunc);
                    pass << success;
                    pass.close();
                    execvp(com[0], com);
                    success = -1;
                    pass.open("pass", std::ios::out | std::ios::trunc);
                    pass << success;
                    pass.close();
                    perror("execvp failed");
                    std::cout << std::endl;
                }
                else if(success == 0 && i > 1 && tokens[j][i-2] == '&')
                {
                    success = 0;
                    pass.open("pass", std::ios::out | std::ios::trunc);
                    pass << success;
                    pass.close();
                    execvp(com[0], com);
                    success = -1;
                    pass.open("pass", std::ios::out | std::ios::trunc);
                    pass << success;
                    pass.close();
                    perror("execvp failed");
                    std::cout << std::endl;
                }
                else if(i == 1)
                {
                    success = 0;
                    pass.open("pass", std::ios::out | std::ios::trunc);
                    pass << success;
                    pass.close();
                    execvp(com[0], com);
                    success = -1;
                    pass.open("pass", std::ios::out | std::ios::trunc);
                    pass << success;
                    pass.close();
                    perror("execvp failed");
                    std::cout << std::endl;
                }
                return 0;
            }

        delete tmp;
        }
    }


}
while (strcmp(com[0], "exit") != 0);


return 0;
}
