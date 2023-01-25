#include "ft_irc.hpp"

vector<string> init_string()
{
	vector<string> tmp;
	tmp.push_back("/join");
	tmp.push_back("/quit");
	tmp.push_back("/leave");
	tmp.push_back("/w");
	tmp.push_back("/msg");
	tmp.push_back("/ping");
	tmp.push_back("/pong");
	tmp.push_back("/nick");
	tmp.push_back("/afk");
	tmp.push_back("/names");
	tmp.push_back("/back");
	tmp.push_back("/list");
	tmp.push_back("/help");
	tmp.push_back("/whois");
	tmp.push_back("/who");
	return tmp;
}

void reset_client(Data *data, int user, vector<Channel> *chan, string channel)
{
	(void)user;
	(void)chan;
	(void)channel;
    data->setusername("");
    data->setnickname("");
    data->setlog(NEW_CLIENT);
    data->setfd(0);
    data->setchannel("The accueil");
    data->setconnected(DEFAULT);
	data->setaway(FALSE);
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