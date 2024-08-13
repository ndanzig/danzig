
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

sig_atomic_t sig_count = 0;

void handler (int signal_number)
{
  ++sig_count;
  sleep(3);
}
int main()
{
  int i,j;
  struct sigaction sa,old_action;
  printf ("my pid %d\n", getpid());
  memset (&sa, 0, sizeof(sa)); //put 0 into first sizeof(sa) bytes of sa
  sa.sa_handler = &handler;//SIG_IGN;//SIG_DFL//&handler;//give it a function pointer
  sigaction (SIGINT, &sa, NULL);//modify siguser1 to handler, NULL means function returns zero instead of previous action for the signal
  for (i = 0; i < 2; i++)
    sleep (5);
  printf ("SIGINT was raised %d times\n", sig_count);
}
