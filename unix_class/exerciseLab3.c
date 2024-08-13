#include <sys/types.h>  
#include <signal.h>
#include <unistd.h>
  
static void sig_usr(int signo) ;
static void wake_up(int signo) ;
int fd[2];//make 2 fd's
int counter =0;

int main(void)
{
  char str[]="hello friend\n";
  int i;
  pid_t child1;
  pipe(fd);              //create pipe 
  child1=fork();//make 2 processes
  if(signal(SIGUSR1, sig_usr)== SIG_ERR)//trap
	perror("can't catch SIGUSER1");              

  if(0==child1)//we are child
    {
      close(fd[1]); //close write side (this is not actually required)
      for(;;)
	{
	  printf("child is running\n");
      	  pause();//wait for signal
	}
    }
  else      //we are parent
    {
      if(signal(SIGUSR2, wake_up)== SIG_ERR)//trap
	perror("can't catch SIGUSER2");              
      
      close(fd[0]); //close read side(also not really required)
      while(1)
	{
	  sleep(2);//avoid race (very important, otherwise the 
	           //father will kill the child before it had a chance to 
	           // set up its signal trap)
	  write(fd[1],str,strlen(str));   
	  kill(child1, SIGUSR1);
	  pause();//wait for child to finish
	          //This is very important, otherwise the 
	          //father will run ahead in loop before child finishes.
	          //This would cause a new SIGUSR1 to be sent which
	          //would behave in its default behavior and kill the child.
	}//end while
    }//end dad
}


static void sig_usr(int signo) /*argument is signal number*/
{

  char ch[100];
  int rd;
  printf("child received SIGUSR1.  I am %d.\n", getpid() );
  rd = read(fd[0],ch,100);      //read from the pipe 100 characters (maximum)
  ch[rd]='\0';
  printf("%s \n",ch);

  kill(getppid(), SIGUSR2);//wake up father
}
static void wake_up(int signo) 
{
  //do nothing

}




