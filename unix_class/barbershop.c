
//by Nachum Danzig
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#define COUNT 6



#define SEM_MODE 0600 //( SEM_R  | SEM_A )

union semun {
  int val;                  /* value for SETVAL */
  struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
  unsigned short *array;    /* array for GETALL, SETALL */
  /* Linux specific part: */
  struct seminfo *__buf;    /* buffer for IPC_INFO */
};

static void sig_handle(int signo) ;
static void sigint_handle(int signo) ;

int main(void) 
{

  FILE *fp;
  char buffer[100];
  int status, i, bytesread;
  int pid, mypid;
  int fd;
  int  sem_id1;
  struct sembuf sops[1];
  union semun semarg;

  //get a semaphore  identifier 
  if((sem_id1=semget ( IPC_PRIVATE , 1 , SEM_MODE ))==-1)
    {
      perror("can't create sem_id\n");
      exit(1);
    }
  
  //=========================================================
  
  //semaphore control operations give an initial value to begin with
  semarg.val=2; // only 2 places in the waiting room
  semctl(sem_id1,0,SETVAL,semarg);    
  sops[0].sem_num=0;
  sops[0].sem_flg=0;

  //=============================================================




  status=  mkfifo("myfifo", S_IRUSR| S_IWUSR);
  if (status < 0) 
    {
    perror ("can't mkfifo\n");
    exit (2);
    }
  if (fork()==0){//i am main child IN CHARGE OF CREATING SONS
    for (i=0;i<COUNT;i++)//create COUNT sons to get their hair cut
      {
	if(pid=fork()==0)//i am a son
	  {
	    if (signal(SIGUSR1, sig_handle) == SIG_ERR)
	      perror("can't catch SIGUSR1");
	    fd=open ("myfifo",O_WRONLY);
	    if (-1==fd)
	      {
		perror("can't open fifo.\n");
		exit (0);
	      }
	    mypid=getpid(); // get my process id
	    sops[0].sem_op=-1;  //set semaphore, "occupied", I am waiting on line
	    semop(sem_id1,sops,1);//I lock semaphore 1

	    printf("Client %d pid %d is taking his seat in waiting room.\n",i,mypid);
	    fflush (stdout);
	    flock (fd,LOCK_EX);//  only one should write to fifo at a time
	    sprintf(buffer,"%d",mypid);
	    strcat(buffer,"\n");
	      if (-1==write(fd,buffer,strlen(buffer)))// write pid into fifo
	      {
		perror("Can't write to fifo.\n");
		exit (0);
	      }
	    
	    flock(pid,LOCK_UN);//unlock
	    pause();  // wait for signal from barber that I can get a haircut
	    printf("Client: My turn (client %d, pid %d) to get haircut and exit (release semephore).\n",i,mypid);
	    sops[0].sem_op=1;
	    semop(sem_id1,sops,1);//release semaphore
	    exit (0);
	  }//end a son
      }//end for loop

  }//end main child  
  else
    {
      //i am the father, i.e. the barber
    if (signal(SIGINT, sigint_handle) == SIG_ERR)
	      perror("can't catch SIGINT");
     
      fp = fopen("myfifo","r");

      while (1)
      {
	sleep(1);
	bytesread=fscanf(fp,"%d",&pid);
	if (bytesread<1)
	  continue;
	printf("Barber read: %d \n This client is about have his hair cut .\n", pid);
	kill(pid, SIGUSR1);

	printf("Barber sent signal.........now barber finished cutting hair\n ");
	fflush(stdout); 
      }
      
    }

  return 1;//exit(0); //finished the main
}


//our trap function
static void sig_handle(int signo)
{
  printf("received signal\n");
  return;
}

static void sigint_handle(int signo)
{
  printf("received sigint signal, deleting named pipe\n");
  remove ("myfifo");
  //Remove  immediately  the semaphore set
  semctl(sem_id1,0,IPC_RMID,semarg);
  exit (0);
}




