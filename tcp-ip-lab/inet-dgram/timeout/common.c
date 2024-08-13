/* FILE: common.c -- these are functions that will probably be common
   to one or more method of timeout.
**********************************************************/

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

/*********************************************************
 *** print_current_time -- print the current time on stdout.
 **********************************************************/

void
print_current_time ()
{
  time_t          curr_time;
  int             status;
  struct timeval  tv;
  struct timezone tz;

  /* get the current time, in a binary format */
  status = gettimeofday (&tv, &tz);
  if ( status != 0 )
    {
      perror ("print_current_time: call to gettimeofday failed");
      return;
    }

  /* Extract the number of seconds, and conver it to a text string via
     the ctime function */
  curr_time = (time_t) tv.tv_sec;
  printf ("Current time = %s\n", ctime (&curr_time));
  return;    
}

/*********************************************************
 *** print_start_timeout -- print the current time, and the timeout in
 ***     seconds.
 **********************************************************/

void
print_start_timeout (const int timeout_in_seconds)
{
  printf ("\n============================\n");
  print_current_time();
  printf ("   timeout in %d seconds.\n",  timeout_in_seconds);
  return;
}

/*********************************************************
 *** print_recv_succeeded -- print a message saying that we
 ***     successfully received.  We also print out how many bytes we
 ***     received and what the timeout value was.
 **********************************************************/

void
print_recv_succeeded (const int num_bytes,
		      const int timeout_in_seconds)
{
  print_current_time();
  printf ("   successfully received %d bytes.  timeout was %d seconds.\n",
	  num_bytes, timeout_in_seconds);
  return;
}
