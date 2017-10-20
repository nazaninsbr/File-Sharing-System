#include <unistd.h>

int main(void){
	if (write(1, "Please fill in the following fields:\n", 37) != 37) {
        write(2, "There was an error writing to standard out\n", 44);
        return -1;
    }

    return 0;
}