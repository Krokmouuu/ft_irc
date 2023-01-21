#include "ft_irc.hpp"

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