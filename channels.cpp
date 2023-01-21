#include "ft_irc.hpp"

vector<Channel> init_channels()
{
    vector<Channel> channels;
    channels.push_back(Channel("The accueil"));
    channels.push_back(Channel("La taniere"));
    channels.push_back(Channel("Juraquantic Park"));
    channels.push_back(Channel("WAURK WAURK WAURK"));
    channels.push_back(Channel("chiez le"));
    channels.push_back(Channel("Sonic Enjoyers"));
    return channels;
}

void    default_channel(vector<Data> *data, vector<Channel> chan, string input, int user)
{
    (void)user;
    (void)data;
    (void)input;
    (void)user;
    (void)chan;
}