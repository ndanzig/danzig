#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>  
void main()
{
  int fd[2];
  pid_t pid;
  int status;
  char str[20];
  pipe(fd); //create pipe with two sides, [0] refering to one end [1] to the other
  switch(fork())
    {       
    case -1:
      printf("fork error\n");
      break;
    case 0:                    //child
      close(fd[0]);       //child only writes to pipe
      dup2(fd[1],1);       //write std out to pipe p[1]
      printf("hello my good friend\n");  //print to stdout will really      
      //go into the pipe.
      close(fd[1]);
      break;
    default:                         //father
      close(fd[1]);            //parent proccess only reads
      dup2(fd[0],0);           //read std input from pipe p[0]
      while(gets(str))    //get from pipe
 	{printf("We are in the father.\n");
	printf("%s\n",str);   //print to std out (the screen this time)
	}
      close(fd[0]);
    }               
} 
