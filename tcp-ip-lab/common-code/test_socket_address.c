/* FILE: test_port.c -- test str_to-port */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#define STR_MAX 80

extern int str_to_socket ( char *host, char *port, char *protocol,
			   struct sockaddr_in *sap);

extern void socket_to_str ( struct sockaddr_in *sap, char *str_host_ip,
			    char *str_host_name, char *str_port);
int 
main ()
{
  
  while (1)
    {
      /* DATA */
      char                ck_hostname[81];
      char                ck_ip[81];
      char                ck_port[81];
      char                host[81];
      int                 iport;
      int                 num_assigned;
      char                port [81];
      char                protocol [81];
      struct sockaddr_in  sap;
      int                 status;
	  
      /* Get the host name or IP */
      printf ("\nEnter host name or IP address (q to quit) >>> ");
      num_assigned = fscanf (stdin, "%80s", host);
      if (strcmp (host, "q") == 0) {exit(0);}
      if (num_assigned == 0) {host[0] = '\0';}

      /* Get the port */
      printf ("Enter one of the following:\n");
      printf ("\tRET or 0 to let system choose a port\n");
      printf ("\tport # (0 or greater)\n");
      printf ("\tservice name\n");
      printf ("\t'q' to quit\n");
      printf (">>> ");

      num_assigned = fscanf (stdin, "%80s", port);
      if (strcmp (port, "q") == 0) {exit(0);}
      if (num_assigned == 0) {port[0] = '\0';}

      /* Get the transport protocol, if needed */
      if (isalpha (port[0]))
	{
	  printf ("\nEnter udp or tcp >>> ");
	  num_assigned = fscanf (stdin, "%80s", protocol);
	  if (strcmp (protocol, "q") == 0) {exit(0);}
	  if (num_assigned == 0) {protocol[0] = '\0';}
	}
      else {protocol[0] = '\0';}
      /* Convert the strings to a socket address */
      status = str_to_socket (host, port, protocol, &sap);
      if (status)
	{
	  printf ("Call to str_to_socket successful\n");
	  socket_to_str (&sap, ck_ip, ck_hostname, ck_port);
	  printf ("socket_to_str call yielded:\n");
	  printf ("    IP    /%s/\n", ck_ip);
	  printf ("    name  /%s/\n", ck_hostname);
	  printf ("    port  /%s/\n", ck_port);
	}

      printf ("\n===========================\n");

    } /* while (1) */
}
