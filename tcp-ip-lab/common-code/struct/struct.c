/* FILE: struct.c -- This program checks the following
   characteristics, which are liable to be different on different
   types of computers.

       if a structure leaves any 'holes'

       how big certain types are.

       


   Compile and run this program on different computers, and compare
   ther results. 
********************************************************************
*/

#include <stdio.h>
#include <string.h>

#define BUFMAX 60

int main ()
{
  /**************************************
   *** DATA
   **************************************/

  int i;

  /* in this union, we can reference this data area either as a
     struct, called 's', or as one long char array, called 'buf'. */

  union {

    struct {               /* don't need a name for this struct type */
      unsigned char c;
      unsigned int  i;
      unsigned char ca[3];
      unsigned int  ia[3];
    } s;                   /* there is a variable of this type, called 's' */

    unsigned char buf [BUFMAX];

  } u;  /* union */

  /**************************************
   *** ACTION
   **************************************/

  printf ("Size of char = %d, size of int = %d\n",
	  sizeof (char), sizeof (int));

  printf ("Size of SHORT int = %d, size of LONG int = %d\n",
	  sizeof (short int), sizeof (long int));

  printf ("Size of union = %d, buffer max = %d\n", sizeof (u), BUFMAX);

  /* Initialize the data area  to all zeros */

  bzero ((void *) &u, sizeof (u));

  /* Set the elements of the structure.  Note the pattern of the
     values we use: this will be useful when analyzing the results. */

  u.s.c     = 0xa1;
  u.s.i     = 0xb123;
  u.s.ca[0] = 0xc1;   u.s.ca[1] = 0xc2;   u.s.ca[2] = 0xc3; 
  u.s.ia[0] = 0xd123; u.s.ia[1] = 0xd456; u.s.ia[2] = 0xd789; 

  /* print the contents.  Access the data via the char buffer, so we
     can see every byte, and see if there are any holes. We'll also be
     able to see in which order bytes are stored in int variables. */

  for (i=0; i<BUFMAX; i++)
    {
      if ( i%10 == 0 ) {printf ("\n");}
      printf ("%2x  ", u.buf[i]);
    }
  printf ("\n");
  exit (0);
}
