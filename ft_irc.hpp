#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <vector>
#include "Data.hpp"

#define TRUE  1 
#define FALSE 0

using namespace std;

class IRC
{

    public :

        IRC(string server, string pass) : serverport(server), password(pass) {};
        IRC(const IRC &params)
        {
            this->serverport = params.serverport;
            this->password = params.password;
            return ;
        }
        IRC &operator=(const IRC &params)
        {
            if (this != &params)
            {
                this->serverport = params.serverport;
                this->password = params.password;
            }
            return *this;
        }
        ~IRC() {};
        
        string getserverport() const { return this->serverport; };
        string getpassword() const { return this->password; };
        int    getmaxuser() const { return this->maxuser; };
        int    getsocketServer() const { return this->socketServer; };
        int    getcurrent_user() const { return this->current_user; };


        void   setsocketServer(int socketServer) { this->socketServer = socketServer; };
        void   setmaxuser(int maxuser) { this->maxuser = maxuser; };
        void   setcurrent_user(int current_user) { this->current_user = current_user; };

        void    decrease_user() { this->current_user--; };
        void    increase_user() { this->current_user++; };

    private :

        string serverport;
        string password;
        int    maxuser;
        int    current_user;
        
        int   socketServer;
};

void    start_server(char **argv, IRC server);
void	typeWriter(string str);
int     parsing_nb_user(string nb, IRC server);
int     ft_parsing(char **argv);
int     parse_input(string input, IRC server, Data *data, int user);
