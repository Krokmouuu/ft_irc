#include "ft_irc.hpp"

class Bot
{
    public :

    Bot()
    {
        this->name = "BruteForce[BOT]";
        this->channel = "The_accueil";
        this->fun = 0;
        this->stop = 0;
    }
    Bot(const Bot &params)
    {
        this->name = params.name;
        this->channel = params.channel;
        this->fun = params.fun;
    }
    Bot &operator=(const Bot &params)
    {
        if (this != &params)
        {
            this->name = params.name;
            this->channel = params.channel;
            this->fun = params.fun;
        }
        return *this;
    }
    ~Bot() {};

    string getname() const { return this->name; };
    string getchannel() const { return this->channel; };
    int    getfun() const { return this->fun; };
    int    getstop() const { return this->stop; };

    void   setname(string name) { this->name = name; };
    void   setchannel(string channel) { this->channel = channel; };
    void   setfun(int fun) { this->fun = fun; };
    void    setstop(int stop) { this->stop = stop; };

    private :

    string name;
    string channel;
    int    fun;

    int stop;
};