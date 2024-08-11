/* FILE: large-stream-serv.c -- demonstrate what happends when send a
   large data stream via TCP.  This is the server.

   SYNOPSIS:  large-stream-serv
*****************************************************/

#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

extern int
str_to_socket (char *host, char *port, char *protocol,
	       struct sockaddr_in *sap);

#define BUF_MAX      60000 * sizeof(u_int16_t)  
#define HOST_STR_MAX   256    /* includes null char at end */
#define PORT_STR_MAX    10    /* includes null char at end */
#define IP_STR_MAX      20    /* 16 should be enough */

/* Error Codes */
#define MY_ERR_CMD_LINE     1  /* Command line syntax error */
#define MY_ERR_SOCKET       2  /* socket creation error */
#define MY_ERR_BIND         3  /* socket binding error */
#define MY_ERR_GETSOCKNAME  4  /* getsockname error */
#define MY_ERR_SOCKET_CONV  5  /* Converting socket address to/from string */
#define MY_ERR_CONNECT      6  /* Error trying to connect */
#define MY_ERR_SEND         7  /* Error writing/sending data */
#define MY_ERR_SHUTDOWN     8
#define MY_ERR_CLOSE        9
#define MY_ERR_LISTEN      10
#define MY_ERR_ACCEPT      11
#define MY_ERR_RECV        12  /* Error reading/receiving data */

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
 *** bind_socket -- if there an error, print message and abort.
 ***************************************************/

#define CHOOSE_PORT_FOR_ME 0

void
bind_socket (int sd)
{
  /*---------------------------------------------------
    --- DATA
    ---------------------------------------------------*/

  char               host_name_str [HOST_STR_MAX];
  char               ip_str        [IP_STR_MAX];
  char               port_str      [PORT_STR_MAX];
  struct sockaddr_in s;     /* my socket address */
  int                s_len; /* length of s */
  int                status;

  /*---------------------------------------------------
    --- ACTION
    ---------------------------------------------------*/

  /* initialize the socket address */

  s_len = sizeof (s);
  bzero ( (void *)&s, s_len);
  s.sin_family = AF_INET;
  s.sin_port = CHOOSE_PORT_FOR_ME;
  s.sin_addr.s_addr = htonl (INADDR_ANY);

  /* bind to a port */

  status = bind (sd,                     /* socket descriptor */
		 (struct sockaddr *) &s, /* socket address */
		 s_len);                 /* length of socket address */
  if (status < 0)
    {
      perror ("Error binding my socket");
      exit (MY_ERR_BIND);
    }

  /* Get my port. */

  status = getsockname (sd,                    /* socket descriptor */
			(struct sockaddr *)&s, /* socket address */
			(socklen_t *)&s_len);  /* length of socket address */
  if (status < 0)
    {
      perror ("Error calling gesockname");
      exit (MY_ERR_GETSOCKNAME);
    }

  /* print my port */

  socket_to_str (&s, ip_str, host_name_str, port_str);
  printf ("Bound to port %s\n", port_str);

  return;
}

/***************************************************
 *** enter_passive_mode -- this makes us ready to accept connections.
 ***************************************************/

#define QUEUE_LENGTH  20

void
enter_passive_mode (int sd)
{
  int status;

  fprintf (stderr,
	   ">>> entering enter_passive_mode, queue len = %d\n",
	   QUEUE_LENGTH);

  status = listen (sd, QUEUE_LENGTH);
  if (status < 0)
    {
      perror ("Error on listen call");
      exit (MY_ERR_LISTEN);
    }

  fprintf (stderr, ">>> leaving enter_passive_mode: success\n");
  return;
}

/***************************************************
 *** create_passive_socket -- do everything we have to do in order to
 ***     be ready to accept a connection.  Returns a socket descriptor.  If
 ***     there is an error, print a message, but do NOT abort.
 ***************************************************/

int
create_passive_socket()
{
  int sd;

  sd = create_socket ();
  bind_socket (sd);
  enter_passive_mode (sd);

  return (sd);
}


/***************************************************
 *** close_connection
 ***************************************************/

#define SHUT_READ_AND_WRITE 2

void
close_connection (int sd)
{
  int status;

  fprintf (stderr, ">>> close_connection, sd = %d\n", sd);

  /* I don't think that I really need to call shutdown() for this
     simple application; close() is probably enough.  However, I think
     that with TCP, it's best to be safe & call shutdown().

     Note that shutdown() returns with an error if the socket is NOT
     connected.  In that case, we print out the error, but that is NOT
     really a problem for our purpose.
  */
 
  status = shutdown (sd, SHUT_READ_AND_WRITE);
  if (status < 0)
    {
      perror ("Error shutting down, but that might not matter");
    }

  status = close (sd);
  if (status < 0)
    {
      perror ("Error closing the socket");
    }

  return;
}



