#pragma once

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <vector>

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

    private :

        string serverport;
        string password;
};