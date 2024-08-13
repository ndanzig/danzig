/* FILE: test_socket.c -- test create_socket function */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

extern int create_socket ( int comm_type);

int main ()
{
  int i, sd;
  
  while (1)
    {
      printf ("Type %d for SOCK_STREAM, %d for SOCK_DGRAM, \n",
	      SOCK_STREAM, SOCK_DGRAM);
      printf ("0 to quit, or another number to abort ");
      scanf ("%d", &i);
      printf ("You typed %d\n", i);

      if (i == 0)  break;

      sd = create_socket (i);

      printf (">>> Socket descriptor = %d\n--------------------\n", sd);
    }

  exit (0);
}
