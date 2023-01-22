#include "ft_irc.hpp"

//! This function is used to print the name of the user in the terminal
void print_name(vector<Data> *data, vector<Channel> *chan, int user, bool useless)
{
	(void)data;
	(void)user;
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