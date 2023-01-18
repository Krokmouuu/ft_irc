#include "ft_irc.hpp"

void start_server(char **argv, IRC server)
{
    string maxuser;
    typeWriter("Welcome in PLE-BLEROY ImanRC settings.\nPlease enter maximum user allowed to join the server :");
    cin >> maxuser;
    if(parsing_nb_user(maxuser, server))
        return ;
    server.setmaxuser(stoi(maxuser));
	//? Initialisation de la socket
	int socketServer = socket(AF_INET, SOCK_STREAM, 0); //? Socket = IPV4, FLUX, don't care
    server.setsocketServer(socketServer);

	//? Creating struct for the server
	struct sockaddr_in addrServer;

	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1"); //? Address
	addrServer.sin_family = AF_INET; //? IPV4
	addrServer.sin_port = htons(atoi(argv[1])); //? Using port not used (more than 10000 is pretty safe)
    typeWriter("Socket created.\n");
    typeWriter("Server started on port : "), printf("%s\n", server.getserverport().c_str());

	//? Connection to server
	bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer)); //? Server, arg type sockaddr for conversion and size
	listen(socketServer, server.getmaxuser()); //? Server, numbers of clients
    typeWriter("Waiting for user.\n");
	//? Accept if a user join the server
    struct sockaddr_in addrClient;
    socklen_t csize = sizeof(addrClient);
    int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize); //? Server, arg type sockaddr for conversion and size
    printf("Client connected, #%d\n", socketClient);
    close(socketClient);
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
        try
        {
            if (ft_parsing(argv))
                return 1;
            IRC server(argv[1], argv[2]);
            start_server(argv, server);
            // while (1)
            // {
            //     close (server.getsocketServer());
            //     ;// info_user(server);
            // }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return 0;
}