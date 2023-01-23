#include "ft_irc.hpp"

void user_join(vector<Data> *data, vector<Channel> *chan, int user, string channel)
{
    size_t j = 0;
    while(chan->at(j).getname() != channel && chan->size() > j)
        j++;
    for (size_t i = 0; i < chan->at(j).vgetusers().size(); i++)
        if (chan->at(j).getuser(i).getfd() != user)
            send(chan->at(j).getuser(i).getfd(), string_to_char(data->at(user - 4).getnickname() + " has joined the channel.\n"), data->at(user - 4).getnickname().size() + 25, 0);
    data->at(user - 4).setchannel(channel);
    for(size_t i = 0; i < chan->size(); i ++)
    {
        if (chan->at(i).getname() == channel)
            chan->at(i).adduser(data->at(user - 4));
            break;
    }
}

void user_left(vector<Data> *data, vector<Channel> *chan, int user, string channel)
{
    size_t j = 0;
    while(chan->at(j).getname() != channel && chan->size() > j)
        j++;
    for (size_t i = 0; i < chan->at(j).vgetusers().size(); i++)
        if (chan->at(j).getuser(i).getfd() != user)
            send(chan->at(j).getuser(i).getfd(), string_to_char(data->at(user - 4).getnickname() + " has left the channel.\n"), data->at(user - 4).getnickname().size() + 24, 0);
    data->at(user - 4).setchannel(channel);
    for(size_t i = 0; i < chan->size(); i++)
    {
        if (chan->at(i).getname() == channel)
            for(size_t j = 0; j < chan->at(i).vgetusers().size(); j++)
                if (chan->at(i).getuser(j).getfd() == user)
                    chan->at(i).removeuser(j);
            break;
    }
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

void    parse_input(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server)
{
    (void)server;
    
    if (command_input(data, chan, user, input, server) == 0)
    {
        // print_name(data, chan, user, FALSE);
        return ;
    }
    else if (data->at(user - 4).getchannel() == "The accueil")
    {
        for (size_t i = 0; i < chan->at(0).vgetusers().size(); i++)
            if (chan->at(0).getuser(i).getfd() != user)
                send(chan->at(0).getuser(i).getfd(), string_to_char(data->at(user - 4).getnickname() + ": " + input + "\n"), data->at(user - 4).getnickname().size() + input.size() + 3, 0);
    }
    else if (data->at(user - 4).getchannel() == "La taniere")
    {
        for (size_t i = 0; i < chan->at(1).vgetusers().size(); i++)
            if (chan->at(1).getuser(i).getfd() != user)
                send(chan->at(1).getuser(i).getfd(), string_to_char("\n" + data->at(user - 4).getnickname() + ": " + input + "\n"), data->at(user - 4).getnickname().size() + input.size() + 4, 0);
    }
    else if (data->at(user - 4).getchannel() == "Juraquantic Park")
    {
        for (size_t i = 0; i < chan->at(3).vgetusers().size(); i++)
            if (chan->at(3).getuser(i).getfd() != user)
                send(chan->at(3).getuser(i).getfd(), string_to_char("\n" + data->at(user - 4).getnickname() + ": " + input + "\n"), data->at(user - 4).getnickname().size() + input.size() + 4, 0);
    }
    else if (data->at(user - 4).getchannel() == "WAURK WAURK WAURK")
    {
        for (size_t i = 0; i < chan->at(3).vgetusers().size(); i++)
            if (chan->at(3).getuser(i).getfd() != user)
                send(chan->at(3).getuser(i).getfd(), string_to_char("\n" + data->at(user - 4).getnickname() + ": " + input + "\n"), data->at(user - 4).getnickname().size() + input.size() + 4, 0);
    }
    else if (data->at(user - 4).getchannel() == "chiez le")
    {
        for (size_t i = 0; i < chan->at(4).vgetusers().size(); i++)
            if (chan->at(4).getuser(i).getfd() != user)
                send(chan->at(4).getuser(i).getfd(), string_to_char("\n" + data->at(user - 4).getnickname() + ": " + input + "\n"), data->at(user - 4).getnickname().size() + input.size() + 4, 0);
    }
    else if (data->at(user - 4).getchannel() == "Sonic Enjoyers")
    {
        for (size_t i = 0; i < chan->at(5).vgetusers().size(); i++)
            if (chan->at(5).getuser(i).getfd() != user)
                send(chan->at(5).getuser(i).getfd(), string_to_char("\n" + data->at(user - 4).getnickname() + ": " + input + "\n"), data->at(user - 4).getnickname().size() + input.size() + 4, 0);
    }
}

void    default_channel(vector<Data> *data, vector<Channel> *chan, int user)
{
    if (data->at(user - 4).getconnected() == DEFAULT)
    {
        send(user, string_to_char("\nWelcome to < The accueil > channel !\n"), 39, 0);
        data->at(user - 4).setconnected(INSIDE_CHANNEL);
        data->at(user - 4).setnumber(user - 4);
        user_join(data, chan, user, "The accueil");
    }
}