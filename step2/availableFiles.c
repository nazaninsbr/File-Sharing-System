#include <unistd.h>

struct FilePart{
	int part; 
	char fileDest[100];
	struct filePart* next;
};
struct File{
	char fileName[100];
	char ip[16];
	int port;
	struct filePart* next;
};
void makeList(struct File* head){
	head = (struct File*)malloc(sizeof(struct File));
}
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
int convertCharArrayToInt(char *buff, int size, int numOfRead){
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
int readUserInputNumber(){
	char buff[10];
	char numbuff[1024];
	int place = 0;
	int n;
	while( (n = read(0, buff, sizeof(buff)>0)) !=0){
		if(n==1 && (buff[0]=='\n'))
			break;
		numbuff[place] = buff[0];
		place++;
	}
	numbuff[place] = '\0';
	return convertCharArrayToInt(numbuff, sizeof(numbuff), place);
}
void readUserInput(char* ip, int size){
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
void getAvailableResources(struct File* head){
	int counter = 0;
	struct File availableParts[100];
	char fileName[100];
	int partNumber;
	do{
		write(1, "Available File Name: (Enter 0 to finish entering availabe resources) ", 69);
		fileName = readUserInput();
		write(1, "Available Part Number: (Enter 0 to finish entering availabe resources) ", 71);
		partNumber = readUserInputNumber();
		if(! fileStructExists(fileName, sizeof(fileName))){
			availableParts[counter] = createFileStruct(fileName, sizeof(fileName))
			struct FilePart newFilePart = createFilePartStruct(partNumber, fileName, sizeof(fileName));
			availableParts[counter].next = newFilePart;
		}
		else{
			int x = whereDoesPartFit(partNumber, fileName, sizeof(fileName));
		}
		counter +=1;
	}while(readInput!='0' && partNumber!=0));
}
int main(){
	struct File* head;
	makeList(head);
	getAvailableResources(head);
}