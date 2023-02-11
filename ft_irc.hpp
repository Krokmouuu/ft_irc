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
        string getwhitelist_users(int i) const { return this->whitelist_users[i]; };
        vector<string> vget_adminusers() const { return this->whitelist_users; };
        void remove_admin(int i) { this->whitelist_users.erase(this->whitelist_users.begin() + i);}

        void   setwhitelist_users(string user) { this->whitelist_users.push_back(user); };
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
        vector<string> whitelist_users;
        int     maxuser;
        int     current_user;
        int     socketServer;
};


//! Server
void            start_server(char **argv, IRC server);
void            beep_beep_boop(string input, int user, vector<Data> *data, vector<Channel> *chan);

//! Parsing
int             ft_parsing(char **argv);
int             parse_log(string input, IRC *server, Data *data, int user, vector<Data> *vdata);
int             parsing_nb_user(string nb, IRC server);
void            parse_input(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server);

//! Commands
void	        names_command(int user, vector<Data> *data);
void            join_command(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server);
void	        list_command(vector<Channel> *chan, int user);
void            msg_command(int user, vector<Data> *data, string input);
void            nick_command(int user, vector<Data> *data, string input);
void            away_command(int user, vector<Data> *data, string input);
void            op_command(int user, vector<Data> *data, string input, IRC *server, int op);
void            kick_command(int user, vector<Data> *data, string input, IRC *server, vector<Channel> *chan);
void            kill_command(int user, vector<Data> *data, string input, vector<Channel> *chan, IRC *server);
void            help_command(int user, string input);

//! Channels
void            default_channel(vector<Data> *data, vector<Channel> *chan, int user);
void            user_join_left(vector<Data> *data, vector<Channel> *chan, int user, string joinchannel , string leftchannel);
void            user_left(vector<Data> *data, vector<Channel> *chan, int user, string channel);

//! Utils
vector<string>  commands();
vector<string>	init_commands();
void	        typeWriter(string str);
vector<Channel> init_channels();
void            reset_client(Data *data);