#pragma once


//?
#define ADMIN 1
#define CLIENT 0

//? getlog()
#define NEW_CLIENT 0
#define LOGGED 1
#define LOGGED_MAYBE 2
#define LOG_COMPLETED 3

//? getconnected()
#define DEFAULT 2
#define JOIN_CHANNEL 0
#define INSIDE_CHANNEL 1

using namespace std;

class Data
{

    public :

        Data()
        {
            this->username = "";
            this->nickname = "";
            this->logged = NEW_CLIENT;
            this->fd = 0;
            this->channel = "The_accueil";
            this->connected = DEFAULT;
            this->number = 0;
            this->away = 0;
            this->admin = CLIENT;
        }
        Data(const Data &params)
        {
            *this = params;
        };
        Data &operator=(const Data &params)
        {
            if (this != &params)
            {
                this->username = params.username;
                this->nickname = params.nickname;
                this->logged = params.logged;
                this->fd = params.fd;
                this->channel = params.channel;
                this->connected = params.connected;
                this->number = params.number;
                this->away = params.away;
                this->admin = params.admin;
            }
            return *this;
        }
        ~Data() {};
    
    string  getusername() const { return this->username; };
    string  getnickname() const { return this->nickname; };
    int     getlog() const { return this->logged; };
    int     getfd() const { return this->fd; };
    string  getchannel() const { return this->channel; };
    int     getconnected() const { return this->connected; };
    int     getnumber() const { return this->number; };
    bool    getaway() const { return this->away; };
    int     getadmin() const { return this->admin; };
    string  getaway_message() const { return this->away_message; };

    void    setaway_message(string away_message) { this->away_message = away_message; };
    void    setaway(bool away) { this->away = away; };
    void    setusername(string username) { this->username = username; };
    void    setnickname(string nickname) { this->nickname = nickname; };
    void    setlog(int logged) { this->logged = logged; };
    void    setfd(int fd) { this->fd = fd; };
    void    setchannel(string channel) { this->channel = channel; };
    void    setconnected(int connected) { this->connected = connected; };
    void    setnumber(int number) { this->number = number; };
    void    setadmin(int admin) { this->admin = admin; };

    private :

    string  username;
    string  nickname;
    int     logged;
    int     fd;
    string  channel;
    int     connected;
    int     number;
    bool    away;
    string  away_message;

    int     admin;

};