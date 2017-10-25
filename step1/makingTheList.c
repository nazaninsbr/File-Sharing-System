#include <stdio.h>
#include <stdlib.h>

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
int main(){
	struct File* head;
	makeList(head);
}