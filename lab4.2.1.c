#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        int socket_desc, new_socket, c;
        struct sockaddr_in server, client;

        //create socket
        socket_desc= socket(AF_INET, SOCK_STREAM, 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }

        //prepare sockaddr in struct
        server.sin_family= AF_INET;
        server.sin_addr.s_addr= INADDR_ANY;
        server.sin_port= htons(8888);

        //bind
        if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
        {
                puts("Bind failed");
        }
        puts("Bind done\n");

        //listen
        listen(socket_desc, 3);

        //accept incoming connections
        puts("Waiting for incoming connections.........");
        c= sizeof(struct sockaddr_in);
        while (new_socket= accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)){
		if (new_socket < 0)
        	{
                	perror("Accept failed.");
        	}
                puts("Connection accepted.\n");
        }
	
	return 0;
}
