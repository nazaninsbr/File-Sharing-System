#include <stdio.h>
#include <sys/socket.h>

/*Once a long time ago, it was thought that maybe a address family (what the "AF" in "AF_INET" stands for) might support several protocols that were referenced by their protocol family (what the "PF" in "PF_INET" stands for).
That didn't happen. Oh well. So the correct thing to do is to use AF_INET in your struct sockaddr_in and PF_INET in your call to socket(). 
But practically speaking, you can use AF_INET everywhere. And, since that's what W. Richard Stevens does in his book, that's what I'll do here.
*/
int main(int argc, char *argv[]){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd<0){
		printf("Error opening socket\n");
	}
	else{
		printf("Able to open socket\n");
	}
	return 0;
}