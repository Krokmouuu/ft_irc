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

//! This function is used to print the name of the user in the terminal, TRUE = print all the name of the users in the channel, FALSE = print the name of the user who send the message
void print_name(vector<Data> *data, vector<Channel> *chan, int user, bool useless)
{
	if (useless == TRUE)
	{
		for (size_t i = 0; i < chan->at(i).vgetusers().size(); i++)
		{
			for (size_t j = 0; j < chan->at(i).vgetusers().size(); j++)
				send(chan->at(i).getuser(j).getfd(), string_to_char(chan->at(i).vgetusers().at(j).getnickname() + ": "), chan->at(i).vgetusers().at(j).getnickname().size() + 2,0);
		}
	}
	else
	    send(user, string_to_char(data->at(user - 4).getnickname() + ": "), data->at(user - 4).getnickname().size() + 2, 0);
}

//my beautiful function to write message in the terminal letter by letter :]
void typeWriter(string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		usleep(15000);
		std::cout << str[i] << std::flush;
	}
}

char	*string_to_char(string str)
{
	char *cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	return cstr;
}