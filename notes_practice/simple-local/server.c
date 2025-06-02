#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/un.h>
#include<sys/types.h>
#include<sys/socket.h>

int main() {

	int bind_status;
	socklen_t server_addr_len;
	socklen_t client_addr_len;

	char client_message[256];
	
	unlink("my_address");
	
	int my_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	int client_socket;
	
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	

	server_address.sun_family = AF_UNIX;
	

	strcpy(server_address.sun_path, "my_address");
	server_addr_len = sizeof(server_address);

	bind_status = bind(my_socket, (struct sockaddr *) &server_address, server_addr_len);

	if (bind_status == -1) {
		perror("Bind Error\n");
		exit(EXIT_FAILURE);
	}

	listen(my_socket, 4);

	for (int i = 0; i < 5; i++) {

		client_addr_len = sizeof(client_address);

		client_socket = accept(my_socket, (struct sockaddr *) &client_address, &client_addr_len);
		

		if (client_socket == -1) {
			perror("Accept Error]n");
			exit(EXIT_FAILURE);
		}
		
		char ch;

		read(client_socket, &ch, 1);
		ch++;
		write(client_socket, &ch, 1);

		close(client_socket);

	}

	close(my_socket);

	return 0;

}
