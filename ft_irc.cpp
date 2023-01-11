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

//my beautiful function to write message in the terminal letter by letter :]
void	typeWriter(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		usleep(15000);
		std::cout << str[i] << std::flush;
	}
}

typedef struct s_user
{
	char nom[30];
	int age;
}t_user;

void *socketThread(void *arg)
{
    int socket = *(int*)arg;
    char msg[] = "quel est votre nom et votre age";
    t_user user;
    //? Sending the message with the right len
	send(socket, msg, strlen(msg)+1, 0);
	typeWriter("WAITING TO RECEIVE INFORMATIONS OF THE USER...\n");
    //? Receive the informations about user in &user
    recv(socket, &user, sizeof(user), 0);
	fflush(0);
    std::stringstream ss;
    ss << user.age;
    string str = ss.str();
	typeWriter("Name: "), typeWriter(user.nom), typeWriter("\nAge: "), typeWriter(str), typeWriter("\n\n");
    close(socket);
    free (arg);
    pthread_exit(NULL);
}

void start_server(char **argv)
{
	IRC server(argv[1], argv[2]);
    int maxuser = 3;

	//? Initialisation de la socket
	int socketServer = socket(AF_INET, SOCK_STREAM, 0); //? Socket = IPV4, FLUX, don't care

	//? Creating struct for the server
	struct sockaddr_in addrServer;

	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1"); //? Address
	addrServer.sin_family = AF_INET; //? IPV4
	addrServer.sin_port = htons(atoi(argv[1])); //? Using port not used (more than 10000 is pretty safe)

	//? Connection to server
	bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer)); //? Server, arg type sockaddr for conversion and size
	listen(socketServer, 3); //? Server, numbers of clients
	//? Accept if a user join the server
    pthread_t clientThread[maxuser];
    struct sockaddr_in addrClient;
    for(int i = 0; i < maxuser; i++)
    {
        socklen_t csize = sizeof(addrClient);
        int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);
		//! socketClient is always the same
        printf("USER NUMERO : %d\n", socketClient);
		int *arg = new int;
        *arg = socketClient;
            
        pthread_create(&clientThread[i], NULL, socketThread, arg);
    }
    for(int i = 0; i < maxuser; i++)
        pthread_join(clientThread[i], NULL);
    close(socketServer);
    return ;
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