#include "ft_irc.hpp"

void reset_client(Data *data, int user, vector<Channel> *chan)
{
    data->setusername("");
    data->setnickname("");
    data->setlog(NEW_CLIENT);
    data->setfd(0);
    data->setchannel("The accueil");
    data->setconnected(DEFAULT);
    chan->at(0).removeuser(user - 4);
}

vector<Channel> init_channels()
{
    vector<Channel> channels;
    channels.push_back(Channel("The accueil")); //? 0
    channels.push_back(Channel("La taniere")); //? 1
    channels.push_back(Channel("Juraquantic Park")); //? 2
    channels.push_back(Channel("WAURK WAURK WAURK")); //? 3
    channels.push_back(Channel("chiez le")); //? 4
    channels.push_back(Channel("Sonic Enjoyers")); //? 5
    return channels;
}

void    parse_input(vector<Data> *data, vector<Channel> *chan, int user, string input)
{
    if (input == "/quit")
    {
        for (size_t i = 0; i < chan->at(0).vgetusers().size(); i++)
            send(chan->at(0).getuser(i).getfd(), string_to_char(data->at(user - 4).getnickname() + " left the channel.\n"), data->at(user - 4).getnickname().size() + 20, 0);
        reset_client(&data->at(user - 4), user, chan);
        close (user);
    }
    // print_name(&chan[user - 4], user);
}

void    default_channel(vector<Data> *data, vector<Channel> *chan, int user)
{
    if (data->at(user - 4).getconnected() == DEFAULT)
    {
        send(user, string_to_char("\nWelcome to < The accueil > channel !\n"), 39, 0);
        data->at(user - 4).setconnected(INSIDE_CHANNEL);
        chan->at(0).adduser(data->at(user - 4));
        for (size_t i = 0; i < chan->at(0).vgetusers().size(); i++)
            send(chan->at(0).getuser(i).getfd(), string_to_char("\n" + data->at(user - 4).getnickname() + " joined the channel.\n"), data->at(user - 4).getnickname().size() + 23, 0);
    }
}