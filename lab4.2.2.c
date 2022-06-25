#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>  //inet addr
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        int socket_desc, new_socket, c;
        struct sockaddr_in server, client;
        char *message, client_reply[2000];

        //create socker
        socket_desc= socket(AF_INET, SOCK_STREAM, 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }

        //prepare sockaddr in structure
        server.sin_family= AF_INET;
        server.sin_addr.s_addr= INADDR_ANY;
        server.sin_port= htons(8888);

        //bind
        if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
        {
                puts("Bind failed");
        }
        puts("Bind done");

        //listen
        listen(socket_desc, 3);

        //accept incoming connection
        puts("Waiting for incoming connections…");
        c= sizeof(struct sockaddr_in);

        while((new_socket= accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)))
        {
                puts ("Connection accepted");

                //message from client
                recv(new_socket, client_reply, 2000, 0);
                puts(client_reply);

                //reply to client
                message = "Hi client, I have accepted your connection :)\n";
                write(new_socket, message, strlen(message));
        }
        if(new_socket < 0)
        {
                perror("accept failed");
                return 1;
        }

        //close(socket_desc);
        return 0;
}
