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

void	list_command(vector<Channel> *chan, int user)
{
	string tmp;

	tmp = "\033[1;36m    Channels: \033[0m\n";
	send(user, tmp.c_str(), tmp.size(), 0);
	for(size_t n = 0; n <= chan->size(); n++)
	{
		tmp = "• " + chan->at(n).getname() + "\n";
		send(user, tmp.c_str(), tmp.size(), 0);
	}

}

void	names_command(int user, vector<Data> *data)
{
	string tmp;

	tmp = "\033[1;36m    Users: \033[0m\n";
	send(user, tmp.c_str(), tmp.size(), 0);
	for (size_t n = 0; n <= data->size(); n++)
	{
		if (data->at(n).getnickname().length() > 1)
		{
			tmp = "• " + data->at(n).getnickname() + "\n";
			send(user, tmp.c_str(), tmp.size(), 0);
		}
	}
}

void    parse_input(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server)
{
    (void)server;
    string tmp;
	if (input == "/list")
		list_command(chan, user);
	if (input == "/names" || input == "/who")
		names_command(user, data);
    if (join_command(data, chan, user, input, server) == 0)
        return ;
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