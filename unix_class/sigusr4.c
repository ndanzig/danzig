//now lets mask out siguser1

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

sig_atomic_t sig_count = 0;
struct sigaction old_action;

void handler (int signal_number)
{
++sig_count;

    printf ("in handle\n");
    fflush(stdout);
    sleep(5);
    //    sigaction (SIGINT, &old_action, NULL);
    printf ("woke up and SIGINT was reset\n");
    fflush(stdout);
}
int main()
{
  int i,j;
  struct sigaction sa;
  printf ("my pid %d\n", getpid());
  memset (&sa, 0, sizeof(sa)); //put 0 into first sizeof(sa) bytes of sa
  sa.sa_handler = &handler;//SIG_IGN;//SIG_DFL//&handler;//give it a function pointer
  sigemptyset(&sa.sa_mask);
  sigaddset(&sa.sa_mask,SIGUSR1);
  sigaction (SIGINT, &sa, &old_action);
  sleep(20);//interrupted sleep does not resume!!
  printf("Came back\n");
  fflush(stdout);
  //  sleep(10);
  printf ("SIGINT was raised %d times\n", sig_count);
}
