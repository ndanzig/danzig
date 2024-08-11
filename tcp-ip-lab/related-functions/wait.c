/* FILE: wait.c -- demonstrate waiting for child processes.

	Demonstrates the fork & wait functions.

	Specifically, this demonstrates that when the child dies, it
	is NOT completely killed until the parent calls the wait
	function.

	See the wait function manual page other variations of the wait
	function.
*/

#include <stdio.h>
#include <sys/wait.h>

char cmd[] = "'ps | sort'";
char cmd_bg[] = "'ps -x | sort";

int main ()

{
  int  child_pid, child_pid_2;  /* process ID of the child process */
  int  child_status;
  int  parent_pid;  /* process ID of the parent */

  child_pid = fork();

  /*--------   PARENT   ------------------*/
  if ( child_pid > 0 )
    {
      parent_pid = getpid();
      printf ("PARENT: my pid = %d, my child's pid = %d\n",
	      parent_pid, child_pid);
      printf ("PARENT: I'm going to sleep for 30 seconds.\n");
      printf ("PARENT: Run %s to see my child & I\n\n", cmd);
      printf ("PARENT: (If you started me in the background, run %s\n",
	      cmd_bg);

      sleep (30);

      child_pid_2 = wait ( &child_status );
      printf ("PARENT: I woke up & called wait.  It returned PID %d\n",
	      child_pid_2);
      printf ("PARENT: exit status of child = %o\n\n", child_status);
      printf ("PARENT: I'll go to sleep for another 15 seconds.\n");
      printf ("PARENT: Run %s again to see that the child is gone.\n\n",
	      cmd);

      sleep (15);

      printf ("PARENT: OK, I'm done.\n");
      exit (0);
    }

  /*--------   CHILD   ------------------------*/
  else if ( child_pid == 0)
    {
      printf ("CHILD: I'm going to sleep for 15 seconds.\n\n");

      sleep (15);

      printf ("CHILD: I'm exiting now.\n");
      printf ("CHILD: Do %s to see if I'm a zombie\n\n", cmd);

      exit (0);
    }

  /*------------------  FORK ERROR  ------------------*/
  else
    {
      perror ("fork error");
      exit (1);
    }
}
