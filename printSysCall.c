#include <unistd.h>

/*ssize_t write(int fildes, const void *buf, size_t nbytes)*/
/*
	int fildes


	The file descriptor of where to write the output. You can either use a file descriptor obtained from the open system call, 
	or you can use 0, 1, or 2, to refer to standard input, standard output, or standard error, respectively.

*/
/*
	const void *buf


	A pointer to a buffer of at least nbytes bytes, which will be written to the file.
*/
/*
	size_t nbytes

	The number of bytes to write. If smaller than the provided buffer, the output is truncated.

*/

int main(void){
	if (write(1, "This will be output to standard out\n", 36) != 36) {
        write(2, "There was an error writing to standard out\n", 44);
        return -1;
    }
 
    //example of an error due to the fact that the buffer size is bigger than we have given as an argument
    if (write(1, "This will be output to standard out\n", 10) != 36) {
        write(2, "There was an error writing to standard out\n", 44);
        return -1;
    }

    return 0;
}