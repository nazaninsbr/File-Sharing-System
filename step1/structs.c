struct filePart{
	int part; 
	char fileDest[100];
	struct filePart* next;
};

struct file{
	char fileName[100];
	char ip[16];
	int port;
	struct filePart* next;
};