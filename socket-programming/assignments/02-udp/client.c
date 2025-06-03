#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main() {
	struct sockaddr_in server_address;
	socklen_t server_address_len;
	int my_socket, send_status, recv_status;
	char client_msg[256] = "Hello, client this side\n";
	char buf[256] = "";

	my_socket = socket(AF_INET, SOCK_DGRAM, 0);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = htons(43000);
	server_address_len = sizeof(server_address);

	send_status = sendto(my_socket, client_msg, sizeof(client_msg), 0, (const struct sockaddr *) &server_address, server_address_len);
	if (send_status < 0) {
		perror("Send Error\n");
		exit(EXIT_FAILURE);
	}
	
	recv_status = recvfrom(my_socket, buf, sizeof(buf), 0, (struct sockaddr *) &server_address, &server_address_len);
	printf("Server: %s\n", buf);

	close(my_socket);

	return 0;
}

