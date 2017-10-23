#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

unsigned short int get_port_number(){
	unsigned short int port;
	char buff[10];
	while(read(0, buff, sizeof(buff)>0)){
		write(1, buff, 1);
	}
	covert_charStar_to_int(buff);
	return port;
}

int main(){
	int sockfd;
	unsigned short int port_number;
	char ip[100];
	struct sockaddr_in my_addr;

	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	port_number = get_port_number();

	my_addr.sin_family = AF_INET;
	my_addr.sin_family = htons(port_number);
	my_addr.sin_addr.s_addr = inet_addr(ip);
	memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct

	return 0;
}