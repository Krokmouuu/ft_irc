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
        for (size_t j = 0; j < chan->size(); j++)
        {
            if (input == "/join " + chan->at(j).getname())
            {
                // send(user, string_to_char("Welcome to < " + chan->at(j).getname() + " >" + " channel !\n"), 29 + chan->at(j).getname().size(), 0);
                user_join(data, chan, user, chan->at(j).getname());
                user_left(data, chan, user, data->at(user - 4).getchannel());
               return 0;
            }
        }
    }
    return 0;
}