/* signal.c -- demonstrate the signal function.  No options or
   parameters to this command.

   When it starts, this command will display its process ID (PID) and
   which signals it is setting handlers for.  Then it waits for 15
   seconds.  During this time, you can send signals to the process
   using the 'kill' command.

   Then it restores the default actions of these signals.  Once again
   it waits for 15 seconds, during which time you can send signals to
   it once again.
*/

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>

/************************************************************************/
/**  THE SIGNAL HANDLERS */
/*************************************************************************/

void hup ()
{
  printf ("You sent me the SIGHUP (%d) signal\n", SIGHUP);
  return;
}

void quit ()
{
  printf ("You sent me the SIGQUIT (%d) signal\n", SIGQUIT);
  return;
}

void term ()
{
  printf ("You sent me the SIGTERM (%d) signal\n", SIGTERM);
  return;
}

void usr1 ()
{
  printf ("You sent me the SIGUSR1 (%d) signal\n", SIGUSR1);
  return;
}

void usr2 ()
{
  printf ("You sent me the SIGUSR2 (%d) signal\n", SIGUSR2);
  return;
}

/************************************************************************/
/**  THE MAIN FUNCTION */
/*************************************************************************/

int main ()
{
  /* ---------------------------------------------------------- */
  printf ("My process ID = %d\n", getpid());
  printf ("%s\n    %s (%d), %s (%d), %s (%d), %s (%d), %s (%d)\n",
	  "Declaring handlers for the following signals:",
	  "SIGHUP",  SIGHUP,
	  "SIGQUIT", SIGQUIT,
	  "SIGTERM", SIGTERM,
	  "SIGUSR1", SIGUSR1,
	  "SIGUSR2", SIGUSR2);

  signal (SIGHUP,  hup);
  signal (SIGQUIT, quit);
  signal (SIGTERM, term);
  signal (SIGUSR1, usr1);
  signal (SIGUSR2, usr2);

  /* ---------------------------------------------------------- */
  printf ("\n%s\n%s\n", "Now we'll wait for 15 seconds.",
	  "Send one of the signals & see what happens.");
  sleep (15);

  printf ("\n\nNow we restore the default actions of these signals\n");

  signal (SIGHUP,  SIG_DFL);
  signal (SIGQUIT, SIG_DFL);
  signal (SIGTERM, SIG_DFL);
  signal (SIGUSR1, SIG_DFL);
  signal (SIGUSR2, SIG_DFL);

  /* ---------------------------------------------------------- */
  printf ("\n%s\n%s\n", "Now we'll wait for 15 seconds.",
	  "Send one of the signals & see what happens.");
  sleep (15);

  printf ("Exiting normally after the 2nd sleep call\n");
  exit (0);
}
