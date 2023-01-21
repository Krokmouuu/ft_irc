#include "ft_irc.hpp"
#include "Data.hpp"

int parse_input(string input, IRC server, Data *data, int user)
{
    data->setnumber(user - 4);
    if (input == server.getpassword() && data->getlog() == 0)
    {
        data->setlog(1);
        send(user, "Password correct.\n", 18, 0);
        send(user, "Please enter your username: ", 29, 0);
    }
    else if (data->getlog() == 1 && data->getusername() == "")
    {
        if (input.size() < 2 || input.size() > 26)
        {
            send(user, "Username must be between 2 and 26 characters.\nPlease enter your username: ", 75, 0);
            return 0;
        }
        data->setusername(input);
        send(user, "Please enter your nickname: ", 28, 0);
        return 1;
    }
    else if (data->getlog() != 0 && data->getnickname() == "" && data->getusername() != "")
    {
        if (data->getlog() != 0 && data->getusername() != "")
        {
            data->setnickname(input);
            send(user, "Welcome to the server ", 22, 0);
            send(user, data->getusername().c_str(), data->getusername().length(), 0);
            send(user, " (", 2, 0);
            send(user, data->getnickname().c_str(), data->getnickname().length(), 0);
            send(user, ") ", 2, 0);
            send(user, "!\n", 2, 0);
            data->setlog(2);
            return 0;
        }
    }
    else if (input != server.getpassword() && data->getlog() == 0)
    {
        send(user, "Password incorrect.\n", 20, 0);
        send(user, "Please enter password: ", 24, 0);
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