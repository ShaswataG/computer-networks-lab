
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

int main() {
	
	int connection_status;
	socklen_t socket_addr_len;
	int my_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	
	char server_message[256];

	
	struct sockaddr_un socket_address;
	socket_address.sun_family = AF_UNIX;
	strcpy(socket_address.sun_path, "my_address");
	socket_addr_len = sizeof(socket_address);
	
	connection_status = connect(my_socket, (struct sockaddr* ) &socket_address, socket_addr_len);

	if (connection_status) {
		printf("Error: failed to connect to socket server\n");
	}

	char ch = 'A';

	write(my_socket, &ch, 1);

	read(my_socket, &ch, 1);

	printf("Server: %c\n", ch);

	close(my_socket);

	return 0;
}
