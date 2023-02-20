#include "ft_irc.hpp"

class Bot
{
    public :

    Bot()
    {
        this->name = "BruteForce[BOT]";
        this->channel = "The_accueil";
		this->key = "";
        this->fun = 0;
        this->stop = 0;
        this->keyadded = 0;
    }
    Bot(const Bot &params)
    {
        this->name = params.name;
        this->channel = params.channel;
        this->fun = params.fun;
        this->key = params.key;
        this->keyadded = params.keyadded;
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

    string 	getname() const { return this->name; };
    string 	getchannel() const { return this->channel; };
    string	getkey() const { return this->key; };
    int    	getfun() const { return this->fun; };
	int		getnew_connection() const { return this->new_connection; };
    int    	getstop() const { return this->stop; };
    int    	getkeyadded() const { return this->keyadded; };

    void    	setkeyadded(int nb) { this->keyadded = nb; };
    void   setname(string name) { this->name = name; };
    void   setkey(string newkey) {
	string tmp = "Authorization: Bearer " + newkey;
	this->key = tmp; 
	setkeyadded(1);};
    void   setchannel(string str) { this->channel = str; };
    void   setfun(int fun) { this->fun = fun; };
    void   setnew_connection(int nb) { this->new_connection = nb; };
    void   setstop(int stop) { this->stop = stop; };

    private :

    string	name;
	string	key;
	int		keyadded;
    string	channel;
    int		fun;
	int		new_connection;

    int stop;
};