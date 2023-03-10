#include "ft_irc.hpp"

void    join_command(vector<Data> *data, vector<Channel> *chan, int user, string input, IRC *server)
{
    (void)server;
    stringstream coucou(input);
    string tmp2;
    string tmp;
    int i = 0;
    while (coucou >> tmp2)
        i++;
    if (i == 1)
    {
        tmp = "\033[38;5;104mPlease enter a channel name\033[0m\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        return ;
    }
    for (size_t i = 0; i < chan->size(); i++)
    {
        if (input == "/join " + chan->at(i).getname())
        {
            {
                if (data->at(user - 4).getchannel() == chan->at(i).getname())
                {
                    tmp = "\033[38;5;104mYou are already in < " + chan->at(i).getname() + " >" + " channel !\033[0m\n";
                    send(data->at(user - 4).getfd(), tmp.c_str(), tmp.size(), 0);
                    return ;
                }
                user_join_left(data, chan, user, chan->at(i).getname(), data->at(user - 4).getchannel());
                return ;
            }
        }
    }
    tmp = "\033[38;5;104mChannel not found\033[0m\n";
    send(user, tmp.c_str(), tmp.size(), 0);    
    return ;
}

void	list_command(vector<Channel> *chan, int user)
{
	string tmp;

	tmp = "\033[1;36m    Channels: \033[0m\n";
	send(user, tmp.c_str(), tmp.size(), 0);
	for(size_t n = 0; n < chan->size(); n++)
	{
		tmp = "• " + chan->at(n).getname() + "\n";
		send(user, tmp.c_str(), tmp.size(), 0);
	}
}

void	who_command(int user, vector<Data> *data)
{
	string tmp;

	tmp = "\033[1;36m    Users: \033[0m\n";
	send(user, tmp.c_str(), tmp.size(), 0);
	for (size_t n = 0; n < data->size(); n++)
	{
		if (data->at(n).getnickname().length() > 1)
		{
			tmp = "• " + data->at(n).getnickname() + "\n";
			send(user, tmp.c_str(), tmp.size(), 0);
		}
	}
}

void	names_command(int user, vector<Channel> *chan, vector<Data> *data)
{
	string tmp;

	tmp = "\033[1;36m    Users in your channel: \033[0m\n";
	send(user, tmp.c_str(), tmp.size(), 0);
	for(size_t n = 0; n < chan->size(); n++)
	{
		if (chan->at(n).getname() == data->at(user - 4).getchannel())
		{
			for (size_t i = 0; i < chan->at(n).vgetusers().size(); i++)
			{
				tmp = "• " + chan->at(n).getuser(i).getnickname() + "\n";
				send(user, tmp.c_str(), tmp.size(), 0);
			}
		}
	}
}

void away_command(int user, vector<Data> *data, string input)
{
    string tmp;
    stringstream ss(input);
    string word;
    string tmp2;
    ss >> tmp2;
    if (input[tmp2.length() + 1] == ' ')
    {
        tmp = "\033[38;5;104mBad input\033[0m\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        return ;
    }
    if (data->at(user - 4).getaway() == TRUE)
    {
        data->at(user - 4).setaway(FALSE);
        tmp = "\033[38;5;104mYou are now back\033[0m\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        return ;
    }
    data->at(user - 4).setaway(TRUE);
	word += &input[tmp2.length() + 1];
	if (word.length() <= 1)
    {
		word = "";
        tmp = "\033[38;5;104mYou are now afk\033[0m";
		tmp += "\n";
    }
    else if (word.length() > 1)
        tmp = "\033[38;5;104mYou are now afk: " + word + "\033[0m\n";
	data->at(user - 4).setaway_message(word);
    send(user, tmp.c_str(), tmp.size(), 0);
}

void nick_command(int user, vector<Data> *data, string input, IRC *server)
{
    string tmp;
    string newnick;
    stringstream ss(input);
    string word;
	string tmp2;

	ss >> tmp2;
	if (input[tmp2.length() + 1] == ' ')
	{
		tmp = "\033[38;5;104mBad input\033[0m\n";
		send(user, tmp.c_str(), tmp.size(), 0);
        return ;
	}
	ss >> newnick;
	if (newnick.length() < 3)
	{
		tmp = "\033[38;5;104mName too short\033[0m\n";
		send(user, tmp.c_str(), tmp.size(), 0);
		return ;
	}

    for (size_t i = 0; i < data->size(); i++)
    {
        if (data->at(i).getnickname() == newnick)
        {
            tmp = "\033[38;5;104mNickname already taken\033[0m\n";
            send(user, tmp.c_str(), tmp.size(), 0);
            return ;
        }
    }
    for (size_t i = 0; i < server->vget_adminusers().size(); i++)
	{
		if (data->at(i).getusername() == newnick)
			break ;
		if (server->getwhitelist_users(i) == newnick)
		{
			tmp = "\033[38;5;104mForbidden name\033[0m\n";
            send(user, tmp.c_str(), tmp.size(), 0);
            return ;
		}
	}
    data->at(user - 4).setnickname(newnick);
    tmp = "\033[38;5;104mNickname changed to " + newnick + "\033[0m\n";
    send(user, tmp.c_str(), tmp.size(), 0);
}

