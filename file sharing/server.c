
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define BUFSIZE 1024
#define FILEBUFF 10000
//the stuct to keep file part info
typedef struct File{
	char fileName[100];
	char ip[16];
	int port;
	int part;
	struct File* nextFile;
}File;
typedef struct ThisSystem{
	char ip[16]; 
	int port;
}ThisSystem;
char intToCharDigit(int c){
	char ret; 
	switch(c){
		case 0:
			ret = '0'; 
			break;
		case 1:
			ret = '1'; 
			break;
		case 2:
			ret = '2'; 
			break;
		case 3:
			ret = '3'; 
			break;
		case 4:
			ret = '4'; 
			break;
		case 5:
			ret = '5'; 
			break;
		case 6:
			ret = '6'; 
			break;
		case 7:
			ret = '7'; 
			break;
		case 8:
			ret = '8'; 
			break;
		case 9:
			ret = '9'; 
			break;
		default:
			ret = '-';
			break;

	}
	return ret;
}
void reverse_string(char* str){
	char temp;
	int i = 0;
    int j = strlen(str) - 1;
 
   	while (i < j) {
      	temp = str[i];
      	str[i] = str[j];
      	str[j] = temp;
      	i++;
      	j--;
    }
}
void intToCharString(int x, char* charEq){
	int a; 
	int counter = 0; 
	while(x>0){
		a = x%10; 
		charEq[counter] = intToCharDigit(a);
		if(charEq[counter]=='-'){
			write(1, "Invalid Port Number\n", 20);
			_exit(1);
		}
		x = x - x%10; 
		x = x/10;
		counter +=1;
	}
	reverse_string(charEq);
}
void print_node_info(File** curr){
	char port[10]; 
	char part[10]; 
	intToCharString((*curr)->part, part);
	intToCharString((*curr)->port, port);
	write(1, "File Name: ", 11); 
	write(1, (*curr)->fileName, sizeof((*curr)->fileName));
	write(1, " Part: ", 7);
	write(1, part, sizeof((*curr)->part));
	write(1, " available at port: ", 20);
	write(1, port, sizeof((*curr)->port)); 
	write(1, " ip: ", 5);
	write(1, (*curr)->ip, sizeof((*curr)->ip));
	write(1, "\n", 1);
}
void make_file_info_message(File** curr, char* buff){
	char port[10]; 
	char part[10]; 
	memset(part, 0, sizeof(part));
	memset(port, 0, sizeof(port));
	intToCharString((*curr)->part, part);
	intToCharString((*curr)->port, port);
	strcpy(buff, "*File Name: ");
	strcat(buff, (*curr)->fileName);
	strcat(buff, " Part: ");
	strcat(buff, part);
	strcat(buff, " available at port: ");
	strcat(buff, port);
	strcat(buff, " and IP: ");
	strcat(buff, (*curr)->ip);
	strcat(buff, "\n");
}
//This function gets a char digit and returns the int value 
//if the char is not a digit it returns -1
int charDigitToInt(char c){
	int ret; 
	switch(c){
		case '0':
			ret = 0; 
			break;
		case '1':
			ret = 1; 
			break;
		case '2':
			ret = 2; 
			break;
		case '3':
			ret = 3; 
			break;
		case '4':
			ret = 4; 
			break;
		case '5':
			ret = 5; 
			break;
		case '6':
			ret = 6; 
			break;
		case '7':
			ret = 7; 
			break;
		case '8':
			ret = 8; 
			break;
		case '9':
			ret = 9; 
			break;
		default:
			ret = -1;
			break;

	}
	return ret;
}
int convertCharArrayToInt(char* arr, int size){
	int converted = 0;
	int pow = 1;
	int base = 10;
	for(int position = 0; position<size; position++){
		int temp = charDigitToInt(arr[position]);
		if(temp==-1){
			write(1, "Invalid Port Number\n", 20);
			_exit(1);
		}
		converted += temp*pow;
		pow *= base;
	}
	return converted;
}
//This function gets a char array and returns the int equivalent
int convertCharPortToInt(char *buff, int size, int numOfRead){
	int converted = 0;
	int pow = 1;
	int base = 10;
	for(int position = numOfRead -1; position>=0; position--){
		int temp = charDigitToInt(buff[position]);
		if(temp==-1){
			write(1, "Invalid Port Number\n", 20);
			_exit(1);
		}
		converted += temp*pow;
		pow *= base;
	}
	return converted;
}
//This function reads the port number using read()
//then passes it to another function to be converted into int
int readNumber(){
	char buff[10];
	char numbuff[1024];
	int place = 0;
	int n;
	memset(buff, 0, sizeof(buff));
	memset(numbuff, 0, sizeof(numbuff));
	while( (n = read(0, buff, sizeof(buff)>0)) !=0){
		if(n==1 && (buff[0]=='\n'))
			break;
		numbuff[place] = buff[0];
		place++;
	}
	numbuff[place] = '\0';
	return convertCharPortToInt(numbuff, 1024, place);
}
//This function teads the ip using read()
void readString(char* ip, int size){
	char buff[10];
	char ipbuff[16];
	int place = 0;
	int n;
	while( (n = read(0, buff, sizeof(buff)>0)) !=0){
		if(n==1 && (buff[0]=='\n'))
			break;
		ipbuff[place] = buff[0];
		place++;
	}
	ipbuff[place] = '\0';
	strcpy(ip, ipbuff);
}
void *get_in_addr(struct sockaddr *sa){
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
File* search_for_file(File** head, char* name, int size, int part){
	File* curr = (*head);
	while(curr!=NULL){
		if(strcmp(curr->fileName,name)==0){
			if(curr->part==part)
				return curr;
		}
		curr = curr->nextFile;
	}
	return NULL;
}
void add_file_part(File** head, int _port, int _part, char* name, int size, char* ip, int sizeIP){
	File* newfile; 
	File* curr;
	curr = (struct File*)malloc(sizeof(struct File));
	newfile = (struct File*)malloc(sizeof(struct File));
	curr= (*head);
	//fill the data for the new node
	strcpy(newfile->fileName, name);
	strcpy(newfile->ip, ip);
	newfile->port = _port; 
	newfile->part = _part;
	newfile->nextFile = NULL;
	while(curr!=NULL){
		if(curr->nextFile!=NULL)
			curr = curr->nextFile;
		else 
			break;
	}
	curr->nextFile = newfile;
}
/*
	the whole thing is 256 chars and we will order it like this:
	<garbage>+<file part: 5>+<file name:100>+<port number: 5>+<ip:16>i
	i stands for info
*/
void encode_resources(File** curr, char* buff){	
	char temp[256];
	char port[5];
	char part[5];
	intToCharString((*curr)->port, port);
	intToCharString((*curr)->part, part);
	strcpy(temp, "i");
	strcat(temp, (*curr)->ip);
	strcat(temp, "+");
	strcat(temp, port);
	strcat(temp, "+");
	strcat(temp, (*curr)->fileName);
	strcat(temp, "+");
	strcat(temp, part);
	strcat(temp, "+");
	strcat(temp, "\0");

	strcpy(buff, temp);
}
int iSaDigitOrDot(char c){
	if(c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9' || c=='0' || c=='.' || c==' ')
		return 1;
	return 0;
}
void decode_Resource_from_socket(File** head, char* resourceString, int size){
	int _part, _port; 
	char ip[16];
	char file[100];
	char partTemp[5];
	char portTemp[5];
	int stringcounter = 1;
	int ipcounter = 0;
	int pluscount=0;
	int portcounter =0;
	int filecounter=0;
	int partcounter =0;
	memset(ip, 0, sizeof(ip));
	memset(file, 0, sizeof(file));
	for(int i=1; i<size; i++){
		if(resourceString[i]=='+'){
			pluscount+=1;
			continue;
		}
		if(pluscount==5)
			break;
		if(pluscount==0){
			ip[ipcounter]=resourceString[i];
			ipcounter+=1;
			continue;
		}
		if(pluscount==1){
			portTemp[portcounter]=resourceString[i];
			portcounter+=1;
			continue;
		}
		if(pluscount==2){
			file[filecounter]=resourceString[i];
			filecounter+=1;
			continue;
		}
		if(pluscount==3){
			partTemp[partcounter]=resourceString[i];
			partcounter+=1;
			continue;
		}
	}
	for (int i = 0; i < sizeof(ip); i++){
		if(!iSaDigitOrDot(ip[i]))
			ip[i]='\0';
	}
	for (int i = 0; i < sizeof(partTemp); i++){
		if(!iSaDigitOrDot(partTemp[i]))
			partTemp[i]='\0';
	}
	for (int i = 0; i < sizeof(portTemp); i++){
		if(!iSaDigitOrDot(portTemp[i]))
			portTemp[i]='\0';
	}
	_port = convertCharArrayToInt(portTemp, portcounter);
	_part = convertCharArrayToInt(partTemp, partcounter);
	add_file_part(head, _port, _part, file, sizeof(file), ip, sizeof(ip));
}
void get_get_part_message(char* file, char* part){
	write(1, "The name of the file you want: ", 31);
	readString(file, sizeof(file));
	write(1, "Which part? ", 12);
	readString(part, sizeof(part));
}
/*
	we encode it like this
		g(which stands for get)<file name>+<part>+
*/
void encode_get_part_message(char* msg){
	char file[100];
	char part[5];
	memset(file, 0, sizeof(file));
	memset(part, 0, sizeof(part));
	get_get_part_message(file, part);
	strcpy(msg, "g");
	strcat(msg, file);
	strcat(msg, "+");
	strcat(msg, part);
	strcat(msg,"+");
}
int decode_get_part_message(char* msg, char* fileName){
	char file[100];
	char part[5];
	memset(file, 0, sizeof(file));
	memset(part, 0, sizeof(part));
	int filecounter = 0;
	int partcounter = 0;
	int pluscount=0;
	for(int i=1; i<sizeof(msg); i++){
		if(msg[i]=='+'){
			pluscount+=1;
			continue;
		}
		if(pluscount==2)
			break;
		if(pluscount==0){
			file[filecounter]=msg[i];
			filecounter+=1;
			continue;
		}
		if(pluscount==1){
			part[partcounter]=msg[i];
			partcounter+=1;
			continue;
		}
	}
	strcpy(fileName, file);
	int partN = convertCharArrayToInt(part, partcounter);
	return partN;
}
//This is a socket that only sends one message
void old_socket(){
	//variable decelerations
  	int welcomeSocket, newSocket;
  	char buffer[1024];
  	struct sockaddr_in serverAddr;
  	struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  

  //reading the port number from stdin
	int port_number = readNumber();
	//I considered the maximum length of the ip to be \0xxx.yyy.zzz.ttt
	//making it 15 bits
	char ip[16];
	//reading the ip from the stdin
	readString(ip, sizeof(ip));


  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(port_number);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr(ip);
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  /*---- Send message to the socket of the incoming connection ----*/
  strcpy(buffer,"Hello World\n");
  send(newSocket,buffer,13,0);
  recv(newSocket, buffer, 1024, 0);
  /*---- Print the received message ----*/
  printf("Data received: %s",buffer);
}
void get_available_resources(char* ip, int size, int port_number, File** head){
	char name[100]; 
	int part_number;
	write(1, "Enter 0 when you are done.\n", 27);
	do{
		memset(name, 0, sizeof(name));
		write(1, "File Name: ", 11);
		readString(name, sizeof(name));
		if(name[0]=='0')
			break;
		write(1, "Part Number: ", 13); 
		part_number = readNumber();
		if(part_number==0)
			break;
		add_file_part(head, port_number, part_number, name, sizeof(name), ip, sizeof(ip));
	}while(name[0]!='0' && part_number!=0);
}
void print_available_resources(File** head){
	File* curr = (*head); 
	if(curr==NULL){
		write(1, "No available resources\n", 23);
		return;
	}
	curr= curr->nextFile;
	while(curr!=NULL){
		print_node_info(&curr); 
		curr =  curr->nextFile;
	}
}
void set_up_linkedlist_head(File** head){
	(*head) = (struct File*)malloc(sizeof(struct File));
	(*head)->port = 0; 
	(*head)->part = 0;
	strcpy((*head)->fileName, "0");
	strcpy((*head)->ip, "0");
	(*head)->nextFile = NULL;
}
void read_and_write_file_content(char* fileName){
	char buffer [BUFSIZE]; 
  	int length; 
  	int fd; 
   
  	/* Open the file, print error message if we fail */
  	if ( ( fd = open (fileName, O_RDONLY) ) < 0 ) { 
    	write(1, "Error\n", 6);
    	return;
  	} 

  	/* Copy file contents to stdout, stop when read returns 0 (EOF) */
  	while ( (length = read (fd, buffer, BUFSIZE)) > 0 ) 
     	write (1, buffer, length); 

   	write(1, "\n", 1);
  	close (fd); 
}
void read_file_content(char* fileName, char* buff){
	char buffer [BUFSIZE]; 
  	int length; 
  	int fd; 
   
  	/* Open the file, print error message if we fail */
  	if ( ( fd = open (fileName, O_RDONLY) ) < 0 ) { 
    	write(1, "Error\n", 6);
    	return;
  	} 
  	strcpy(buff, "");
  	/* Copy file contents to stdout, stop when read returns 0 (EOF) */
  	while ( (length = read (fd, buffer, BUFSIZE)) > 0 ) 
  		strcat(buff, buffer);
}
int compare_ip_strings(char* ip1, char*ip2){
	if(sizeof(ip1)!=sizeof(ip2))
		return 0;
	int x=0; 
	while(x<sizeof(ip1)){
		if(ip1[x]==ip2[x])
			x+=1;
		else
			return 0;
	}
	return 1;
}
int handle_get_file(char* msg, File** head, ThisSystem** ourSystem, char* buff){
	char fileName[100];
	int part = decode_get_part_message(msg, fileName);
	File* curr; 
	curr = search_for_file(head, fileName, sizeof(fileName), part);
	if(curr==NULL)
		return -1;
	else{
		if( (curr->port==(*ourSystem)->port) && (compare_ip_strings(curr->ip, (*ourSystem)->ip)) ){
			read_file_content(fileName, buff);
		}
		else{
			make_file_info_message(&curr, buff);
		}
	}
	return 20;
}
void workWithSocket(File** head, ThisSystem** ourSystem){
	fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    int fdmax;        // maximum file descriptor number

    int listener;     // listening socket descriptor
    int newfd;        // newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;
    char outputbuff[BUFSIZE];
    char buf[256];    // buffer for client data
    int nbytes;

	char remoteIP[INET6_ADDRSTRLEN];

    int yes=1;        // for setsockopt() SO_REUSEADDR, below
    int i, j, rv;

	struct addrinfo hints, *ai, *p;

    FD_ZERO(&master);    // clear the master and temp sets
    FD_ZERO(&read_fds);

	// get us a socket and bind it
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	char port_char[10];
	memset(port_char, 0, sizeof(port_char));
	intToCharString((*ourSystem)->port, port_char);
	if ((rv = getaddrinfo((*ourSystem)->ip, port_char, &hints, &ai)) != 0) {
		write(1, "Error at geraddrinfo.\n", 22);
		_exit(1);
	}
	write(1, "No Error at geraddrinfo.\n", 25);
	for(p = ai; p != NULL; p = p->ai_next) {
    	listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0) { 
			continue;
		}
		
		// lose the pesky "address already in use" error message
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(listener);
			continue;
		}

		break;
	}

	// if we got here, it means we didn't get bound
	if (p == NULL) {
		fprintf(stderr, "selectserver: failed to bind\n");
		exit(2);
	}

	freeaddrinfo(ai); // all done with this

    // listen
    if (listen(listener, 10) == -1) {
        perror("listen");
        exit(3);
    }

    // add the listener to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one
    // main loop
    for(;;) {
        read_fds = master; // copy it
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }

        // run through the existing connections looking for data to read
        for(i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // we got one!!
                if (i == listener) {
                    // handle new connections
                    addrlen = sizeof remoteaddr;
					newfd = accept(listener,
						(struct sockaddr *)&remoteaddr,
						&addrlen);

					if (newfd == -1) {
                        perror("accept");
                    } else {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax) {    // keep track of the max
                            fdmax = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                            "socket %d\n",
							inet_ntop(remoteaddr.ss_family,
								get_in_addr((struct sockaddr*)&remoteaddr),
								remoteIP, INET6_ADDRSTRLEN),
							newfd);
                    }
                } else {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof buf, 0))) {
                    	if(nbytes>0){
                    		//we got resource information
                    		if(buf[0]=='i'){
                    			decode_Resource_from_socket(head, buf, sizeof(buf));
                    		}
                    		//we got file request
                    		if(buf[0]=='g'){
                    			handle_get_file(buf, head, ourSystem, outputbuff);
                    			send(i, outputbuff, sizeof(outputbuff), 0);
                    		}
                    	}
                        // got error or connection closed by client
                        else if (nbytes == 0) {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        } else {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    } else {
                        // we got some data from a client
                        for(j = 0; j <= fdmax; j++) {
                            // send to everyone!
                            if (FD_ISSET(j, &master)) {
                                // except the listener and ourselves
                                if (j != listener && j != i) {
                                    if (send(j, buf, nbytes, 0) == -1) {
                                        perror("send");
                                    }
                                }
                            }
                        }
                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors
    } // END for(;;)--and you thought it would never end!
}
int main(){
	ThisSystem* ourSystem = (ThisSystem*)malloc(sizeof(ThisSystem));
	write(1, "Port: ", 6);
	int port_number = readNumber();
	//I considered the maximum length of the ip to be \0xxx.yyy.zzz.ttt making it 16 bits
	char ip[16];
	memset(ip, 0, sizeof(ip));
	memset(ourSystem->ip, 0, sizeof(ip));
	//reading the ip from the stdin
	write(1, "IP: ", 3);
	readString(ip, sizeof(ip));

	strcpy(ourSystem->ip, ip); 
	ourSystem->port = port_number;

	File* head; 
	set_up_linkedlist_head(&head);
	get_available_resources(ip, sizeof(ip), port_number, &head);
	print_available_resources(&head);
	//old_socket();
	workWithSocket(&head, &ourSystem);
}