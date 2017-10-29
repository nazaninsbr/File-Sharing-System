/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

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
int readPortNumber(){
  char buff[10];
  char numbuff[1024];
  int place = 0;
  int n;
  write(1, "Port: ", 6);
  while( (n = read(0, buff, sizeof(buff)>0)) !=0){
    if(n==1 && (buff[0]=='\n'))
      break;
    numbuff[place] = buff[0];
    place++;
  }
  numbuff[place] = '\0';
  return convertCharPortToInt(numbuff, 1024, place);
}
//this function teads the ip using read()
void readIP(char* ip, int size){
  char buff[10];
  char ipbuff[16];
  int place = 0;
  int n;
  write(1, "IP: ", 3);
  while( (n = read(0, buff, sizeof(buff)>0)) !=0){
    if(n==1 && (buff[0]=='\n'))
      break;
    ipbuff[place] = buff[0];
    place++;
  }
  ipbuff[place] = '\0';
  strcpy(ip, ipbuff);
}
void clientConnect(){
  int clientSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  


  //reading the port number from stdin
  int port_number = readPortNumber();
  //I considered the maximum length of the ip to be \0xxx.yyy.zzz.ttt
  //making it 15 bits
  char ip[16];
  //reading the ip from the stdin
  readIP(ip, sizeof(ip));


  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(port_number);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr(ip);
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  /*---- Read the message from the server into the buffer ----*/
  recv(clientSocket, buffer, 1024, 0);

  /*---- Print the received message ----*/
  printf("Data received: %s",buffer);
}
int main(){
    clientConnect();
    return 0;
}