void msg_command(int user, vector<Data> *data, string input)
{
    string tmp;
	string finalMSG;
    string receveur;
    stringstream cc(input);
	string sender;
    
	cc >> tmp;
	cc >> receveur;
	size_t size = tmp.length() + receveur.length() + 1;
	if (input[tmp.length() + 1] == ' ')
	{
		tmp = "\033[38;5;104mBad input\033[0m\n";
		send(user, tmp.c_str(), tmp.size(), 0);
        return ;
	}
	finalMSG += &input[size];
	finalMSG += "\n";
	if (data->at(user - 4).getaway() == TRUE)
    {
        data->at(user - 4).setaway(FALSE);
        data->at(user - 4).setaway_message("");
        tmp = "\033[38;5;104mYou are now back\033[0m\n";
        send(user, tmp.c_str(), tmp.size(), 0);
    }
	for (size_t n = 0; n < data->size(); n++)
	{
		if (data->at(n).getnickname() == receveur && data->at(n).getaway() == FALSE)
		{
			tmp = "from ";
			sender = data->at(user - 4).getnickname() + ":";
			send(data->at(n).getfd(), tmp.c_str(), tmp.size(), 0);
			send(data->at(n).getfd(), sender.c_str(), sender.size(), 0);
			send(data->at(n).getfd(), finalMSG.c_str(), finalMSG.size(), 0);
			return ;
		}
		else if (data->at(n).getnickname() == receveur && data->at(n).getaway() == TRUE)
        {
			sender = "from " + data->at(user - 4).getnickname() + ":";
            tmp = receveur + " is away: " + data->at(n).getaway_message() + "\n";
            send(user, tmp.c_str(), tmp.size(), 0);
            send(data->at(n).getfd(), sender.c_str(), sender.size(), 0);
			send(data->at(n).getfd(), finalMSG.c_str(), finalMSG.size(), 0);
            return ;
        }

    }
	tmp = "\033[38;5;104mUser not found\033[0m\n";
	send(user, tmp.c_str(), tmp.size(), 0);
}

void op_command(int user, vector<Data> *data, string input, IRC *server, int op)
{
    string tmp;
    string newop;
    stringstream ss(input);
    string word;
    string tmp2;
	string pass;
    ss >> tmp2;
    if (input[tmp2.length() + 1] == ' ')
    {
        tmp = "\033[38;5;104mBad input\033[0m\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        return ;
    }
	ss >> newop;
    ss >> pass;
	bool check_user = FALSE;
	for(size_t n = 0; n < data->size(); n++)
	{
		tmp = data->at(n).getusername();
		if (newop == tmp)
			check_user = TRUE;
	}
	if (check_user == FALSE)
	{
		tmp = "\033[38;5;104mUser not found\033[0m\n";
		send(user, tmp.c_str(), tmp.size(), 0);
		return ;
	}
	if (pass != server->getadminpassword())
	{
		tmp = "\033[38;5;104mBad password\033[0m\n";
		send(user, tmp.c_str(), tmp.size(), 0);
		return ;
	}


	for (size_t j = 0; j < server->vget_adminusers().size(); j++)
	{
		if (server->getwhitelist_users(j) == data->at(user - 4).getusername())
		{
            for (size_t i = 0; i < data->size(); i++)
            {
                if (data->at(i).getusername() == newop)
                {
					if (op == 1)
					{
						if (data->at(i).getadmin() == ADMIN)
						{
							tmp = "\033[38;5;104m" + data->at(i).getusername() + " is already an op\033[0m\n";
							send(user, tmp.c_str(), tmp.size(), 0);
							return ;
						}
						else if (data->at(i).getadmin() != ADMIN)
						{
							data->at(i).setadmin(ADMIN);
							tmp = "\033[38;5;104m" + data->at(i).getusername() + " is now an op\033[0m\n";
							server->setwhitelist_users(newop);
							send(user, tmp.c_str(), tmp.size(), 0);
							return ;
						}
					}
					else if (op == 0)
					{
						if (data->at(i).getadmin() != ADMIN)
						{
							tmp = "\033[38;5;104m" + data->at(i).getusername() + " isn't op\033[0m\n";
							send(user, tmp.c_str(), tmp.size(), 0);
							return ;
						}
						else if (data->at(i).getadmin() == ADMIN)
						{
							data->at(i).setadmin(CLIENT);
							tmp = "\033[38;5;104m" + data->at(i).getusername() + " is not op anymore\033[0m\n";
							server->remove_admin(j); 
							send(user, tmp.c_str(), tmp.size(), 0);
							return ;
						}
					}
                }
            }
		}
    }
	tmp = "\033[38;5;104mYou're not an admin\033[0m\n";
	send(user, tmp.c_str(), tmp.size(), 0);
}

