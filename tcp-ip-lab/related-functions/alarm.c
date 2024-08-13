/* FILE: alarm.c

   SYNTAX: alarm

   DESCRIPTION:

        This program demonstrates the alarm & signal functions.  It
        sets the alarm for 15 seconds & waits.  When the alarm goes
        off, it prints how early the alarm. This can happen because
        some other process might have sent it the SIGALRM signal.

        This program also illustrates the gettimeofday & ctime
        functions.  I use them together to print the current time.

        This program does not stop by itself.  You have to send it a
        signal to stop it.  However, see BUGS.

   BUGS:

        Typing control-C does NOT stop this process.  Perhaps the loop
	in the main function is the problem.  Workarounds:

            (1) You can suspend the process by typing control-Z,
                and then kill the background process.

            (2) You can run this program in the background.  It will
	        still print on standard output.

            (3) another process can send this process the SIGTERM signal
	        (e.g., via the kill command). 
   ============================================================== */

#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

/*------------------------------------------------------------
  print_current_time -- print the current time on the standard output
  ------------------------------------------------------------
*/
void print_current_time ()
{
  time_t          curr_time;
  int             status;
  struct timeval  tv;
  struct timezone tz;

  /* get the current time, in a binary format */
  status = gettimeofday (&tv, &tz);
  if ( status != 0 )
    {
      perror ("call to gettimeofday failed");
      exit (1);
    }

  /* Extract the number of seconds, and conver it to a text string via
     the ctime function */
  curr_time = (time_t) tv.tv_sec;
  printf ("Current time = %s\n", ctime (&curr_time));
  return;  
}

/*------------------------------------------------------------
  reset_alarm -- resets the alarm & prints out information on the
  standard output.  This function is called when the process receives
  the SIGALRM signal.
  ------------------------------------------------------------
*/
void reset_alarm ()
{
  unsigned int    remainder;

  /* remainder is how many seconds remain from the PREVIOUS call to
     alarm().  Note that the alarm() function does NOT suspend the
     process; it returns immediately.
  */
  remainder = alarm (15);
  printf ( "%u %s\n%s\n\n",
	   remainder,
	   "seconds remaining from previous alarm call",
	   "Next alarm will go off in 15 seconds");
  print_current_time ();

  /* for interrupts, the programmer often uses setjmp & longjmp
     instead of return.  But return is easier, and is enough for this
     example. */
  return;
}


/*------------------------------------------------------------
  MAIN FUNCTION
  ------------------------------------------------------------
*/
int main ()
{
  int             pid;

  pid = getpid();
  printf ("%s %d %s\n%s %d %s\n\n",
	  "My process ID (PID) is",
	  pid,
	  ".  You can cause the alarm function",
	  "to return earlier by running 'kill -ALRM",
	  pid,
	  ".");

  /* Now, whenever this process receives the SIGLARM signal, it will
     call function reset_alarm. */
  signal (SIGALRM, &reset_alarm);

  /* call it 1st time to initialize */
  reset_alarm();  

  /* Now just keep busy while we wait for the alarm to go off.  We
     cannot use sleep, because that does not work well with alarm.
     See the alarm(3) man page for details.

     We do not want just an empty loop, because that will hog CPU
     cycles.  Therefore, I chose a command with a lot of I/O.
     /etc/termcap is a large file. */
  for (;;)   system ("cp /etc/termcap /dev/null");      
  
}
