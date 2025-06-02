#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

int main() {
	int client_socket;
	int connection_status;
	socklen_t socket_len;
	struct sockaddr_in socket_address;
	char ch = 'A';

	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	socket_address.sin_port = htons(44330);
	socket_len = sizeof(socket_address);

	connection_status = connect(client_socket, (struct sockaddr *) &socket_address, socket_len);

	if (connection_status == -1) {
		perror("Connection Error\n");
		exit(EXIT_FAILURE);
	}

	write(client_socket, &ch, 1);
	read(client_socket, &ch, 1);

	printf("Server: %c\n", ch);


	close(client_socket);

	return 0;
}