void kick_command(int user, vector<Data> *data, string input, IRC *server, vector<Channel> *chan)
{
	string channel;
	string client;
    stringstream ss(input);
	string tmp;

    ss >> tmp;
	ss >> channel;
	ss >> client;
    if (input[tmp.length() + 1] == ' ')
    {
        tmp = "\033[38;5;104mBad input\033[0m\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        return ;
    }
	bool check_user = FALSE;
	for(size_t n = 0; n < data->size(); n++)
		if (client == data->at(n).getnickname() && data->at(n).getnickname().size() > 2)
			check_user = TRUE;
	if (check_user == FALSE)
	{
		tmp = "\033[38;5;104mUser not found\033[0m\n";
		send(user, tmp.c_str(), tmp.size(), 0);
		return ;
	}
	bool check_channel = FALSE;
	for(size_t n = 0; n < chan->size(); n++)
		if (chan->at(n).getname() == channel)
			check_channel = TRUE;
	if (check_channel == FALSE)
	{
		tmp = "\033[38;5;104mChannel not found\033[0m\n";
		send(user, tmp.c_str(), tmp.size(), 0);
		return ;
	}
    string reason = &input[input.find(client) + client.length()];
	for (size_t j = 0; j < server->vget_adminusers().size(); j++)
	{
		if (server->getwhitelist_users(j) == data->at(user - 4).getusername())
		{
            for (size_t i = 0; i < data->size(); i++)
            {
                if (data->at(i).getnickname() == client)
                {
					if (data->at(i).getchannel() == "The_accueil")
                    {
						tmp = "\033[38;5;104m" + client + " have been killed by " + data->at(user - 4).getnickname() + " for: " + reason + "\033[0m\n";
						send(user, tmp.c_str(), tmp.size(), 0);
						tmp = "\033[38;5;104mYou have been killed by " + data->at(user - 4).getnickname() + " for: " + reason + "\033[0m\n";
						send(data->at(i).getfd(), tmp.c_str(), tmp.size(), 0);
						cout << "\033[38;5;196mUser " << data->at(i).getusername() << " has been killed by " << data->at(user - 4).getusername() << "\033[0m" << endl;
						user_left(data, chan, data->at(i).getfd(), data->at(i).getchannel());
						close(data->at(i).getfd());
						reset_client(&data->at(i), server);
						server->setcurrent_user(server->getcurrent_user() - 1);
						return ;
                    }
					tmp = "\033[38;5;104m" + client + " have been kicked for: " + reason + "\033[0m\n";
					send(user, tmp.c_str(), tmp.size(), 0);
                    tmp = "\033[38;5;104mYou have been kicked by " + data->at(user - 4).getnickname() + " for: " + reason + "\033[0m\n";
					send(data->at(i).getfd(), tmp.c_str(), tmp.size(), 0);
                    user_join_left(data, chan,  data->at(i).getfd(), "The_accueil", data->at(i).getchannel());
					cout << "\033[38;5;196mUser " << data->at(i).getusername() << " has been kicked by " << data->at(user - 4).getusername() << "\033[0m" << endl;
					return ;
                }
            }
		}
    }
	tmp = "\033[38;5;104mYou're not an admin\033[0m\n";
	send(user, tmp.c_str(), tmp.size(), 0);
}

