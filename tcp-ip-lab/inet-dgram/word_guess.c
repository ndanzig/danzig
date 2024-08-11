/* FILE: word_guess -- server for the word guess program.

	This program demonstrates a standard technique for handling
	more than one client at a time:

	    (1) after getting the initial request, create a new socket
	        for the rest of the session.

	    (2) fork & have the child handle the rest of the session.

	Another technique is to use select(2) function instead of
	forking.  Do "man select" (or "man 2 select") for more
	information.  Step 1 would remain the same.

	===================================================
	=== NOTE: as of 30 Cheshvan 5760 (09/11/1999), this program
	=== compiles, but is very incomplete.  Most of the functions
	=== are stubs.  I started writing this program last year; I'm
	=== not sure if I'll want it this year.
	===================================================

    SYNOPSIS:  word_guess
*/

#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>  /* for sleep function, which is used for stubs */


/**************************************************
 * create_socket  -- create the socket, bind it to a port, and print
 *     which port it bound to.
 **************************************************/

#define DEFAULT_PROTOCOL 0  /* Let system choose a protocol */
#define CHOOSE_A_PORT    0  /* Let system  choose an internet port */

int create_socket()
{
  /*-------------------------------------------------
   * DATA
   *-------------------------------------------------*/
  int                length;
  u_short            port;     /* internet port number */
  int                sd;
  struct sockaddr_in sock_addr;
  int                status;

  /*-------------------------------------------------
   * Create the socket
   *-------------------------------------------------*/
  sd = socket (PF_INET, SOCK_DGRAM, DEFAULT_PROTOCOL);
  if ( sd < 0 )
    {
      perror ("trying to create socket");
      exit (1);
    }

  /*-------------------------------------------------
   * Bind the socket
   *-------------------------------------------------*/

  /* use the internet address family */
  sock_addr.sin_family = AF_INET;

  
  /* Specify that we'll accept messages sent to ANY of the local
     host's valid IP addresses.  This is important if the host has
     more than one network connection. */
  sock_addr.sin_addr.s_addr = INADDR_ANY;

  /* Let the system choose a port */
  sock_addr.sin_port = CHOOSE_A_PORT;

  /* Now bind the socket "name" that we have defined to the socket.
     Abort if there is an error. */
  status = bind ( sd,  (struct sockaddr *) &sock_addr,  sizeof sock_addr );
  if (status < 0)
    {
      perror ("binding name to socket");
      exit (1);
    }

  /*-------------------------------------------------
   * Print the port
   *-------------------------------------------------*/

  /* getsockname (& some other socket functions) require that you pass
     it the amount of data pointed to by the socket name structure.
     getsockname will then change this variable to reflect the true
     length of the data. */
  length = sizeof (sock_addr);

  /* get the actual socket name. */
  status = getsockname ( sd,  (struct sockaddr *) &sock_addr,  &length);
  if (status < 0)
    {
      perror ("getting socket name");
      exit (1);
    }

  /* Extract the port from the socket name structure.  We also have to
     convert the data from network format to host format.  Network
     format is the format used when sending to another host via
     TCP/IP.  Host format is the format used on our local host.  You
     should always use ntohs or related functions, even if the local
     host's format = the network format. */
  port = ntohs ( sock_addr.sin_port );

  printf ("Listening on socket #%u\n", port);

  return (sd);
}

/**************************************************
 * set_signal_handlers
 **************************************************/

void
set_signal_handlers ()
{
  fprintf (stderr, "Called set_signal_handlers (stub)\n");
  return;
}

/**************************************************
 * get_request -- get a request from a client to play a game.  This
 *       request includes the first letter that the client guesses.
 *       Note that the server has not necessarily chosen a word yet.
 *       (PROBABLY WILL WANT TO CHANGE THIS)
 *
 *	 This function returns the letter guessed (null if there is an
 *       error) and the socket address of the client.
 **************************************************/

char
get_request (int sd,                             /* my socket's descriptor */
	     struct sockaddr_in *client_socket)  /* client socket address */
{
  fprintf (stderr, "Called get_request (stub), sd = %d, sleeping 15 secs\n",
	   sd);
  (void) sleep (15);
  bzero ( (char *)client_socket,
	  sizeof (struct sockaddr_in) );
  return('a');
}

/**************************************************
 * play_game -- start playing the game with a client.  This function
 *       binds to a different port and starts a new process for the rest
 *       of the game (not necessarily in that order).
 **************************************************/

void
play_game (int sd,
	   char letter,
	   struct sockaddr_in *client_socket)
{
  fprintf (stderr, "Called play_game(stub), sd = %d, letter = %c\n",
	   sd, letter);
  return;
}

/**************************************************
 * MAIN FUNCTION
 **************************************************/
int main ()
{
  /*------------------------------------------------
   * DATA
   *------------------------------------------------*/
  struct sockaddr_in  client_socket;
  char                letter;
  int                 sd;

  /*------------------------------------------------
   * ACTION
   *------------------------------------------------*/
  sd = create_socket();

  set_signal_handlers();

  for (;;)
    {
      letter = get_request (sd, &client_socket);
      play_game (sd, letter, &client_socket);
    }
}
