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

int    command_input(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server)
{
    (void)data;
    (void)server;
    (void)user;
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
                user_left(data, chan, user, data->at(user - 4).getchannel());
                user_join(data, chan, user, chan->at(i).getname());
                tmp = string_to_char("Welcome to < " + chan->at(i).getname() + " > channel !\n");
                send(user, tmp, 28 + chan->at(i).getname().size(), 0);
                free(tmp);
                return 0;
            }
        }
    }
    return 0;
}