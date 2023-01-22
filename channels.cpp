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

void    parse_input(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server)
{
    (void)server;
    if (input == "")
        return ;
    if (data->at(user - 4).getchannel() == "The accueil")
    {
        for (size_t i = 0; i < chan->at(0).vgetusers().size(); i++)
            if (chan->at(0).getuser(i).getfd() != user)
                send(chan->at(0).getuser(i).getfd(), string_to_char("\n" + data->at(user - 4).getnickname() + ": " + input + "\n"), data->at(user - 4).getnickname().size() + input.size() + 4, 0);
    }
    print_name(data, chan, user, TRUE);
    // if (data->at(user - 4).getchannel() == "La taniere")
    // if (data->at(user - 4).getchannel() == "Juraquantic Park")
    // if (data->at(user - 4).getchannel() == "WAURK WAURK WAURK")
    // if (data->at(user - 4).getchannel() == "chiez le")
    // if (data->at(user - 4).getchannel() == "Sonic Enjoyers")
}

void    default_channel(vector<Data> *data, vector<Channel> *chan, int user)
{
    if (data->at(user - 4).getconnected() == DEFAULT)
    {
        send(user, string_to_char("\nWelcome to < The accueil > channel !\n"), 39, 0);
        chan->at(0).adduser(data->at(user - 4));
        data->at(user - 4).setconnected(INSIDE_CHANNEL);
        for (size_t i = 0; i < chan->at(0).vgetusers().size(); i++)
            send(chan->at(0).getuser(i).getfd(), string_to_char("\n" + data->at(user - 4).getnickname() + " joined the channel.\n"), data->at(user - 4).getnickname().size() + 23, 0);
    }
}