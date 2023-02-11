#include "ft_irc.hpp"

vector<string> commands()
{
	vector<string> commands;
	commands.push_back("/join");
	commands.push_back("/list");
	commands.push_back("/names");
	commands.push_back("/w");
	commands.push_back("/msg");
	commands.push_back("/nick");
	commands.push_back("/away");
	commands.push_back("/op");
	commands.push_back("/deop");
	commands.push_back("/kick");
	commands.push_back("/kill");
	commands.push_back("/help");
	return commands;
}

vector<string>	init_commands()
{
	vector<string> commands;
	commands.push_back("/join <channel>: join a channel\n");
	commands.push_back("/list: display all channels available\n");
	commands.push_back("/names: display all users in the channel\n");
	commands.push_back("/w <user> | /msg <user>: send a private message to a user\n");
	commands.push_back("/nick <nickname>: change your nickname\n");
	commands.push_back("/away <message>: set your status to away\n");
	commands.push_back("/op <user> <password>: give operator status to a user\n");
	commands.push_back("/deop <user> <password>: remove operator status to a user\n");
	commands.push_back("/kick <channel> <user>: kick a user from a channel\n");
	commands.push_back("/kill <user>: kick a user from the server\n");
	commands.push_back("/help | /help <command>: display all commands or a specific command\n");
	return commands;
}

void reset_client(Data *data)
{
    data->setusername("");
    data->setnickname("");
    data->setlog(NEW_CLIENT);
    data->setfd(-1);
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