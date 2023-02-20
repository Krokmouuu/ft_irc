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
        tmp = "\033[38;5;208m" + data->at(user - 4).getnickname() + " has left the channel.\033[0m\n";
        send(chan->at(k).getuser(i).getfd(), tmp.c_str(),tmp.size(), 0);
    }
    tmp = "\033[38;5;120mWelcome to < " + joinchannel + " > channel !\033[0m\n";
    send(user, tmp.c_str(), tmp.size(), 0);
    for (size_t i = 0; i < chan->at(j).vgetusers().size(); i++)
    {
        if (chan->at(j).getuser(i).getfd() != user)
        {
            tmp = "\033[38;5;120m" + data->at(user - 4).getnickname() + " has joined the channel.\033[0m\n";
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
            string tmp = "\033[38;5;208m" + data->at(user - 4).getnickname() + " has left the channel.\033[0m\n";
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


void    parse_input(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server, Bot *bot)
{
    string tmp;
    stringstream parse(input);
    string cmd;
    parse >> cmd;
    if (input[0] == '!' && data->at(user - 4).getadmin() == ADMIN && input != "!joke" && input != "!help" && input != "!love" && input != "dofus" && cmd != "!gpt")
    {
        if (cmd == "!stop")
            stop_bot_command(bot, user);
        if (bot->getstop() == 1)
            return ;
        else if (cmd == "!nick")
            nick_bot_command(input, bot, user);
        else if (cmd == "!join")
            join_bot_command(input, bot, user, chan);
        else if (cmd == "!fun")
            fun_bot_command(input, bot, user);
        else if (cmd == "!key")
            adding_key_api( input, user, bot);
        return ;
    }
    else if (input[0] == '/')
    {
        if (cmd == "/join")
            join_command(data, chan, user, input, server);
        else if (cmd == "/list")
            list_command(chan, user);
        else if ( cmd == "/who")
            who_command(user, data);
        else if (cmd == "/w" || cmd == "/msg")
            msg_command(user, data, input);
        else if (cmd == "/nick")
            nick_command(user, data, input, server);
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
        else if (cmd == "/help")
            help_command(user, input);
        else if (cmd == "/whois") 
            whois_command(user, data, input);
        else
        {
            tmp = "\033[38;5;208mCommand not found\033[0m\n";
            send(user, tmp.c_str(), tmp.size(), 0);
        }
        return ;
    }
    if (data->at(user - 4).getaway() == TRUE)
    {
        data->at(user - 4).setaway(FALSE);
        tmp = "You are now back\n";
        send(user, tmp.c_str(), tmp.size(), 0);
    }
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
    if (data->at(user - 4).getIRSSI() == 1)
    {
        tmp = data->at(user - 4).getnickname() + ": " + input + "\n";
        send(user, tmp.c_str(), tmp.size(), 0);
    }
    beep_beep_boop(input, user, data, chan, bot);
}

void    default_channel(vector<Data> *data, vector<Channel> *chan, int user)
{
    if (data->at(user - 4).getconnected() == DEFAULT)
    {
        string tmp = "\n\033[38;5;120mWelcome to < The_accueil > channel !\033[0m\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        data->at(user - 4).setconnected(INSIDE_CHANNEL);
        data->at(user - 4).setnumber(user - 4);
        chan->at(0).adduser(data->at(user - 4));
        for (size_t i = 0; i < chan->at(0).vgetusers().size(); i++)
            if (chan->at(0).getuser(i).getfd() != user)
            {
                tmp = "\033[38;5;120m" + data->at(user - 4).getnickname() + " has joined the channel.\033[0m\n";
                send(chan->at(0).getuser(i).getfd(), tmp.c_str(), tmp.size(), 0);
            }
    }
}