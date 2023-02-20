#include "ft_irc.hpp"
#include "Data.hpp"
//! regler les quelques sauts à la ligne en trop
void sent(Data *data, int user, const char *input)
{
	if (data->getIRSSI() == 1)
	{
		send(user, "\n", 1, 0);
		send(user, input, strlen(input), 0);
	}
	else
		send(user, input, strlen(input), 0);
}

int irssi_parsing(string input, Data *data, IRC *server, int user, vector<Data> *vdata)
{

	string strPASS = "PASS";
	string strNICK = "NICK";
	string strUSER = "USER";
	string foundPASS;
	string foundUSER;
	string foundNICK;
	string tmp;
	std::size_t found = input.find(strPASS);
  	if (found != std::string::npos && data->getlog() == NEW_CLIENT)
    {
		stringstream ss(&input[found]);  
		ss >> tmp;
		ss >> foundPASS;
	}
	found = input.find(strNICK);
  	if (found != std::string::npos && data->getlog() == NEW_CLIENT)
    {
		stringstream ss(&input[found]);  
		ss >> tmp;
		ss >> foundNICK;
	}
	found = input.find(strUSER);
  	if (found != std::string::npos && data->getlog() == NEW_CLIENT)
    {
		stringstream ss(&input[found]);  
		ss >> tmp;
		ss >> foundUSER;
	}

	if (foundPASS == server->getpassword() && data->getlog() == NEW_CLIENT)
    {
        data->setlog(LOGGED);
		cout.flush();
        sent(data, user, "​Password correct.\n");
        data->setfd(user);
    }
	if (data->getlog() == LOGGED && foundUSER.length() > 1)
    {
        for (size_t i = 0; i < foundUSER.length(); i++)
        {
            if (foundUSER[i] > 0 && foundUSER[i] < 33)
            {
                sent(data, user, "Username can't contain a space.\nPlease enter your nickname:\n");
                return 1;
            }
        }
        if (foundUSER.length() < 2 || foundUSER.length() > 26)
        {
            sent(data, user, "Username must be between 2 and 26 characters.\nPlease enter your username:\n");
            return 1;
        }
<<<<<<< HEAD
        for (size_t i = 0; i < vdata->size(); i++)
        {
            if (vdata->at(i).getusername() == foundUSER)
            {
                sent(data, user, "Username already taken.\nYou are disconnected.\n");
                reset_client(data, server);
                close(user);
                return 1;
            }
        }
		send(user, "\nUsername valid.\n", 18, 0);
=======
		sent(data, user, "\nUsername valid.\n");
>>>>>>> 88db85e33ac93c0781b66265f18d5c1cc5a3a263
        data->setusername(foundNICK);
        data->setlog(LOGGED_MAYBE);
    }
 	if (data->getlog() == LOGGED_MAYBE && foundNICK.length() > 1)
    {
        for (size_t i = 0; i < foundNICK.length(); i++)
        {
            if (foundNICK[i] > 0 && foundNICK[i] < 33)
            {
                sent(data, user, "Nickname can't contain a space.\nPlease enter your username:\n");
                return 1;
            }
        }
        if (foundNICK.length() < 2 || foundNICK.length() > 26)
        {
            sent(data, user, "Nickname must be between 2 and 26 characters.\nPlease enter your nickname:\n");
            return 1;
        }
        else
        {
            for (size_t i = 0; i < vdata->size(); i++)
            {
                if (vdata->at(i).getnickname() == foundNICK)
                {
                    sent(data, user, "Nickname already taken.\nYou are disconnected.\n");
                    reset_client(data, server);
                    close(user);
                    return 1;
                }
            }
            for (size_t i = 0; i < vdata->size(); i++)
            {
                if (vdata->at(i).getnickname() == foundNICK)
                {
<<<<<<< HEAD
                    sent(data, user, "Nickname already taken.\nPlease enter your username:\n");
=======
                    sent(data, user, "Nickname already taken.\nPlease enter your nickname:\n");
>>>>>>> 88db85e33ac93c0781b66265f18d5c1cc5a3a263
                    return 1;
                }
            }
            data->setnickname(foundNICK);
            sent(data, user, "Nickname valid.\n");
			string toto = "Welcome to the server " + data->getusername() + " (" + data->getnickname() + " )!\n";
			sent(data, user, toto.c_str());
            data->setlog(LOG_COMPLETED);
            data->setconnected(DEFAULT);
            data->setfd(user);
            data->setnumber(user - 4);
			data->setadmin(CLIENT);
            for (size_t i = 0; i < server->vget_adminusers().size(); i++)
                if (server->getwhitelist_users(i) == data->getusername())
                    data->setadmin(ADMIN);
        }
    }
	return 0;
}


