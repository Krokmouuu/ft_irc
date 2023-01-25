#include "ft_irc.hpp"

//? /join
//? /quit / leave
//? /w /msg
//? /ping / pong
//? /nick
//? /afk
//? /names
//? /back
//? /list
//? /help
//? /help [command]
//? /whois
//? /who

void beep_beep_boop(string input, int user, vector<Data> *data, vector<Channel> *chan)
{
    stringstream ss(input);  
    string word;
    while (ss >> word)
    {
        if (word == "quoi" || word == "QUOI" || word == "Quoi" || word == "quoi?" || word == "QUOI?" || word == "Quoi?" || word == "koi" || word == "Koi")
        {
            for (size_t i = 0; i < chan->size(); i++)
            {
                char *tmp = string_to_char("feurbot: feur @" + data->at(user - 4).getnickname() + " XD\n");
                for (size_t j = 0; j < chan->at(i).vgetusers().size(); j++)
                    send(chan->at(i).getuser(j).getfd(), tmp, 20 + data->at(user - 4).getnickname().size(), 0);
                free(tmp);
            }
        }
    }
}

int    command_input(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server)
{
    (void)server;
    beep_beep_boop(input, user, data, chan);
    if (input[0] != '/')
        return 1;
    vector<string> tmp = init_string();
    for(size_t i = 0; i < tmp.size(); i++)
    {
        if (input == "/join " + chan->at(i).getname() && i < chan->size())
        {
            {
                char *tmp = NULL;
                if (data->at(user - 4).getchannel() == chan->at(i).getname())
                {
                    tmp = string_to_char("You are already in < " + chan->at(i).getname() + " >" + " channel !\n");
                    send(data->at(user - 4).getfd(), tmp, 34 + chan->at(i).getname().size(), 0);
                    free(tmp);
                    return 0;
                }
                user_join_left(data, chan, user, chan->at(i).getname(), data->at(user - 4).getchannel());
                return 0;
            }
        }
    }
    return 0;
}