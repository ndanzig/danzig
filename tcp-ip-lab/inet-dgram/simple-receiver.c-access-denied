/* FILE: simple-receiver.c -- simple receiver to illustrate programming an
   internet datagram application with sockets.

   SYNTAX: receiver

   DESCRIPTION:

   Prints out the port it is listening to, then waits for a text
   message.  After receiving the message, it prints it and then
   exits.  The message cannot be more than 76 characters.
*/

#include <stdio.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>   /* needed for internet sockets */

/******************************************************/
/* err_exit -- call this when exiting due to an error
/******************************************************/

void err_exit ( int status, char *mesg )
{
  perror (mesg);
  exit (status);
}

/******************************************************/
/* bind_socket -- bind a socket name to the socket.
/******************************************************/

#define CHOOSE_A_PORT 0  /* System will choose an internet port for us */

void bind_socket ( int sd )
{
  /* local data */
  struct sockaddr_in  sockname;
  int status;

  /* use the internet address family */
  sockname.sin_family = AF_INET;

  /* Specify that we'll accept messages sent to ANY of the local
     host's valid IP addresses.  This is important if the host has
     more than one network connection. */
  sockname.sin_addr.s_addr = INADDR_ANY;

  /* Let the system choose a port */
  sockname.sin_port = CHOOSE_A_PORT;

  /* Now bind the socket "name" that we have defined to the socket.
     Abort if there is an error. */
  status = bind ( sd,  (struct sockaddr *) &sockname,  sizeof sockname );
  if (status < 0)  err_exit (3, "binding name to socket");

  return; 
}

/******************************************************/
/* print_port -- print on standard output which port we are listening
/*    to.  This is needed so that we can tell the sending program to
/*    which port to send.
/*
/*    When we bind the socket to a "name" (or address), we don't have
/*    to specify EVERYTHING.  For example, we can tell the system to
/*    choose a port for us.  So we need this routine to tell us which
/*    port we are actually bound to.
/******************************************************/

void print_port ( int sd )
{
  /* local data */
  int                length;
  u_short            port;     /* internet port number */
  struct sockaddr_in sockname; /* socket name (i.e., address( */
  int                status;

  /* getsockname (& some other socket functions) require that you pass
     it the amount of data pointed to by the socket name structure.
     getsockname will then change this variable to reflect the true
     length of the data. */
  length = sizeof (sockname);

  /* get the actual socket name. */
  status = getsockname ( sd,  (struct sockaddr *) &sockname,  &length);
  if (status < 0)  err_exit (4, "getting socket name");

  /* Extract the port from the socket name structure.  We also have to
     convert the data from network format to host format.  Network
     format is the format used when sending to another host via
     TCP/IP.  Host format is the format used on our local host.  You
     should always use ntohs or related functions, even if the local
     host's format = the network format. */
  port = ntohs ( sockname.sin_port );

  printf ("Listening on socket #%u\n", port);

  return;
}

/******************************************************/
/* read_and_print_message
/******************************************************/

#define MESG_MAX 76

void read_and_print_message ( int sd )
{
  /* local data */
  char mesg [MESG_MAX+1];
  int length;

  /* Read a maximum of MESG_MAX characters.  When we get here, the
     read will "block" (i.e., wait) until some other process sends us
     a message. */
  length = read (sd, mesg, MESG_MAX);
  if ( length < 0 ) err_exit (5, "read error");

  /* Make sure that the message ends in a null character.  The printf
     function will require this. */
  mesg[length] = '\0';

  /* print the message */
  printf ("Read %d bytes.  The message is:\n     %s\n", length, mesg);

  return;
}

/******************************************************/
/* MAIN FUNCTION
/******************************************************/

#define DEF_PROTOCOL 0   /* Use the default protocol */

int main (int argc, char **argv)
{
  /* local data */
  int                 sd; /* socket descriptor */

  /* create the socket */
  sd = socket ( PF_INET, SOCK_DGRAM, DEF_PROTOCOL );
  if ( sd < 0 ) {err_exit (1, "trying to create socket");}

  /* Bind this socket to a name */
  bind_socket (sd);

  /* Print out the port we bound to */
  print_port (sd);

  /* Read & print a message */
  read_and_print_message (sd);

  close (sd);  
 
}
