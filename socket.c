#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
/*added to solve this warning:
	implicit declaration of function 'inet_addr' is invalid
      in C99 [-Wimplicit-function-declaration]
*/

#include <arpa/inet.h>

#define MYPORT 3490

int main()
{
    int sockfd;
    struct sockaddr_in my_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    my_addr.sin_family = AF_INET;         // host byte order
    my_addr.sin_port = htons(MYPORT);     // short, network byte order
    my_addr.sin_addr.s_addr = inet_addr("10.12.110.57");
    memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the struct

    printf("%d\n", bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)));
}