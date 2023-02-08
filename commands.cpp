#include "ft_irc.hpp"

// /join Y
// /quit / leave Y
// /w /msg Y
// /nick Y
// /away Y 
// /names Y
// /list Y
//? /ping / pong X
//? /help X 
//? /help [command] X
//? /whois X 
//? /who X
//? kick (leave channel) X
//? kill (leave server) X
// /op Y
// /deop Y

void beep_beep_boop(string input, int user, vector<Data> *data, vector<Channel> *chan)
{
    string tmp;
    stringstream ss(input);  
    string word;
    while (ss >> word)
    {
        if (word == "quoi" || word == "QUOI" || word == "Quoi" || word == "quoi?" || word == "QUOI?" || word == "Quoi?" || word == "koi" || word == "Koi")
        {
            for (size_t i = 0; i < chan->size(); i++)
            {
                tmp = "feurbot: feur @" + data->at(user - 4).getnickname() + " XD\n";
                for (size_t j = 0; j < chan->at(i).vgetusers().size(); j++)
                    send(chan->at(i).getuser(j).getfd(), tmp.c_str(), tmp.size(), 0);
            }
        }
        else if (word == "qui" || word == "QUI" || word == "Qui" || word == "qui?" || word == "QUI?" || word == "Qui?" || word == "ki")
        {
            for (size_t i = 0; i < chan->size(); i++)
            {
                tmp = "quettebot: qui ? quette @" + data->at(user - 4).getnickname() + " XD\n";
                for (size_t j = 0; j < chan->at(i).vgetusers().size(); j++)
                    send(chan->at(i).getuser(j).getfd(), tmp.c_str(), tmp.size(), 0);
            }
        }
    }
}

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
        tmp = "Please enter a channel name\n";
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
                    tmp = "You are already in < " + chan->at(i).getname() + " >" + " channel !\n";
                    send(data->at(user - 4).getfd(), tmp.c_str(), tmp.size(), 0);
                    return ;
                }
                user_join_left(data, chan, user, chan->at(i).getname(), data->at(user - 4).getchannel());
                return ;
            }
        }
    }
    tmp = "Channel not found\n";
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

void	names_command(int user, vector<Data> *data)
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

void away_command(int user, vector<Data> *data, string input)
{
    string tmp;
    stringstream ss(input);
    string word;
    string tmp2;
    ss >> tmp2;
    if (input[tmp2.length() + 1] == ' ')
    {
        tmp = "Bad input\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        return ;
    }
    if (data->at(user - 4).getaway() == TRUE)
    {
        data->at(user - 4).setaway(FALSE);
        tmp = "You are now back\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        return ;
    }
    data->at(user - 4).setaway(TRUE);
	word += &input[tmp2.length() + 1];
	if (word.length() <= 1)
    {
		word = "";
        tmp = "You are now afk";
		tmp += "\n";
    }
    else if (word.length() > 1)
        tmp = "You are now afk: " + word + "\n";
	data->at(user - 4).setaway_message(word);
    send(user, tmp.c_str(), tmp.size(), 0);
}