int parse_log(string input, IRC *server, Data *data, int user, vector<Data> *vdata)
{
	string IRSSIstr = "CAP LS";

	//Check if the client connecting is from IRSSI or not
	std::size_t found = input.find(IRSSIstr);
  	if (found != std::string::npos && data->getlog() == NEW_CLIENT)
    {
		data->setIRSSI(1);
		return (irssi_parsing(input, data, server, user, vdata));
	}

    if (input == server->getpassword() && data->getlog() == NEW_CLIENT)
    {
        data->setlog(LOGGED);
		sent(data, user, "Password correct.\n");
		sent(data, user, "Please enter your username:\n");
        data->setfd(user);
    }
    else if (data->getlog() == LOGGED)
    {
        for (size_t i = 0; i < input.size(); i++)
        {
            if (input[i] > 0 && input[i] < 33)
            {
				sent(data, user, "Username can't contain a space.\nPlease enter your username:\n");
                return 1;
            }
        }
        if (input.size() < 2 || input.size() > 26)
        {
			sent(data, user, "Username must be between 2 and 26 characters.\nPlease enter your username:\n");
            return 1;
        } 
        else
        {
            for (size_t i = 0; i < vdata->size(); i++)
                {
                    if (vdata->at(i).getnickname() == input)
                    {
                        sent(data, user, "Username already taken.\nPlease enter your nickname:\n");
                        return 1;
                    }
                }
        }
        data->setusername(input);
        data->setlog(LOGGED_MAYBE);
		sent(data, user, "Please enter your nickname:\n");
    }
    else if (data->getlog() == LOGGED_MAYBE)
    {
        for (size_t i = 0; i < input.size(); i++)
        {
            if (input[i] > 0 && input[i] < 33)
            {
				sent(data, user, "Nickname can't contain a space.\nPlease enter your username:\n");
                return 1;
            }
        }
        if (input.size() < 2 || input.size() > 26)
        {
			sent(data, user, "Nickname must be between 2 and 26 characters.\nPlease enter your nickname:\n");
            return 1;
        }
        else
        {
            for (size_t i = 0; i < vdata->size(); i++)
            {
                if (vdata->at(i).getnickname() == input)
                {
					sent(data, user, "Nickname already taken.\nPlease enter your nickname:\n");
                    return 1;
                }
            }
            data->setnickname(input);
          	sent(data, user, "Nickname valid.\n");
			string toto = "Welcome to the server " + data->getusername() + " (" + data->getnickname() + " )!";
			sent(data, user, toto.c_str());
            data->setlog(LOG_COMPLETED);
            data->setconnected(DEFAULT);
            data->setfd(user);
            data->setnumber(user - 4);
			data->setadmin(CLIENT);
            for (size_t i = 0; i < server->vget_adminusers().size(); i++)
                if (server->getwhitelist_users(i) == data->getusername())
                    data->setadmin(ADMIN);
        }
    }
    else if (input != server->getpassword() && data->getlog() == NEW_CLIENT)
    {
        sent(data, user, "Password incorrect.\nPlease enter password:\n");
        return 1;
    }
    return 0;
}

int ft_parsing(char **argv)
{
    int i = -1;
    while (argv[1][++i] != '\0')
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            cout << "Server port must be a number" << endl;
            return 1;
        }
        if (i > 4)
        {
            cout << "Port too high" << endl;
            return 1; 
        }
        else if (i == 4)
        {
            if (argv[1][0] > '6')
            {
                cout << "Port too high" << endl;
                return 1;
            }
            else if (argv[1][0] == '6' && argv[1][4] > '5')
            {
                cout << "Port too high" << endl;
                return 1;
            }
        }
    }
    i = -1;
    while (argv[2][++i] != '\0')
    {
        if (argv[2][i] < 32 || argv[2][i] > 126)
        {
            cout << "Password have incorrect character" << endl;
            return 1;
        }
    }
    if (i <= 3)
    {
        cout << "Password too short" << endl;
        return 1;
    }
    return 0;
}

int parsing_nb_user(string nb, IRC server)
{
    try
    {
        int a = nb.size();
        if (a == 1)
        {
            if (nb[0] <= '0')
            {
                typeWriter("0 user set. Server closed.\n");
                return 1;
            }
        }
        if (stoi(nb) > 2147483647 || stoi(nb) < -2147483648)
        {
            typeWriter("Invalid number of user.\n");
            return 1;
        }
        for (int i = 0; i < '\0'; i++)
        {
            if (nb[i] < '0' || nb[i] > '9')
            {
                typeWriter("Invalid number of user.\n");
                return 1;
            }
        }
        if (nb[0] == '0')
        {
            int i = -1;
            while (nb[++i] == '0')
            {
                ;
            }
            server.setmaxuser(stoi(nb.substr(i , nb.size() - 1)));
            typeWriter("Maximun user set to : "), printf("%d\n\n", server.getmaxuser());
            return 0;
        }
    }
    catch (const std::exception& e)
    {
        typeWriter("Invalid number of user.\n");
        return 1;
    }
    server.setmaxuser(stoi(nb));
    typeWriter("Maximun user set to : "), printf("%d\n\n", server.getmaxuser());
    return 0;
}