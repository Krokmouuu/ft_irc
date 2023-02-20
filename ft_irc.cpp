#include "ft_irc.hpp"
#include "Data.hpp"
#include "Channel.hpp"

//! Demander mot de passe si personne de la whitelist se connecte
void start_server(IRC server)  
{  
    int opt = TRUE;  
    int master_socket, addrlen, new_socket, max_clients, activity, i, valread, sd;

    typeWriter("\033[4m\033[1m\033[38;5;120mWelcome in PLE-BLEROY IRC server settings.\033[0m\nPlease enter maximum user allowed to join the server : ");
    cin >> max_clients;
	if (max_clients == 0)
		max_clients++;
    vector<Data> data;
    Bot bot;
    for (int i = 0; i < max_clients; i++)
        data.push_back(Data());
    vector<Channel> channels = init_channels();
    typeWriter("Maximum user allowed to join the server : " + to_string(max_clients) + "\n");

    server.setadminpassword("admin");
    server.setwhitelist_users("pleber");
    server.setwhitelist_users("bleroy");
    int client_socket[max_clients];
    int max_sd;
    struct sockaddr_in address;  
         
    char buffer[1024];  //data buffer of 1K 

    //set of socket descriptors 
    fd_set readfds;  
    char message[] = "\033[38;5;120mWelcome in PLE-BLEROY IRC server.\033[0m\n\r";  
     
    //initialise all client_socket[] to 0 so not checked 
    for (i = 0; i < max_clients; i++)  
        client_socket[i] = 0;  
         
    //create a master socket 
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons(stoi(server.getserverport())); 
         
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)  
    {  
        perror("bind failed");
        exit(EXIT_FAILURE);  
    }  
    typeWriter("Listener on port " + server.getserverport() + "\n");
         
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 3) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
         
    //accept the incoming connection 
    addrlen = sizeof(address);  
    typeWriter("\033[38;5;226mWaiting for connections ...\033[0m\n");  
    
    while(TRUE)  
    {  
        //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
             
        //add child sockets to set 
        for (int i = 0; i < max_clients; i++)
            if (data[i].getfd() == -1)
            {
                client_socket[i] = 0;
                data[i].setfd(client_socket[i]);
                continue;
            }
          
        for ( i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
             
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
            if (server.getcurrent_user() == max_clients)
            {
                send(new_socket, "\033[1;31mServer is full try again later.\033[0m\n", strlen("\033[1;31mServer is full try again later.\033[0m\n"), 0);
                close(new_socket);
                continue;
            }
            //inform user of socket number - used in send and receive commands 
            typeWriter("\033[38;5;120mNew connection , socket fd is " + to_string(new_socket) + ", ip is : " + inet_ntoa(address.sin_addr) + ", port : " + to_string(ntohs(address.sin_port)) + "\033[0m\n"); 
           
            //send new connection greeting message 
            if(send(new_socket, message, (ssize_t)strlen(message), 0) != (ssize_t)strlen(message) == 0)
            {  
                typeWriter("Welcome message sent successfully\n");  
                if (send(new_socket, "Please enter password:\n", 24, 0) != 24)
                    perror("send");
                typeWriter("Password asked to user: #" + to_string(new_socket) + "\n");    
            }
                else
                    perror("send");
                 
            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if(client_socket[i] == 0 )  
                {  
                    client_socket[i] = new_socket;  
                    typeWriter("Adding to list of sockets as " + to_string(i) + "\n");
                    server.setcurrent_user(server.getcurrent_user() + 1);
                    break;  
                }
            }  
        }  
         
        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)  
        {  
            sd = client_socket[i];
            if (FD_ISSET( sd , &readfds))  
            { 
                //Check if it was for closing , and also read the 
                //incoming message 
                //if ((valread = recv(sd, buffer, 1024, MSG_TRUNC)) == 0)  
                if ((valread = read(sd, buffer, 1025)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    printf("\033[38;5;208mUser #%d disconnected , ip %s , port %d \033[0m\n", sd, inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                    //Close the socket and mark as 0 in list for reuse
                    server.setcurrent_user(server.getcurrent_user() - 1);
                    if (data.at(sd - 4).getlog() == LOG_COMPLETED)
                    {
                        user_left(&data, &channels, sd, data.at(sd - 4).getchannel());
                        reset_client(&data[sd - 4], &server);
                    }
                    else if (data.at(sd - 4).getlog() == LOGGED || data.at(sd - 4).getlog() == LOGGED_MAYBE)
                        reset_client(&data[sd - 4], &server); 
                    close( sd );  
                    client_socket[i] = 0;
                }    
                //Parse the incoming input
                else
                {
                    //set the string terminating NULL byte on the end of the data 
                    try
                    {
						if (data.at(sd - 4).getIRSSI() == 1)
							buffer[valread - 1] = '\0';
						else
							buffer[valread] = '\0';
                        string input(buffer, strlen(buffer) - 1);

                        if (parse_log(input, &server, &data[sd - 4], sd, &data) == 1)
                            continue;
                        if (data.at(sd - 4).getlog() == LOG_COMPLETED && data.at(sd - 4).getconnected() == DEFAULT)
                        {
                            default_channel(&data, &channels, sd);
                            continue;
                        }
                        if ((input == "/quit" || input == "/leave") && data.at(sd - 4).getlog() == LOG_COMPLETED)
                        {
                            server.setcurrent_user(server.getcurrent_user() - 1);
                            user_left(&data, &channels, sd, data.at(sd - 4).getchannel());
                            reset_client(&data[sd - 4], &server);
                            close(sd);  
                            client_socket[i] = 0;
                        }
                        if(data.at(sd - 4).getlog() == LOG_COMPLETED && data.at(sd - 4).getconnected() == INSIDE_CHANNEL && input.size() > 0)
                            parse_input(&data, &channels, sd, input, &server, &bot);
						
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
            }
        }  
    }  
    return ;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "\033[1;31mServer port and password is needed\033[0m" << endl;
        return 0;
    }
    else
    {
        try
        {
            if (ft_parsing(argv))
                return 1;
            IRC server(argv[1], argv[2]);
            start_server(server);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return 0;
}