void nick_command(int user, vector<Data> *data, string input)
{
    string tmp;
    string newnick;
    stringstream ss(input);
    string word;
	string tmp2;

	ss >> tmp2;
	if (input[tmp2.length() + 1] == ' ')
	{
		tmp = "Bad input\n";
		send(user, tmp.c_str(), tmp.size(), 0);
        return ;
	}
	ss >> newnick;
    for (size_t i = 0; i < data->size(); i++)
    {
        if (data->at(i).getnickname() == newnick)
        {
            tmp = "Nickname already taken\n";
            send(user, tmp.c_str(), tmp.size(), 0);
            return ;
        }
    }
    data->at(user - 4).setnickname(newnick);
    tmp = "Nickname changed to " + newnick + "\n";
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
		tmp = "Bad input\n";
		send(user, tmp.c_str(), tmp.size(), 0);
        return ;
	}
	finalMSG += &input[size];
	finalMSG += "\n";
	if (data->at(user - 4).getaway() == TRUE)
    {
        data->at(user - 4).setaway(FALSE);
        data->at(user - 4).setaway_message("");
        tmp = "You are now back\n";
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
	tmp = "User not found\n";
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
        tmp = "Bad input\n";
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
		tmp = "User not found\n";
		send(user, tmp.c_str(), tmp.size(), 0);
		return ;
	}
	if (pass != server->getadminpassword())
	{
		tmp = "Bad password\n";
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
							tmp = data->at(i).getusername() + " is already an op\n";
							send(user, tmp.c_str(), tmp.size(), 0);
							return ;
						}
						else if (data->at(i).getadmin() != ADMIN)
						{
							data->at(i).setadmin(ADMIN);
							tmp = data->at(i).getusername() + " is now an op\n";
							server->setwhitelist_users(newop);
							send(user, tmp.c_str(), tmp.size(), 0);
							return ;
						}
					}
					else if (op == 0)
					{
						if (data->at(i).getadmin() != ADMIN)
						{
							tmp = data->at(i).getusername() + " isn't op\n";
							send(user, tmp.c_str(), tmp.size(), 0);
							return ;
						}
						else if (data->at(i).getadmin() == ADMIN)
						{
							data->at(i).setadmin(CLIENT);
							tmp = data->at(i).getusername() + " is not op anymore\n";
							server->remove_admin(j); 
							send(user, tmp.c_str(), tmp.size(), 0);
							return ;
						}
					}
                }
            }
		}
    }
	tmp = "You're not an admin\n";
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
        tmp = "Bad input\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        return ;
    }
	bool check_user = FALSE;
	for(size_t n = 0; n < data->size(); n++)
	{
		tmp = data->at(n).getnickname();
		if (client == tmp)
			check_user = TRUE;
	}
	if (check_user == FALSE)
	{
		tmp = "User not found kk\n";
		send(user, tmp.c_str(), tmp.size(), 0);
		return ;
	}
	bool check_channel = FALSE;
	for(size_t n = 0; n < chan->size(); n++)
		if (chan->at(n).getname() == channel)
			check_channel = TRUE;
	if (check_channel == FALSE)
	{
		tmp = "Channel not found\n";
		send(user, tmp.c_str(), tmp.size(), 0);
		return ;
	}
	for (size_t j = 0; j < server->vget_adminusers().size(); j++)
	{
		if (server->getwhitelist_users(j) == data->at(user - 4).getusername())
		{
            for (size_t i = 0; i < data->size(); i++)
            {
                if (data->at(i).getusername() == client)
                {
					if (data->at(i).getchannel() == "The_accueil")
                    {
						kill_command(user, data, input, chan);
                        return ;
                    }
                    user_join_left(data, chan,  data->at(i).getfd(), "The_accueil", data->at(i).getchannel());
					tmp = "kicking " + client + "\n";
					send(user, tmp.c_str(), tmp.size(), 0);
					return ;
                    //! send to the client that he has been kicked
                }
            }
		}
    }
	tmp = "You're not an admin\n";
	send(user, tmp.c_str(), tmp.size(), 0);
}

//! KILL <client> <comment>
void kill_command(int user, vector<Data> *data, string input, vector<Channel> *chan)
{
    stringstream ss(input);
    string tmp;

    ss >> tmp;
    if (input[tmp.length() + 1] == ' ')
    {
        tmp = "Bad input\n";
        send(user, tmp.c_str(), tmp.size(), 0);
        return ;
    }
    string client;

    ss >> client;
    for (size_t i = 0; i < data->size(); i++)
    {
        if (data->at(i).getnickname() == client)
        {
            tmp = "You have been killed by " + data->at(user - 4).getnickname() + "\n";
            send(data->at(i).getfd(), tmp.c_str(), tmp.size(), 0);
            user_left(data, chan, user, data->at(user - 4).getchannel());
            // reset_client(&data[user - 4], user, &chan, data->at(user - 4).getchannel());
            close(data->at(i).getfd());
            //! RESET LE CLIENT
        }
    }
    return ;
}