/***************************************************
 *** accept_connection
 ***************************************************/

int
accept_connection (int current_sd)
{
  /*---------------------------------------------------
    --- DATA
    ---------------------------------------------------*/

  char               host_name_str [HOST_STR_MAX];
  char               ip_str [IP_STR_MAX];
  char               port_str [PORT_STR_MAX];
  int                new_sd;
  struct sockaddr_in s;
  int                s_len;

  /*---------------------------------------------------
    --- ACTION
    ---------------------------------------------------*/

  fprintf (stderr,
	   ">>> entering accept_connection, current sd = %d\n",
	   current_sd);

  /* Accept a connection.  If error, print message & abort.  */
  s_len = sizeof (s);  /* initialize for accept() */
  new_sd = accept (current_sd,
		   (struct sockaddr *) &s,
		   &s_len);

  if (new_sd < 0)
    {
      perror ("Error trying to accept connection");
      exit (MY_ERR_ACCEPT);
    }

  /* Print the socket address of the other */

  socket_to_str (&s, ip_str, host_name_str, port_str);
  printf ("Accepted connection from host %s, port %s\n",
	  ip_str, port_str);

  fprintf (stderr,
	   ">>> leaving accept_connection: old sd = %d, new sd = %d\n",
	   current_sd, new_sd);
  return (new_sd);
  
}


/***************************************************
 *** open_dump_file -- open file that we will dump data to.  Return
 ***     file descriptor of that file.
 ***************************************************/

#define FILE_NAME_MAX 256

int
open_dump_file ()
{
  int fd;
  char file_name [FILE_NAME_MAX];
  
  sprintf ( file_name, "/tmp/large-stream.%06d", getpid() );
  fprintf (stderr, ">>> in open_dump_file, file name = %s\n", file_name);

  fd = open (file_name,
	     O_WRONLY | O_CREAT,  /* flags: write-only, create if need to */
	     S_IRUSR | S_IWUSR);  /* permissions: user can read & write file */
  if (fd < 0)
    {perror ("Error trying to open dump file");}
  else
    {
      printf (">>> open_dump_file: successfully opened dump file, fd = %d\n",
	      fd);
    }

  return (fd);
      
}

/***************************************************
 *** dump_data -- write data to dump file, if there is one
 ***************************************************/

void
dump_data (int fd, char *buf, int num_bytes)
{
  int bytes_written;

  if (fd < 0)  return;

  bytes_written = write (fd, buf, num_bytes);
  fprintf (stderr, ">>> Dumped %d/%d bytes\n", bytes_written, num_bytes);
  return;
}

/***************************************************
 *** receive_and_dump_data -- do NOT assume that the data is ASCII.
 ***************************************************/

void
receive_and_dump_data (int sd)
{
  /*---------------------------------------------------
    --- DATA
    ---------------------------------------------------*/

  int  bytes_read;
  char buf [BUF_MAX];
  int  fd;            /* file descriptor of dump file */
  int  iteration;

  /*---------------------------------------------------
    --- ACTION
    ---------------------------------------------------*/

  fd = open_dump_file ();
  
  iteration = 0;
  do
    {
      iteration++;
      
      /* read the data, check for error */
      bytes_read = read (sd, buf, BUF_MAX);

      if (bytes_read < 0)
	{
	  perror ("read error");
	  exit (MY_ERR_RECV);
	}

      printf ("ITERATION %d, READ %d BYTES.\n", iteration, bytes_read);

      /* dump the data to the dump file, if there is one */
      dump_data (fd, buf, bytes_read);
    }
  while (bytes_read > 0);

  close (fd);
  return;
}


/***************************************************
 *** MAIN FUNCTION
 ***************************************************/

int
main ()
{
  /*---------------------------------------------------
    --- DATA
    ---------------------------------------------------*/

  char buf [BUF_MAX];
  int  buf_len;
  char host_str [HOST_STR_MAX];
  int  new_sd;
  char port_str [PORT_STR_MAX];
  int  sd;

  /*---------------------------------------------------
    --- ACTION
    ---------------------------------------------------*/
  
  sd = create_passive_socket();

  new_sd = accept_connection (sd);

  close_connection (sd);

  receive_and_dump_data (new_sd);

  close_connection (new_sd);

  exit(0);
}