void kill_command(int user, vector<Data> *data, string input, vector<Channel> *chan, IRC *server)
{
    stringstream ss(input);
    string tmp;

    ss >> tmp;
    string client;
    ss >> client;
    if (input[tmp.length() + 1] == ' ')
    {
        tmp = "\033[38;5;104mBad input\033[0m\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        return ;
    }
    bool check_user = FALSE;
	for(size_t n = 0; n < data->size(); n++)
		if (client == data->at(n).getnickname() && data->at(n).getnickname().size() > 2)
			check_user = TRUE;
	if (check_user == FALSE)
	{
		tmp = "\033[38;5;104mUser not found\033[0m\n";
		send(user, tmp.c_str(), tmp.size(), 0);
		return ;
	}
    string reason = &input[input.find(client) + client.length() + 1];
    for (size_t j = 0; j < server->vget_adminusers().size(); j++)
	{
		if (server->getwhitelist_users(j) == data->at(user - 4).getusername())
		{
            for (size_t i = 0; i < data->size(); i++)
            {
              
                if (data->at(i).getnickname() == client)
                {
                    tmp = "\033[38;5;104m" + client + " have been killed by " + data->at(user - 4).getnickname() + " for: " + reason + "\033[0m\n";
                    send(user, tmp.c_str(), tmp.size(), 0);
                    tmp = "\033[38;5;104mYou have been killed by " + data->at(user - 4).getnickname() + " for: " + reason + "\033[0m\n";
                    send(data->at(i).getfd(), tmp.c_str(), tmp.size(), 0);
					cout << "\033[38;5;196mUser " << data->at(i).getusername() << " has been killed by " << data->at(user - 4).getusername() << "\033[0m" << endl;
                    user_left(data, chan, data->at(i).getfd(), data->at(i).getchannel());
                    close(data->at(i).getfd());
					reset_client(&data->at(i), server);
                    server->setcurrent_user(server->getcurrent_user() - 1);
                    return ;
                }
            }
        }
    }
	tmp = "\033[38;5;104mYou're not an admin\033[0m\n";
	send(user, tmp.c_str(), tmp.size(), 0);
}

void    help_command(int user, string input)
{
    vector<string> tmp = init_commands();
    vector<string> tmp3 = commands();
    string tmp2;
    if (input.length() - 1 == 4)
    {
        for (size_t i = 0; i < tmp.size(); i++)
            send(user, tmp.at(i).c_str(), tmp.at(i).size(), 0);
        return ;
    }
    else
    {
        stringstream ss(input);
        for (size_t i = 0; i < 2; i++)
            ss >> tmp2;
        for (size_t i = 0; i < tmp.size(); i++)
        {
            if (tmp3.at(i) == tmp2)
            {
                send(user, tmp.at(i).c_str(), tmp.at(i).size(), 0);
                return;
            }
        }
    }
    tmp2 = "\033[38;5;104mCommand not found\033[0m\n";
    send(user, tmp2.c_str(), tmp2.size(), 0);
}

void	whois_command(int user, vector<Data> *data, string input)
{
    stringstream ss(input);
    string tmp;
    string display;

    ss >> tmp;
    string client;
    ss >> client;
	for (size_t n = 0; n < data->size(); n++)
	{
		if (data->at(n).getnickname().length() > 1)
		{
			if (data->at(n).getnickname() == client)
			{
				display = "• Nickname: " + data->at(n).getnickname() + "\n";
				display += "• Username: " +data->at(n).getusername() + "\n";
				display += "• Current channel: " + data->at(n).getchannel() + "\n";
				if (data->at(n).getaway() == 1)
					display += "• Away: " + data->at(n).getaway_message() + "\n";
				send(user, display.c_str(), display.size(), 0);
				return ;
			}
		}
	}
	display = "\033[38;5;104mNo user found\033[0m\n";
	send(user, display.c_str(), display.size(), 0);
}

void notice_command(int user, vector<Data> *data, string input, vector<Channel> *chan)
{
	stringstream ss(input);
	string tmp;

	ss >> tmp;
	if (input[tmp.length() + 1] == ' ')
	{
		tmp = "\033[38;5;104mBad input\033[0m\n";
		send(user, tmp.c_str(), tmp.size(), 0);
		return ;
	}
	ss >> tmp;
	string client = tmp;
	for (size_t i = 0; i < data->size(); i++)
	{
		if (data->at(i).getnickname() == client)
		{
			size_t it = input.find(client) + client.size() + 1;
			tmp = "\033[38;5;104m" + data->at(user - 4).getnickname() + " send you a notice: " + &input[it] + "\033[0m\n";
			send(data->at(i).getfd(), tmp.c_str(), tmp.size(), 0);
			return ;
		}
	}
	for (size_t i = 0; i < chan->size(); i++)
	{
		if (chan->at(i).getname() == tmp)
		{
			for (size_t j = 0; j < chan->at(i).vgetusers().size(); j++)
			{
				if (chan->at(i).getuser(j).getfd() != user)
				{
					size_t it = input.find(tmp) + tmp.size() + 1;
					tmp = "\033[38;5;196m" + data->at(user - 4).getnickname() + ": " + &input[it] + "\033[0m" +"\n";
					send(chan->at(i).getuser(j).getfd(), tmp.c_str(), tmp.size(), 0);
					return ;
				}
			}
			return ;
		}
	}
	tmp = "\033[38;5;104mNo user or channel found\n\033[0m";
	send(user, tmp.c_str(), tmp.size(), 0);
}