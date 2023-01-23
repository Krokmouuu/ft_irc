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
    if (input[0] != '/')
        return 1;
    vector<string> tmp = init_string();
    for(size_t i = 0; i < tmp.size(); i++)
    {
        for (size_t j = 0; j < chan->size(); j++)
        {
            if (input == "/join " + chan->at(j).getname())
            {
               user_join(data, chan, user, chan->at(j).getname());
               user_left(data, chan, user, data->at(user - 4).getchannel());
            }
            else if (input == "/quit " + chan->at(j).getname() || input == "/leave " + chan->at(j).getname())
            {
                user_left(data, chan, user, chan->at(j).getname());
                server->setcurrent_user(server->getcurrent_user() - 1);
                chan->at(j).removeuser(user - 4);
            }       
        }
    }
    return 0;
}