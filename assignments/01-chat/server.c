#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

int main() {
	int my_socket, bind_status, client_socket;
	socklen_t server_address_len, client_address_len;
	struct sockaddr_in server_address, client_address;
	
	my_socket = socket(AF_INET, SOCK_STREAM, 0);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = htons(40000);
	server_address_len = sizeof(server_address);

	bind_status = bind(my_socket, (struct sockaddr *) &server_address, server_address_len);

	if (bind_status < 0) {
		perror("Bind Error\n");
		exit(EXIT_FAILURE);
	}

	listen(my_socket, 6);


	client_address_len = sizeof(client_address);
	char buf[100];
	client_socket = accept(my_socket, (struct sockaddr *) &client_address, &client_address_len);
	if (client_socket < 0) {
		perror("Accept Error\n");
		exit(EXIT_FAILURE);
	}		
	while (1) {
		read(client_socket, buf, sizeof(buf));
		printf("%s\n", buf);
		if (strcmp(buf, "exit") == 0) {
			write(client_socket, "exit", 4);	
			printf("Closing connection...\n");
			close(client_socket);
			break;
		} else {
			fgets(buf, sizeof(buf), stdin);
			write(client_socket, buf, sizeof(buf));
		}
	
	}

	close(client_socket);
	return 0;
}
