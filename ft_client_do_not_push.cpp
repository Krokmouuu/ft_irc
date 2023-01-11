#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct s_user
{
	char nom[30];
	int age;
}t_user;


int main(void)
{
	int socketClient = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addrClient;
	addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(30000);
	connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient));
	std::cout << "CONNECTED" << std::endl;

	t_user user;
	char msg[33];
	recv(socketClient, msg, 32, 0);
	std::cout << msg << std::endl;
	std::cin >> user.nom;
	std::cin >> user.age;
	connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient));
	send(socketClient, &user, sizeof(user), 0);

	close(socketClient);

	return 0;
}
