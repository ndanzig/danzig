#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define SONS 3
#define READ_SIZE 100

pid_t pid[SONS]={1,1,1};
char buff[READ_SIZE];
char buff2[READ_SIZE];
int i, file_read, pd[2];


static void sig_usr1(int signo) ;
static void sig_term(int signo) ;

int main(void)
{

  pipe(pd);


  for(i=0;i<SONS;i++)
    {
      pid[i]=fork();
      if(!pid[i])
	break;
    }
  
  if(pid[0]&&pid[1]&&pid[2])//abba
    {
      if (signal(SIGTERM, sig_term) == SIG_ERR)
	perror("can't catch SIGTERM\n");
      //      close(pd[1]);//close write side

      while(1)
	{
	  if(!(pid[0]||pid[1]||pid[2]))
	    {
	      printf("All sons are dead, self-terminating...\n");
	      return 0;
	    }
	  
	  scanf("%d%s",&i,buff);

	  if (i>2 || i<0 )
	    {
	    printf("no such son!\n");
	    continue;
	    }	  
	  if(!strcmp(buff,"quit"))
	    {
	      close(pd[0]);
	      raise(SIGTERM);
	    }
	  else if(!strcmp(buff,"kill"))
	    {
	      if(pid[i])
		{
		  kill(pid[i],SIGTERM);
		  printf("Son %d terminated.\n",i);
		  pid[i]=0;
		}
	      else
		printf("Son %d is already dead.\n",i);
	    }

	  else
	    {
	      if(pid[i])
		{
		  write(pd[1],buff,strlen(buff));
		  kill(pid[i],SIGUSR1);
		  sleep(1);
		}
	      else
		printf("Son %d is dead.\n",i);
	    }
	}
      
      

    }
  else
    {
      close(pd[1]);
      //printf("I'm a son\n");
      while(1)
	{
	  if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
	    perror("can't catch SIGUSR1\n");
	  pause();
	}
    }
}



//our trap function
static void sig_usr1(int signo) /*argument is signal number*/
{
  int size; 
 printf("Son %d: ",i);
  size=read(pd[0],buff2,READ_SIZE);
  buff2[size]=0;
  printf("%s",buff2);
  printf("\n");
  return;
}



//our trap function
static void sig_term(int signo) /*argument is signal number*/
{
  int j;
  printf("termination started");
  
  for(i=0;i<SONS;i++)
    kill(pid[i],SIGKILL);
  
  /*  signal(SIGTERM,SIG_DFL);
  for( j=0;j<3;j++)
    {
      printf(".");
	sleep(1);
    }
  printf("\n");
  printf("termination complete\n");
  */
  raise(SIGTERM);
        
  return;
}
