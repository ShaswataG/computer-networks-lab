#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main() {
	char server_msg[100];
	socklen_t socket_address_len;
	struct sockaddr_in socket_address;
	int my_socket, connection_status;

	my_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	socket_address.sin_port = htons(40000);
	socket_address_len = sizeof(socket_address);

	connection_status = connect(my_socket, (struct sockaddr *) &socket_address, socket_address_len);
	
	if (connection_status < -1) {
		perror("Connection Error\n");
	}
	
	while (1) {
		char buf[100];
		fgets(buf, sizeof(buf), stdin);
		write(my_socket, buf, sizeof(buf));
		read(my_socket, buf, sizeof(buf));
		if (strcmp(buf, "exit") == 0) {
			break;
		}
		printf("%s\n", buf);
	}
	printf("Closing socket...\n");
	close(my_socket);
	return 0;
}
