#include<sys/types.h> 
//example 1 
int main() {
int status;
char *array[]={"ls", "-l", "a.out"  ,0};

printf("Files in Directory are:\n"); 


if(fork()==0){
   execv("/bin/ls",array); 
}



 wait(&status);



}
