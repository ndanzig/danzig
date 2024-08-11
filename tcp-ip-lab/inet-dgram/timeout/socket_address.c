/* FILE: socket_address.c

   This file contains functions that convert strings to a valid internet
   socket address (struct sockaddr_in) or vice-versa.
****************************************************/

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define CHOOSE_A_PORT 0  /* let the system choose a port for us */

/**************************************************
 * null_str -- return true if either null pointer or null string.
 *************************************************/

int 
null_str (char *ptr)
{
  if      (ptr == NULL)       {return (1);}
  else if (strlen (ptr) == 0) {return (1);}
  else                        {return (0);}
		      
}


/**************************************************
 * str_to_port -- conver strings to binary port #
 *
 * RETURN STATUS:
 *	1 = success
 *		    
 *	0 = error 
 *
 * This routine will print error messages on stderr.
 *************************************************/

u_int16_t
str_to_port (
    char *str_port,     /* port num as char string, or service name.
			   null string or 0 = system picks a port. */
    char *str_protocol, /* if 'port' is a service name, then
                           this must be either "tcp" or "udp". */
    u_int16_t *b_port ) /* resulting port, in binary form.  On an
			   error return, this is UNdefined. */
{
  int              iport;  /* port number in integer format */
  struct servent  *sep;    /* pointer to service entry structure */

  /* if a null string, or if "0", caller wants the system to choose a port */
  if ( null_str (str_port) || (strcmp (str_port, "0") == 0) )
    {
      *b_port = (u_int16_t) CHOOSE_A_PORT;
      return (1);
    }

  /* if 'str_port' is a number in string form, return that number */
  iport = atoi(str_port);
  if (iport > 0)
    {
      *b_port = htons ((u_int16_t) iport);
      return (1);
    }

  /* if 'str_port' specifies a service name, get the port number from that */
  sep = getservbyname (str_port, str_protocol);
  if (sep != NULL) {
    *b_port = (u_int16_t) sep->s_port;
    return (1);
  }

  /* if we have gotten this far, then there is an error */
  fprintf (stderr,
	   "str_to_port: Cannot get valid port for port %s, protocol %s\n",
	   str_port, str_protocol);
  return (0);
}

/*************************************************************
 * str_to_ip -- convert a host name or an IP address string to the
 *	form needed by the sockaddr_in structure.
 *
 * RETURN VALUES:
 *
 *	1 = success
 *
 *	0 = failure
 *******************************************************************/

int
str_to_ip ( char *host,                  /* host name or IP address.  Null
					    string or null ptr = local host */
	    struct in_addr *ip_address) /* Store IP address in here */
{
  struct hostent *hep;
  struct in_addr *ip;
  char            message [200];

  /* If 'host' is a null pointer or null string, then we use the
     special host value INADDR_ANY, which means the IP address of any
     of the computer's network interfaces. */
  if (null_str(host))
    {
      bcopy ( (char *) INADDR_ANY,      /* copy from this */
	      (char *) ip_address,      /* to here */
	      sizeof (struct in_addr)); /* this many bytes */
      return (1);
    }

  /* Else look up the host name or IP address */
  hep = gethostbyname (host);

  /* If the call failed... */
  if (hep == NULL)
    {
      (void) sprintf (message,
		      "str_to_ip: call to gethostbyname failed, host = %s\n",
		      host);
      perror (message);
      return (0);
    }

  /* otherwise copy the IP address network format to the parameter */
  bcopy ( (char *)hep->h_addr, /* copy from the hostent structure... */
	  (char *)ip_address,  /* to the parameter */
	  hep->h_length);      /* # bytes to copy */
   return (1);
}

/******************************************************
 * str_to_socket -- given a host, transport protocol, and port in
 *	string form, construct an internet socket address structure.
 *
 * RETURN VALUES:
 *
 *	0 = error
 *	1 = success
 *******************************************************/

char nul[] = "";

int
str_to_socket (
    char *host,              /* host name or IP address.  Null
				string/pointer = localhost */
    char *port,              /* name of service or port number.
				Null string/pointer = let the
				system choose a port for us. */
    char *protocol,          /* if 'port' is the name of a
		 		service, this must be "tcp" or
		 		"udp".  Otherwise, it is ignored.  */
    struct sockaddr_in *sap) /* the socket address to fill in */
{
  char *cp1, *cp2;
  int   status;

  /* initialize the socket address */
  bzero ( sap, sizeof (struct sockaddr_in) );

  /* Set to internet address family */
  sap->sin_family = AF_INET;

  /* Set the host */
  status = str_to_ip (host, &(sap->sin_addr));
  if (status == 0)
    {
      cp1 = host;  if (cp1 == NULL) {cp1 = nul;}
      fprintf (stderr, "str_to_socket: failed getting host /%s/\n", host);
      return (0);
    }

  /* Set the port */
  status = str_to_port (port, protocol, &(sap->sin_port));
  if (status == 0)
    {
      cp1 = port;      if (cp1 == NULL) {cp1 = nul;}
      cp2 = protocol;  if (cp2 == NULL) {cp2 = nul;}
      fprintf (stderr,
	       "str_to_socket: failed getting port /%s/ (proto /%s/\n",
	       cp1, cp2);
      return (0);
    }
}


/******************************************************
 * socket_to_str -- given a socket address, return the host IP address
 *	and port #.  These can then be used for messages.
 *
 * NO RETURN VALUE -- if we fail to translate a certain element, it
 *      will be returned as a null string.
 * 
 *******************************************************/

void
socket_to_str (
    struct sockaddr_in *sap, /* pointer to the socket addrss structure */
    char *str_host_ip,       /* host IP address string */
    char *str_host_name,     /* host name string - not generated,
				reserved for future use */
    char *str_port)          /* port # string */
{
  char      *cp_status;  /* status, as char pointer */
  u_int16_t  host_port;  /* port #, in host order */
  int	     i_status;	 /* status, as int */

  /* Get the host IP address */
  cp_status =  inet_ntop (AF_INET,
			  (void *) &(sap->sin_addr),
			  str_host_ip,
			  INET_ADDRSTRLEN);
  if (cp_status == NULL)
    {
      fprintf (stderr, "socket_to_str: could not convert host\n");
      str_host_ip[0] = '\0';
    }

  /* Set host name to null.  Maybe in the future we'll really set it. */
  str_host_name[0] = '\0';

  /* Get the port # */
  i_status = sprintf ( str_port, "%d", ntohs(sap->sin_port) );
  if (i_status == 0)
    {
      fprintf (stderr, "socket_to_str: could not convert port\n");
      str_port[0] = '\0';
    }

  return;
}
