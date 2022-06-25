#include <unistd.h>
#include <arpa/inet.h> //inet address
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 

//client-server chat function 
void function(int socket_desc) 
{ 
	char buffer[80]; 
	int i; 
	
	// infinite loop 
	for (;;)
	{ 
		bzero(buffer, 80); 

		// read message in buffer 
		read(socket_desc, buffer, sizeof(buffer));
 
		// print buffer with client's message
		printf("Client: %sYOU   : ", buffer); 
		bzero(buffer, 80); 
		i = 0;
 
		// copy message in buffer 
		while ((buffer[i++]= getchar()) != '\n'); 

		// send buffer to client 
		write(socket_desc, buffer, sizeof(buffer)); 

		// "exit" to end chat and server exit 
		if (strncmp("exit", buffer, 4) == 0)
		{ 
			printf("\nServer left the chat...\n"); 
			printf("--SEE YOU SOON--\n\n"); 
			break; 
		} 
	} 
}


int main() 
{ 
	int socket_desc, new_socket, c; 
	struct sockaddr_in server, client; 

	//create socket 
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); 
	if (socket_desc == -1)
	{ 
		printf("Failed to create socket.\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created.\n"); 

	bzero(&server, sizeof(server)); 

	//IP, family, port
	server.sin_family = AF_INET; 
	server.sin_addr.s_addr = INADDR_ANY; 
	server.sin_port = htons(8888); 

	// bind socket to IP 
	if ((bind(socket_desc, (struct sockaddr*)&server, sizeof(server))) != 0)
	{ 
		printf("Bind failed.\n"); 
		exit(0); 
	} 
	else
		printf("Bind is successful.\n"); 

	//Listen
	if ((listen(socket_desc, 5)) != 0)
	{ 
		printf("Listen failed.\n"); 
		exit(0); 
	} 
	else
		printf("Listening...\n"); 

	c = sizeof(client); 

	// accept connection and data from client  
	new_socket = accept(socket_desc, (struct sockaddr*)&client, &c); 
	if (new_socket < 0)
	{ 
		printf("Failed to acccept connection from client.\n"); 
		exit(0); 
	} 
	else
	{
		printf("Connection acccepted. To start a chat, please send a response message.\n");
		printf("--WELCOME TO CHAT APP--\n\n");
		printf("Enter [exit] to close the server and chat. \n\n---CHAT---\n"); 
	}

	//client-server chat function 
	function(new_socket); 

	//close socket 
	close(socket_desc); 
} 
