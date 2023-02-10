#include "ft_irc.hpp"

vector<Channel> init_channels()
{
    vector<Channel> channels;
    channels.push_back(Channel("The_accueil")); //? 0
    channels.push_back(Channel("La_taniere")); //? 1
    channels.push_back(Channel("Juraquantic_Park")); //? 2
    channels.push_back(Channel("Le_Spa")); //? 3
    channels.push_back(Channel("chiez_le")); //? 4
    channels.push_back(Channel("Sonic_Enjoyers")); //? 5
    return channels;
}

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


void    parse_input(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server)
{
    string tmp;
    if (input[0] == '/')
    {
        stringstream parse(input);
        string cmd;
        parse >> cmd;
        if (cmd == "/join")
            join_command(data, chan, user, input, server);
        else if (cmd == "/list")
            list_command(chan, user);
        else if (cmd == "/names")
            names_command(user, data);
        else if (cmd == "/w" || cmd == "/msg")
            msg_command(user, data, input);
        else if (cmd == "/nick")
            nick_command(user, data, input);
        else if (cmd == "/away")
            away_command(user, data, input);
        else if (cmd == "/op")
            op_command(user, data, input, server, ADMIN);
        else if (cmd == "/deop")
            op_command(user, data, input, server, CLIENT);
        else if (cmd == "/kick")
            kick_command(user, data, input, server, chan);
        else if (cmd == "/kill")
            kill_command(user, data, input, chan, server);
        return ;
    }
    if (data->at(user - 4).getaway() == TRUE)
    {
        data->at(user - 4).setaway(FALSE);
        tmp = "You are now back\n";
        send(user, tmp.c_str(), tmp.size(), 0);
    }
    beep_beep_boop(input, user, data, chan);
    if (data->at(user - 4).getchannel() == "The_accueil")
    {
        for (size_t i = 0; i < chan->at(0).vgetusers().size(); i++)
            if (chan->at(0).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
                send(chan->at(0).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
    else if (data->at(user - 4).getchannel() == "La_taniere")
    {
        for (size_t i = 0; i < chan->at(1).vgetusers().size(); i++)
            if (chan->at(1).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
                send(chan->at(1).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
    else if (data->at(user - 4).getchannel() == "Juraquantic_Park")
    {
        for (size_t i = 0; i < chan->at(2).vgetusers().size(); i++)
            if (chan->at(2).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
                send(chan->at(2).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
    else if (data->at(user - 4).getchannel() == "Le_Spa")
    {
        for (size_t i = 0; i < chan->at(3).vgetusers().size(); i++)
            if (chan->at(3).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
                send(chan->at(3).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
    else if (data->at(user - 4).getchannel() == "chiez_le")
    {
        for (size_t i = 0; i < chan->at(4).vgetusers().size(); i++)
            if (chan->at(4).getuser(i).getfd() != user)
            {
                tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
                send(chan->at(4).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
    else if (data->at(user - 4).getchannel() == "Sonic_Enjoyers")
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
        string tmp = "\nWelcome to < The_accueil > channel !\n";
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