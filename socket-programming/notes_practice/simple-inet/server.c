#include<stdio.h>

#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main() {

	int server_socket;
	socklen_t server_address_len;
	int bind_status;
	int accept_status;
	struct sockaddr_in server_address;
	
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = htons(44330);

	server_address_len = sizeof(server_address);

	bind_status = bind(server_socket, (struct sockaddr *) &server_address, server_address_len);

	if (bind_status == -1) {
		perror("Bind Error\n");
		exit(EXIT_FAILURE);
	}
	
	listen(server_socket, 6);

	while (1) {
		
		struct sockaddr_in client_address;
		socklen_t client_address_len;
		int client_socket;
		char ch;	

		client_address_len = sizeof(client_socket);
		client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_address_len);
		
		if (client_socket == -1) {
			perror("Accept Error\n");
			exit(EXIT_FAILURE);
		}
		

		read(client_socket, &ch, 1);
		ch++;
		write(client_socket, &ch, 1);

		close(client_socket);
	}

	close(server_socket);

	return 0;
}
