/* FILE: struct-tftp-data.c -- This program checks the following
   characteristics, which are liable to be different on different
   types of computers.

       if a structure leaves any 'holes'

       how big certain types are.

   The example structure is similar to a TFTP data packet.

   Compile and run this program on different computers, and compare
   ther results. 
********************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>   /* for type u_int16_t */

#define BUFMAX 128

int main ()
{
  /**************************************
   *** DATA
   **************************************/

  int i;

  /* in this union, we can reference this data area either as a
     struct, called 's', or as one long char array, called 'buf'. */

  union {

    /* Note that this struct is similar to the structure of TFTP data
       and error packets: 2 16-bit unsigned numbers, followed by a
       byte array of data.  I chose the names of the fields based on a
       TFTP data packet.
    */

    struct {               /* don't need a name for this struct type */
      u_int16_t     opcode;
      u_int16_t     pkt_num;
      unsigned char data[64];
    } s;                   /* there is a variable of this type, called 's' */

    unsigned char buf [BUFMAX];

  } u;  /* union */

  /**************************************
   *** Print size of various data types
   **************************************/

  printf ("Size of char = %d, size of int = %d\n",
	  sizeof (char), sizeof (int));

  printf ("Size of SHORT int = %d, size of LONG int = %d\n",
	  sizeof (short int), sizeof (long int));

  printf ("Size of u_int16_t = %d\n",
	  sizeof (u_int16_t));

  printf ("Size of union = %d, buffer max = %d\n", sizeof (u), BUFMAX);

  /**************************************
   *** Set the data via the struct, and brint the buffer byte-by-byte.
   **************************************/

  /* Initialize the data area  to all zeros */

  bzero ((void *) &u, sizeof (u));

  /* Set the elements of the structure.  Note the pattern of the
     values we use: this will be useful when analyzing the results. */

  u.s.opcode  = 0xa123;   /* 16-bit value */
  u.s.pkt_num = 0xb123;   /* 16-bit value */

  u.s.data[0] = 0x11;
  u.s.data[1] = 0x22;
  u.s.data[2] = 0x33;
  u.s.data[3] = 0x44;
  u.s.data[4] = 0x55;
  u.s.data[5] = 0x66;
  u.s.data[6] = 0x77;
  u.s.data[7] = 0x88;


  /* print the contents.  Access the data via the char buffer, so we
     can see every byte, and see if there are any holes. We'll also be
     able to see in which order bytes are stored in int variables. */

  for (i=0; i<BUFMAX; i++)
    {
      if ( i%8 == 0 ) {printf ("\n");}
      printf ("%2x  ", u.buf[i]);
    }
  printf ("\n-------------------------------------\n");

  /**************************************
   *** Set the data via the buffer, and the fields
   **************************************/

  u.buf[0]  = 0x11;
  u.buf[1]  = 0x22;
  u.buf[2]  = 0x33;
  u.buf[3]  = 0x44;
  u.buf[4]  = 0x55;
  u.buf[5]  = 0x66;
  u.buf[6]  = 0x77;
  u.buf[7]  = 0x88;
  u.buf[8]  = 0x99;
  u.buf[9]  = 0xaa;
  u.buf[10] = 0xbb;
  u.buf[11] = 0xcc;
  u.buf[12] = 0xdd;
  u.buf[13] = 0xee;
  u.buf[14] = 0xff;

  /* Now print the values of the fields */

  printf ("opcode = %4x, pkt_num = %4x\n", u.s.opcode, u.s.pkt_num);

  printf ("1st 4 bytes of data field = %2x %2x %2x %2x\n",
	  u.s.data[0], u.s.data[1], u.s.data[2], u.s.data[3]);

  exit (0);

}
