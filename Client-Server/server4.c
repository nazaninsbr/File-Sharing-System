/****************** SERVER CODE ****************/
#include <fcntl.h>
 
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
		int welcomeSocket, newSocket;
		char buffer[1024];
		char textBuffer[4096];
		struct sockaddr_in serverAddr;
		struct sockaddr_storage serverStorage;
		socklen_t addr_size;

		/*---- Create the socket. The three arguments are: ----*/
		/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
		welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
		
		/*---- Configure settings of the server address struct ----*/
		/* Address family = Internet */
		serverAddr.sin_family = AF_INET;
		/* Set port number, using htons function to use proper byte order */
		serverAddr.sin_port = htons(7891);
		/* Set IP address to localhost */
		serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		/* Set all bits of the padding field to 0 */
		memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

		/*---- Bind the address struct to the socket ----*/
		bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

		while(1){
				/*---- Listen on the socket, with 5 max connection requests queued ----*/
				if(listen(welcomeSocket,5)==0)
					printf("Listening\n");
				else
					printf("Error\n");

				/*---- Accept call creates a new socket for the incoming connection ----*/
				addr_size = sizeof serverStorage;
				newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

				// Read data into buffer.  We may not have enough to fill up buffer, so we
		    // store how many bytes were actually read in bytes_read.
		    int fd = open("1.txt", O_WRONLY | O_APPEND);
		    if(fd <0){
		    	printf("error opening file\n");
		    }
		    int bytes_read = read(fd, textBuffer, sizeof(textBuffer));
		    if (bytes_read == 0){ // We're done reading from the file
		    		strcpy(buffer,"No Content\n");
    				send(newSocket,buffer,11,0);
		    }

		    if (bytes_read < 0) {
		        strcpy(buffer,"Error\n");
    				send(newSocket,buffer,6,0);
		    }
		    write(1, textBuffer, 4096);
		    // You need a loop for the write, because not all of the data may be written
		    // in one call; write will return how many bytes were written. p keeps
		    // track of where in the buffer we are, while we decrement bytes_read
		    // to keep track of how many bytes are left to write.
		    void *p = textBuffer;
		    while (bytes_read > 0) {
		        int bytes_written = write(newSocket, p, bytes_read);
		        if (bytes_written <= 0) {
		            strcpy(buffer,"Error\n");
    						send(newSocket,buffer,6,0);
		        }
		        bytes_read -= bytes_written;
		        p += bytes_written;
		    }
		}

		return 0;
}