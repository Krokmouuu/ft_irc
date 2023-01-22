#include "ft_irc.hpp"


void	print_server(vector<Data> *data, vector<Channel> *chan, int user)
{
	send(chan->at(0).vgetusers().at(user - 4).getfd(), string_to_char(chan->at(0).vgetusers().at(user - 4).getnickname() + ": "), chan->at(0).vgetusers().at(user - 4).getnickname().size() + 2,0);
	for (size_t i = 0; i < data->size(); i++)
	{
		if (data->at(i).getfd() != chan->at(0).vgetusers().at(user - 4).getfd())
		{
			send(chan->at(0).vgetusers().at(user - 4).getfd(), string_to_char(data->at(i).getnickname() + " "), data->at(i).getnickname().size() + 1,0);
		}
	}
	// send(chan->at(0).vgetusers().at(user - 4).getfd(), string_to_char(" joined the channel.\n"), 31,0);
}

void print_name(vector<Channel> *chan, int user)
{
	send(chan->at(0).vgetusers().at(user - 4).getfd(), string_to_char(chan->at(0).vgetusers().at(user - 4).getnickname() + ": "), chan->at(0).vgetusers().at(user - 4).getnickname().size() + 2,0);
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