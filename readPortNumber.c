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
int main(void){
	//reading the port number from stdin
	int port_number = readPortNumber();
}