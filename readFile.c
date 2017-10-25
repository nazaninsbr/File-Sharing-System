#include <unistd.h> 
#include <fcntl.h> 
#define BUFSIZE 1024 
int main () 
{ 
  char buffer [BUFSIZE]; 
  int length; 
  int fd; 
   
  /* Open the file, print error message if we fail */
  if ( ( fd = open ("2.txt", O_RDONLY) ) < 0 ) { 
    write(1, "Error\n", 6);
    return 1;
  } 

  /* Copy file contents to stdout, stop when read returns 0 (EOF) */
  while ( (length = read (fd, buffer, BUFSIZE)) > 0 ) 
     write (1, buffer, length); 

   write(1, "\n", 1);
  close (fd); 
  return 0; 
}