#include "ft_irc.hpp"

//? /join Y
//? /quit / leave Y
//? /w /msg X
//? /ping / pong X
//? /nick X
//? /afk X 
//? /back X 
//? /names X
//? /list X
//? /help X 
//? /help [command] X
//? /whois X 
//? /who X
//? kick (leave channel) X
//? kill (leave server) X
//? op X

void beep_beep_boop(string input, int user, vector<Data> *data, vector<Channel> *chan)
{
    string tmp;
    stringstream ss(input);  
    string word;
    while (ss >> word)
        if (word == "quoi" || word == "QUOI" || word == "Quoi" || word == "quoi?" || word == "QUOI?" || word == "Quoi?" || word == "koi" || word == "Koi")
            for (size_t i = 0; i < chan->size(); i++)
            {
                tmp = "feurbot: feur @" + data->at(user - 4).getnickname() + " XD\n";
                for (size_t j = 0; j < chan->at(i).vgetusers().size(); j++)
                    send(chan->at(i).getuser(j).getfd(), tmp.c_str(), tmp.size(), 0);
            }
}

int    join_command(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server)
{
    (void)server;
    beep_beep_boop(input, user, data, chan);
    if (input[0] != '/')
        return 1;
    string tmp;
    for (size_t i = 0; i < chan->size(); i++)
    {
        if (input == "/join " + chan->at(i).getname())
        {
            {
                if (data->at(user - 4).getchannel() == chan->at(i).getname())
                {
                    tmp = "You are already in < " + chan->at(i).getname() + " >" + " channel !\n";
                    send(data->at(user - 4).getfd(), tmp.c_str(), tmp.size(), 0);
                    return 0;
                }
                user_join_left(data, chan, user, chan->at(i).getname(), data->at(user - 4).getchannel());
                return 0;
            }
        }
    }
    if (input == "/join" || input == "/join ")
    {
        tmp = "Please enter a channel name\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        return 0;
    }
    tmp = "Channel not found\n";
    send(user, tmp.c_str(), tmp.size(), 0);    
    return 0;
}