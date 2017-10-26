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
	struct File* nextFile;
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
void readUserInput(char* fileName, int size){
	char buff[10];
	char fileNamebuff[16];
	int place = 0;
	int n;
	while( (n = read(0, buff, sizeof(buff)>0)) !=0){
		if(n==1 && (buff[0]=='\n'))
			break;
		fileNamebuff[place] = buff[0];
		place++;
	}
	fileNamebuff[place] = '\0';
	strcpy(fileName, fileNamebuff);
}
int fileStructExists(struct File* head, char* fileName, int size){
	struct File* curr = head;
	while(curr!=NULL){
		if(curr->fileName == fileName){
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}
void createFileStruct(struct File* head, char* fileName, int size){
	struct File* newfile;
	strcpy(newfile->fileName, fileName);
	strcpy(newfile->ip, head->ip);
}
struct FilePart* createFilePartStruct(int part, char* fileName, int size){
	struct FilePart* newFilePart;
	newFilePart->part = part;
	strcpy(newFilePart->fileDest, fileName);
	return newFilePart;
}
void getAvailableResources(struct File* head){
	int counter = 0;
	char fileName[100];
	int partNumber;
	do{
		write(1, "Available File Name: (Enter 0 to finish entering availabe resources) ", 69);
		readUserInput(fileName, sizeof(fileName));
		write(1, "Available Part Number: (Enter 0 to finish entering availabe resources) ", 71);
		partNumber = readUserInputNumber();
		if(! fileStructExists(head, fileName, sizeof(fileName))){
			createFileStruct(head, fileName, sizeof(fileName));
			struct FilePart* newFilePart = createFilePartStruct(partNumber, fileName, sizeof(fileName));
		}
		// else{
		// 	int x = whereDoesPartFit(partNumber, fileName, sizeof(fileName));
		// }
		counter +=1;
	}while(fileName!="0" && partNumber!=0);
}
void printAvailableResources(struct File* head){
	struct File* curr = head;
	struct FilePart* thisPart;
	while(curr!=NULL){
		write(1, curr->fileName, sizeof(curr->fileName));
		write(1, " : ", 3);
		thisPart = curr->next;
		while(thisPart!=NULL){
			write(1, thisPart->part, sizeof(thisPart->part));
			write(1, ", ", 2);
			thisPart = thisPart->next;
		}
		write(1, "\n", 1);
		curr = curr->nextFile;
	}
}
int main(){
	struct File* head;
	makeList(head);
	getAvailableResources(head);
	printAvailableResources(head);
}