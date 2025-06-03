#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
	socklen_t socket_address_len, client_address_len;
	struct sockaddr_in socket_address, client_address;
	char server_msg[256] = "Hello, server this side";
	int my_socket, bind_status;
	char buf[256];
	client_address_len = sizeof(client_address);

	my_socket = socket(AF_INET, SOCK_DGRAM, 0);

	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	socket_address.sin_port = htons(43000);
	socket_address_len = sizeof(socket_address);

	bind_status = bind(my_socket, (struct sockaddr *) &socket_address, socket_address_len);
	if (bind_status < 0) {
		perror("Bind Error\n");
		exit(EXIT_FAILURE);
	}
	
	recvfrom(my_socket, buf, sizeof(buf), 0, (struct sockaddr *) &client_address, &client_address_len);
	printf("Client: %s", buf);

	sendto(my_socket, server_msg, sizeof(server_msg), 0, (const struct sockaddr *) &client_address, client_address_len);

	close(my_socket);

	return 0;
}
