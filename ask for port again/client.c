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
      //write(1, "Invalid Port Number\n", 20);
      //_exit(1);
      return -1;
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
void encode_get_part_message(char* msg, char* file){
  char part[5];
  memset(part, 0, sizeof(part));
  get_get_part_message(file, part);
  strcpy(msg, "g");
  strcat(msg, file);
  strcat(msg, "+");
  strcat(msg, part);
  strcat(msg,"+");
}
//This is a socket that only sends one message
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
void save_file_content(char* buffer, char* fileName){
    FILE *fp;

    fp=fopen(fileName, "a");
    if(fp==NULL){
      write(1, "Error opening or creating file\n", 31);
      _exit(1);
    }
    int x = fputs(buffer, fp);
    if(!(x>=0)){
      write(1, "Error writing to file\n", 22);
      _exit(1);
    }
    int y = fclose(fp);
    if(y!=0){
      write(1, "Error closing file\n", 19);
      _exit(1);
    }
}
void connect_to_the_mini_server(){
    int clientSocket;
    char buffer[BUFSIZE];
    char file[100];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char ip[16];
    memset(ip, 0, sizeof(ip));
    write(1, "Port of the miniServer you want to connect to: ", 47);
    int port = readNumber();
    write(1, "IP: ", 4);
    readString(ip, sizeof(ip));
    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;
  
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
    encode_get_part_message(buffer, file);
    send(clientSocket, buffer, sizeof(buffer), 0);
    recv(clientSocket, buffer, 1024, 0);
    write(1, "Got file content:\n", 18);
    write(1, buffer, sizeof(buffer));
    save_file_content(buffer, file);
    write(1, "\n", 1);
    close(clientSocket);
}
void clientConnect(ThisSystem** mySystem){
  int clientSocket;
  char buffer[BUFSIZE];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  char file[100];
  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons((*mySystem)->port);
  serverAddr.sin_addr.s_addr = inet_addr((*mySystem)->ip);
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  
  while(1){
      connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
      memset(file, 0, sizeof(file));
      memset(buffer, 0, sizeof(buffer));
      encode_get_part_message(buffer, file);
      send(clientSocket, buffer, sizeof(buffer), 0);
      recv(clientSocket, buffer, 1024, 0);
      if(buffer[0]=='*'){
          char ans[2];
          write(1, buffer, sizeof(buffer));
	      if(buffer[1]=='F'){
          write(1, "Do you want to connect to that port now?Y or N ", 47);
          read(0, ans, 2);
          if(ans[0]=='Y'){
            write(1, "Going to the other socket.\n", 27);
            connect_to_the_mini_server();
            write(1, "Back to the main server\n", 24);
         }
        }
      }
      else{
        write(1, "Got file content:\n", 18);
        write(1, buffer, sizeof(buffer));
        save_file_content(buffer, file);
        write(1, "\n", 1);
        memset(buffer, 0, sizeof(buffer));
      }
  }
}
int iSaDigitOrDot(char c){
  if(c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9' || c=='0' || c=='.' || c==' ' ||  c=='\n' || c=='\0')
    return 1;
  return 0;
}
int checkIP(char* ip){
  for(int i=0; i<sizeof(ip); i++){
    if(iSaDigitOrDot(ip[i])==0){
      return 0; 
    }
  }
  return 1;
}
int main(){
    ThisSystem* mySystem = (ThisSystem*)malloc(sizeof(ThisSystem)); 
    char ip[16];
    memset(ip, 0, sizeof(ip));
    //memset(mySystem->ip, 0, sizeof(mySystem->ip));
    do{
      write(1, "Port: ", 6);
      mySystem->port = readNumber();
    }while(mySystem->port==-1);
    do{
      memset(ip, 0, sizeof(ip));
      write(1, "IP: ", 3);
      readString(ip, sizeof(ip));
      strcpy(mySystem->ip, ip);
    }while(checkIP(ip)==0);
    clientConnect(&mySystem);
    return 0;
}
