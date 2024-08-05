#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
void main() 
{ 
int fd, number_read_in=10; 
char buffer[50];
 int pd[2];
 pipe(pd); 
fd= open("./file.txt", O_RDONLY);//open file for read only 
if(fd<0)//if we fail to open the file 
{ printf("file not opened"); exit( 1); } //now we will read the contents 
//of the file 

 while (number_read_in){
number_read_in = read(fd,buffer,49); //size of buffer is 256 
buffer[number_read_in]=NULL;//so the printf will work 

printf("number read: %d \n", number_read_in); 
printf("buffer: %s\n", buffer);

 }
close(fd); 

 }
