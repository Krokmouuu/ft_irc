#pragma once

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sstream>

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
        
        void   setsocketServer(int socketServer) { this->socketServer = socketServer; };
        void   setmaxuser(int maxuser) { this->maxuser = maxuser; };
    private :

        string serverport;
        string password;
        int    maxuser;
        
        int   socketServer;
};

void    start_server(char **argv, IRC server);
void	typeWriter(string str);
int     parsing_nb_user(string nb, IRC server);
int     ft_parsing(char **argv);