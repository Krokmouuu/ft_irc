#pragma once

using namespace std;

class Data
{

    public :

        Data()
        {
            this->username = "";
            this->nickname = "";
            this->logged = 0;
            this->fd = 0;
            this->channel = "The accueil";
            this->connected = 0;
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

    void    setusername(string username) { this->username = username; };
    void    setnickname(string nickname) { this->nickname = nickname; };
    void    setlog(int logged) { this->logged = logged; };
    void    setfd(int fd) { this->fd = fd; };
    void    setchannel(string channel) { this->channel = channel; };
    void    setconnected(int connected) { this->connected = connected; };

    private :

    string  username;
    string  nickname;
    int     logged;
    int     fd;
    string  channel;
    int     connected;
};