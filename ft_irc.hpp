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
#include <sstream> 
#include "Data.hpp"
#include "Channel.hpp"

#define TRUE  1 
#define FALSE 0

using namespace std;

class IRC
{

    public :

        IRC(string server, string pass) : serverport(server), password(pass), current_user(0) {};
        IRC(const IRC &params)
        {
            this->serverport = params.serverport;
            this->password = params.password;
            this->maxuser = params.maxuser;
            this->current_user = params.current_user;
            this->socketServer = params.socketServer;
            return ;
        }
        IRC &operator=(const IRC &params)
        {
            if (this != &params)
            {
                this->serverport = params.serverport;
                this->password = params.password;
                this->maxuser = params.maxuser;
                this->current_user = params.current_user;
                this->socketServer = params.socketServer;
            }
            return *this;
        }
        ~IRC() {};
        
        string getserverport() const { return this->serverport; };
        string getpassword() const { return this->password; };
        int    getmaxuser() const { return this->maxuser; };
        int    getsocketServer() const { return this->socketServer; };
        int    getcurrent_user() const { return this->current_user; };
        string getadminpassword() const { return this->adminpassword; };

        void   setadminpassword(string adminpassword) { this->adminpassword = adminpassword; };
        void   setsocketServer(int socketServer) { this->socketServer = socketServer; };
        void   setmaxuser(int maxuser) { this->maxuser = maxuser; };
        void   setcurrent_user(int current_user) { this->current_user = current_user; };
        void   decrease_user() { this->current_user--; };
        void   increase_user() { this->current_user++; };

    private :

        string  serverport;
        string  password;
        string  adminpassword;
        int     maxuser;
        int     current_user;
        int     socketServer;
};


//! Server
void            start_server(char **argv, IRC server);

//! Parsing
int             ft_parsing(char **argv);
int             parse_log(string input, IRC server, Data *data, int user, vector<Data> *vdata);
int             parsing_nb_user(string nb, IRC server);
void            parse_input(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server);

//! Commands
void	        names_command(int user, vector<Data> *data);
void            join_command(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server);
void	        list_command(vector<Channel> *chan, int user);

//! Channels
void            default_channel(vector<Data> *data, vector<Channel> *chan, int user);
void            user_join_left(vector<Data> *data, vector<Channel> *chan, int user, string joinchannel , string leftchannel);
void            user_left(vector<Data> *data, vector<Channel> *chan, int user, string channel);

//! Utils
void	        typeWriter(string str);
vector<Channel> init_channels();
void            reset_client(Data *data, int user, vector<Channel> *chan, string channel);