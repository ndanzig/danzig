/* FILE: large-stream-cli.c -- demonstrate what happends when send a
   large data stream via TCP.  This is the client.

   SYNOPSIS:  large-stream-cli  host  port
*****************************************************/

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

extern int
str_to_socket (char *host, char *port, char *protocol,
	       struct sockaddr_in *sap);

#define BUF_MAX      60000
#define HOST_STR_MAX 256    /* includes null char at end */
#define PORT_STR_MAX 10     /* includes null char at end */

/* Error Codes */
#define MY_ERR_CMD_LINE    1  /* Command line syntax error */
#define MY_ERR_SOCKET      2  /* socket creation error */
#define MY_ERR_BIND        3  /* socket binding error */
#define MY_ERR_GETSOCKNAME 4  /* getsockname error */
#define MY_ERR_SOCKET_CONV 5  /* Converting socket address to/from string */
#define MY_ERR_CONNECT     6  /* Error trying to connect */
#define MY_ERR_SEND        7  /* Error writing/sending data */
#define MY_ERR_SHUTDOWN    8
#define MY_ERR_CLOSE       9

/***************************************************
 *** parse_cmd_line
 ***************************************************/

void
parse_cmd_line (int    argc,
		char **argv,
		char  *host_str,
		size_t host_str_max,
		char  *port_str,
		size_t port_str_max)
{
  fprintf (stderr, ">>> enter parse_cmd_line: argc = %d\n", argc);
  
  /* Error checking */
  if (argc != 3)
    {
      fprintf (stderr, "Usage: large-stream-cli  host  port\n");
      exit (MY_ERR_CMD_LINE);
    }
  else if (strlen(argv[1]) > host_str_max-1)
    {
      fprintf (stderr, "Host name cannot be longer than %d characters.\n",
	       host_str_max-1);
      exit (MY_ERR_CMD_LINE);
    }
  else if (strlen(argv[2]) > port_str_max-1)
    {
      fprintf (stderr, "Port name cannot be longer than %d characters.\n",
	       port_str_max-1);
      exit (MY_ERR_CMD_LINE);
    }

  /* If get this far, then no command line errors */

  strncpy (host_str,         /* destination */
	   argv[1],          /* source */
	   host_str_max);    /* max # chars */

  strncpy (port_str,         /* destination */
	   argv[2],          /* source */
	   port_str_max);    /* max # chars */

  fprintf (stderr, ">>> parse_cmd_line: host = /%s/, port = /%s/\n",
	   host_str, port_str);

  return;
}

/***************************************************
 *** init_buf -- initialize a large buffer.  Return the actual length
 ***    of the buffer.  Do NOT assume that the data is ASCII
 ***************************************************/

int
init_buf (u_int16_t *buf,      /* buffer to initialize */
	  size_t     buf_max)  /* Maximum length buffer can possibly be */
{
  u_int16_t i;      /* value of the current number */

  fprintf (stderr,
	   ">>> start init_buf, buf max = %d, each element = %d bytes\n",
	   buf_max, sizeof (u_int16_t));

  for (i = 0; i< buf_max; i++) {buf[i] = i;}

  return (buf_max);
}

/***************************************************
 *** create_socket -- returns socket descriptor.
 ***************************************************/

#define DEFAULT_PROTOCOL 0

int
create_socket ()
{
  int sd;
  sd = socket (PF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
  if (sd < 0)
    {
      perror ("could not create socket");
      exit (MY_ERR_SOCKET);
    }

  fprintf (stderr, ">>> create_socket: returning with sd = %d\n", sd);

  return(sd);
}

/***************************************************
 *** connect_to_server -- if there is an error, print a message & abort.
 ***************************************************/

void
connect_to_server (int   sd,       /* socket descriptor */
		   char *host_str, /* host to connect to */
		   char *port_str) /* port to connect to */
{
  struct sockaddr_in s;      /* the other end's socket address */
  int                s_len;  /* length of socket address */
  int                status;


  fprintf (stderr,
	   ">>> entering connect_to_server: host = /%s/, port = /%s/\n",
	   host_str, port_str);

  /* Convert the host anme & port strings to a socket address */
  status = str_to_socket (host_str, port_str, "tcp", &s);
  if (status < 1)
    {
      fprintf (stderr,
	       "connect_to_server: str_to_socket returned %d\n", status);
      exit (MY_ERR_SOCKET_CONV);
    }

  /* COnnect to the other socket */
  s_len = sizeof (s);
  status = connect (sd,
		    (struct sockaddr *)&s,
		    s_len);
  if (status < 0)
    {
      perror ("Error trying to connect");
      exit (MY_ERR_CONNECT);
    }

  fprintf (stderr, ">>> leaving connect_to_server: successful\n");
  return;
}


/***************************************************
 *** send_data_to_server
 ***************************************************/

void
send_data_to_server (int        sd,        /* socket descriptor */
		     u_int16_t *buf,       /* buffer to send */
		     int        buf_len)   /* number of elements to send */
{
  /*---------------------------------------------------
    --- DATA
    ---------------------------------------------------*/
  int     bytes_to_write;
  ssize_t bytes_written;
  int     status;

  /*---------------------------------------------------
    --- ACTION
    ---------------------------------------------------*/

  /* Compute how many bytes to write. */
  bytes_to_write = buf_len * sizeof(buf[0]);
  fprintf (stderr,
	   ">>> send_data_to_server: each elem = %d bytes * ",
	   sizeof(buf[0]) );
  fprintf (stderr,
	   "%d elems to write = %d bytes to write\n", buf_len, bytes_to_write);

  /* Write the data to the server.  Print how many bytes were actually
     written */
  bytes_written = write (sd, (void *)buf, bytes_to_write);

  if (bytes_written < 0)
    {
      perror ("Error sending the stream");
      exit (MY_ERR_SEND);
    }

  else if (bytes_written < bytes_to_write)
    {
      fprintf (stderr, "Only %d bytes out of %d sent\n",
	       bytes_written, buf_len);
    }
  else
    {
      printf ("Sent all %d bytes\n", bytes_written);
    }

  return;
}


/***************************************************
 *** close_connection
 ***************************************************/

#define SHUT_READ_AND_WRITE 2

void
close_connection (int sd)
{
  int status;

  /* I don't think that I really need to call shutdown() for this
     simple application; close() is probably enough.  However, I think
     that with TCP, it's best to be safe & call shutdown(). */
 
  status = shutdown (sd, SHUT_READ_AND_WRITE);
  if (status < 0)
    {
      perror ("Error shutting down");
      exit (MY_ERR_SHUTDOWN);
    }

  status = close (sd);
  if (status < 0)
    {
      perror ("Error closing the socket");
      exit (MY_ERR_CLOSE);
    }

  return;
}



/***************************************************
 *** MAIN FUNCTION
 ***************************************************/

int
main (int argc, char **argv)
{
  /*---------------------------------------------------
    --- DATA
    ---------------------------------------------------*/

  u_int16_t buf [BUF_MAX];
  int       buf_len;
  char      host_str [HOST_STR_MAX];
  char      port_str [PORT_STR_MAX];
  int       sd;

  /*---------------------------------------------------
    --- ACTION
    ---------------------------------------------------*/

  parse_cmd_line (argc, argv,
		  host_str, (size_t) HOST_STR_MAX,
		  port_str, (size_t) PORT_STR_MAX);

  buf_len = init_buf (buf, BUF_MAX);
  
  sd = create_socket();

  connect_to_server (sd, host_str, port_str);

  send_data_to_server (sd, buf, buf_len);

  close_connection (sd);

  exit(0);
}
