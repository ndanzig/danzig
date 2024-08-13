
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

sig_atomic_t sigusr1_count = 0;
sig_atomic_t sigusr2_count = 0;

void handler (int signal_number)
{
++sigusr1_count;
}

void handler2(int sig, siginfo_t *siginfo, void *context)
{
fprintf(stderr, "PID %ld UID %ld\n", (long)siginfo->si_pid, (long)siginfo->si_uid); 
}
int main()
{
int i,j;
printf ("my pid %d\n", getpid());
struct sigaction sa,old_action;
 memset (&sa, 0, sizeof(sa)); //put 0 into first sizeof(sa) bytes of sa
 sa.sa_handler = &handler;//give it a function pointer
 sigaction (SIGUSR1, &sa, NULL);//modify siguser1 to handler, NULL means function returns zero instead of previous action for the signal


struct sigaction sa2;
memset (&sa2, 0, sizeof(sa2));
sa2.sa_sigaction = &handler2;
sa2.sa_flags |= SA_SIGINFO;


sigaction (SIGUSR1, &sa, NULL);

sigaction (SIGUSR2, NULL, &old_action);
sigemptyset(&sa2.sa_mask);
sigaddset(&sa2.sa_mask, SIGUSR1);

if (old_action.sa_handler != SIG_IGN)
        sigaction (SIGUSR2, &sa2, NULL);

//sigprocmask (SIG_BLOCK, &sa2.sa_mask, NULL);

for (i = 0; i < 30; i++)
  sleep (1);
printf ("SIGUSR1 was raised %d times\n", sigusr1_count);
}
