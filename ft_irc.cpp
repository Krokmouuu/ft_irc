#include "ft_irc.hpp"

using namespace std;

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
    return 0;
}
typedef struct s_user
{
	char nom[30];
	int age;
}t_user;
void start_server(char **argv)
{
        IRC server(argv[1], argv[2]);

	while(1)
	{
		printf("ok");
		//? Initialisation de la socket
		int socketServer = socket(AF_INET, SOCK_STREAM, 0); //? Socket = IPV4, FLUX, don't care

		//? Creating struct for the server
		struct sockaddr_in addrServer;

		printf("ok");
		addrServer.sin_addr.s_addr = inet_addr("127.0.0.1"); //? Address
		addrServer.sin_family = AF_INET; //? IPV4
		addrServer.sin_port = htons(30000); //? Using port not used (more than 10000 is pretty safe)

		printf("ok1");
		//? Connection to server
		bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer)); //? Server, arg type sockaddr for conversion and size
		listen(socketServer, 20); //? Server, numbers of clients

		printf("ok2");
		//? Accept if a user join the server
		struct sockaddr_in addrClient;
		socklen_t csize = sizeof(addrClient);
		int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);
			
		t_user user;
		send(socketClient, &user, sizeof(t_user), 0);

		printf("ok3");
		close(socketClient);
		close(socketServer); 
	}
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Server port and password is needed" << endl; 
        return 0;
    }
    else
    {
        if (ft_parsing(argv))
            return 1;
        start_server(argv);
    }
    return 0;
}