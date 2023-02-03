#include "ft_irc.hpp"

void user_join_left(vector<Data> *data, vector<Channel> *chan, int user, string joinchannel , string leftchannel)
{
    string tmp;
    size_t j = 0;
    while(chan->at(j).getname() != joinchannel && chan->size() > j)
        j++;
    size_t k = 0;
    while(chan->at(k).getname() != leftchannel && chan->size() > k)
        k++;
    for (size_t i = 0; i < chan->at(k).vgetusers().size(); i++)
    {
        tmp = data->at(user - 4).getnickname() + " has left the channel.\n";
        send(chan->at(k).getuser(i).getfd(), tmp.c_str(),tmp.size(), 0);
    }
    tmp = "Welcome to < " + joinchannel + " > channel !\n";
    send(user, tmp.c_str(), tmp.size(), 0);
    for (size_t i = 0; i < chan->at(j).vgetusers().size(); i++)
    {
        if (chan->at(j).getuser(i).getfd() != user)
        {
            tmp = data->at(user - 4).getnickname() + " has joined the channel.\n";
            send(chan->at(j).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
        }
    }
    data->at(user - 4).setchannel(joinchannel);
    for(size_t i = 0; i < chan->size(); i ++)
        if (chan->at(i).getname() == joinchannel)
        {
            data->at(user - 4).setchannel(joinchannel);
            chan->at(i).adduser(data->at(user - 4));
            break;
        }
    for (size_t i = 0; i < chan->at(k).vgetusers().size(); i++)
        if (chan->at(k).getuser(i).getfd() == user)
        {
            chan->at(k).removeuser(i);
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
        {
            string tmp = data->at(user - 4).getnickname() + " has left the channel.\n";
            send(chan->at(j).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
        }
    for(size_t i = 0; i < chan->size(); i++)
    {
        if (chan->at(i).getname() == channel)
            data->at(user - 4).setchannel(channel);
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

vector<string> init_cmd()
{
    vector<string> cmd;
    cmd.push_back("/join");
    cmd.push_back("/w");
    cmd.push_back("/msg");
    cmd.push_back("/ping");
    cmd.push_back("/pong");
    cmd.push_back("/nick");
    cmd.push_back("/afk");
    cmd.push_back("/back");
    cmd.push_back("/names");
    cmd.push_back("/list");
    cmd.push_back("/help");
    cmd.push_back("/who");
    cmd.push_back("/whois");
    cmd.push_back("/kick");
    cmd.push_back("/kill");
    cmd.push_back("/op");
    return cmd;
}

void    parse_input(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server)
{
    string tmp;
    if (input[0] == '/')
    {
        stringstream parse(input);
        string cmd;
        vector<string> list_cmd = init_cmd();
        while (parse >> cmd)
        {
            if (cmd == "/join")
                join_command(data, chan, user, input, server);
            else if (cmd == "/list")
                list_command(chan, user);
            else if (cmd == "/names")
                names_command(user, data);
            return ;
        }
    }
    else if (data->at(user - 4).getchannel() == "The accueil")
    {
        for (size_t i = 0; i < chan->at(0).vgetusers().size(); i++)
            if (chan->at(0).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
                send(chan->at(0).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
    else if (data->at(user - 4).getchannel() == "La taniere")
    {
        for (size_t i = 0; i < chan->at(1).vgetusers().size(); i++)
            if (chan->at(1).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
                send(chan->at(1).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
    else if (data->at(user - 4).getchannel() == "Juraquantic Park")
    {
        for (size_t i = 0; i < chan->at(2).vgetusers().size(); i++)
            if (chan->at(2).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
                send(chan->at(2).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
    else if (data->at(user - 4).getchannel() == "WAURK WAURK WAURK")
    {
        for (size_t i = 0; i < chan->at(3).vgetusers().size(); i++)
            if (chan->at(3).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
                send(chan->at(3).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
    else if (data->at(user - 4).getchannel() == "chiez le")
    {
        for (size_t i = 0; i < chan->at(4).vgetusers().size(); i++)
            if (chan->at(4).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
                send(chan->at(4).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
    else if (data->at(user - 4).getchannel() == "Sonic Enjoyers")
    {
        for (size_t i = 0; i < chan->at(5).vgetusers().size(); i++)
            if (chan->at(5).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
                send(chan->at(5).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
}

void    default_channel(vector<Data> *data, vector<Channel> *chan, int user)
{
    if (data->at(user - 4).getconnected() == DEFAULT)
    {
        string tmp = "\nWelcome to < The accueil > channel !\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        data->at(user - 4).setconnected(INSIDE_CHANNEL);
        data->at(user - 4).setnumber(user - 4);
        chan->at(0).adduser(data->at(user - 4));
        for (size_t i = 0; i < chan->at(0).vgetusers().size(); i++)
            if (chan->at(0).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + " has joined the channel.\n";
                send(chan->at(0).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
}