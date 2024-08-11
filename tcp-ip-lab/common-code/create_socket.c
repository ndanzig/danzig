/* FILE: socket.c -- interface to the socket function call.

   This fills in the parameters that will always be the same for
   me. In addition, it will print an appropriate error message & abort
   if it cannot succeed.

   If successful, this will return the socket descriptor.
*****************************************************/

#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

#define DEFAULT_PROTOCOL 0  /* Let system choose the protocol */

int      /* returns socket descriptor */
create_socket ( int comm_type)  /* communications type */
{
   int sd;

   /* make sure that comm_type has a valid value */
   if ( (comm_type != SOCK_STREAM) && (comm_type != SOCK_DGRAM))
     {
       fprintf (stderr,
		"ERR: create_socket function: called with invalid value %d\n",
		comm_type);
       fprintf (stderr,
		"Valid values are SOCK_STREAM (%d) or SOCK_DGRAM (%d)\n",
		SOCK_STREAM, SOCK_DGRAM);
       exit (1);		
     }

   /* Create the socket */
   sd = socket (PF_INET, comm_type, DEFAULT_PROTOCOL);

   /* If could not create the socket, abort. Otherwise, return */
   if (sd < 0)
     {
       perror ("create_socket function: failed to create socket");
       exit (errno);       
     }

   else {return (sd);}
}
