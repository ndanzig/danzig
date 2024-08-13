/* FILE: simple-sender.c -- simple sender to illustrate programming an
   internet datagram application with sockets.

   SYNTAX: sender  hostname  port  message

   DESCRIPTION:

   Sends a simple text message to the specified IP host and port.  We
   assume that the message is one word.  If you want it to be more
   than one word, you must quote it.
*/

#include <stdio.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>   /* needed for internet sockets */
#include <netdb.h>	  /* needed for gethostbyname */

/******************************************************/
/* err_exit -- call this when exiting due to an error
/******************************************************/

void err_exit ( int status, char *mesg )
{

  perror (mesg);
  exit (status);
}

/******************************************************/
/* parse_cmd_line -- parse the command line & extract the hostname,
/* port, and message.
/*
/*   argc (IN) -- number of words in argv.
/*   argv (IN) -- the command line.
/*   port (OUT) -- gets the value of the port.
/*   hostname (OUT) -- gets the value of the host name.
/*   hostname_max (IN) -- maximum allowed length of hostname.
/*   mesg (OUT) -- set to the message to send.
/*   mesg_max (IN) -- maximum allowed length of mesg.  
/******************************************************/

void parse_cmd_line (int argc,   char **argv,  int *port,  
		     char *hostname,  int hostname_max,
		     char *mesg,  int mesg_max )
{
  int   amount_left;
  int   i;

  if (argc < 4)  err_exit (1, "Need  3 arguments");
  else if (argc > 4)  fprintf (stderr, "Ignoring extra arguments\n");

  /* Get the host name.  We might have to truncate it */

  (void) strncpy (hostname, argv[1], hostname_max);
  if (strlen (hostname) >= hostname_max)
    hostname[hostname_max-1] = '\0';

  /* Get the port.  If the user did not specify a number for the port,
     then atoi will return 0.
  */	
  *port = atoi (argv[2]);
  if (*port <= 0)   err_exit (1, "Invalid port");

  /* Get the message to send.  We might have to truncate it.
  */

  (void) strncpy (mesg, argv[3], mesg_max);
  if (strlen (mesg) >= mesg_max)
    mesg[mesg_max-1] = '\0';

  return;
  
}

/******************************************************/
/* format_socket_name
/******************************************************/

void format_socket_name (char *hostname, int port,
			 struct sockaddr_in *sockname)
{
  struct hostent *host;
  u_short         temp_us;

  /* convert the host name to an IP address.  The IP address will be
     referenced by host->h_addr, & its legnth by host->h_length */

  host = gethostbyname (hostname);
  if (host == 0)  err_exit (2, "gethostbyname call");

  /* Copy the IP address to the sockname structure.  We use bcopy
     instead of strncpy because we don't want a null character
     appended to the end.
  */

  bcopy ( (char *) host->h_addr,
	  (char *) &sockname->sin_addr,
	  host->h_length
	);

  /* Copy the port to the sockname structure.  htons converts from
     host byte-order to network byte-order.  This is to provide
     portability between platforms.  On some platforms, htons does
     absolutely nothing.
  */

  sockname->sin_port = htons ( (u_short) port );

  /* Set the address family (i.e., address domain) */

  sockname->sin_family = AF_INET;

  return;
}

/******************************************************/
/* MAIN FUNCTION
/******************************************************/

#define BUF_MAX 1024
#define DEF_PROTOCOL 0   /* Use the default protocol */
#define SEND_FLAGS 0     /* Flags for the call to sendto */

int main (int argc, char **argv)
{
  char                buf [BUF_MAX+1];  /* message buffer */
  char                hostname [MAXHOSTNAMELEN+1];
  int	              port;
  int                 sd; /* socket descriptor */
  struct sockaddr_in  to_sockname;
  int                 status;

  /* parse the command line.  Exit with a message if there is a syntax
     error
  */

  parse_cmd_line ( argc, argv, &port, hostname, MAXHOSTNAMELEN+1,
		   buf, BUF_MAX+1 );

  /* create the socket.  We do not need to set a name.  The receiver
     DOES; we'll send to him.  The sendto call will automatically
     generate a name for our socket */ 

  sd = socket ( PF_INET, SOCK_DGRAM, DEF_PROTOCOL );
  if ( sd < 0 ) {err_exit (1, "trying to create socket");}

  /* Format the name of the receiving socket & store in to_sockname */

  format_socket_name ( hostname, port,  &to_sockname);

  /* Send the message to the other process.  Because buf contains a
     null-terminated string, we compute the length via 'strlen'.  */

  status = sendto ( sd, buf, strlen(buf), SEND_FLAGS,
		    (struct sockaddr *) &to_sockname,
		    sizeof (to_sockname)
		  );
  if (status < 0)  err_exit (4, "sendto call");

  close (sd);  
 
}
