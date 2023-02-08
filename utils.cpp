#include "ft_irc.hpp"

void reset_client(Data *data, int user, vector<Channel> *chan, string channel)
{
	(void)user;
	(void)chan;
	(void)channel;
    data->setusername("");
    data->setnickname("");
    data->setlog(NEW_CLIENT);
    data->setfd(0);
    data->setchannel("The_accueil");
    data->setconnected(DEFAULT);
	data->setaway(FALSE);
	data->setaway_message("");
	data->setadmin(CLIENT);
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