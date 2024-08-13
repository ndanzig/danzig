/* FILE: getservbyport.c 
/* 
/* SYNTAX: getservbyport  port  protocol 
/* 
/* DESCRIPTION: 
/* 
/* This program demonstrates the getservbyport function. 
/* 
/* port		number of the TCP/UDP port.
/* 
/* protocol	"tcp" or "udp"
/*========================================================*/

#include <stdio.h>
#include <sys/param.h>    /* needed for MAXHOSTNAMELEN */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

/*------------------------------------------------- */
/* parse_cmd_line */
/*------------------------------------------------- */

void parse_cmd_line (int argc, char **argv, int *port,
		     char *proto_name, int proto_max)
{
  static char usage[] = "Usage: getservbyport  port  protocol";

  if ( argc != 3 )
    {
      fprintf (stderr, "%s\n", usage);
      exit (1);
    }
  else if ( strlen(argv[2]) > proto_max )
    {
      fprintf (stderr, "Protocol name must be no more than %d characters\n",
	       proto_max);
      exit (1);
    }
  else
    {
      *port = atoi (argv[1]);
      strncpy ( proto_name, argv[2], proto_max);
    }

  if ( *port <= 0 )
    {
      fprintf (stderr, "Invalid port %s\n", argv[1]);
      exit (1);
    }
  else if ( (strcmp (proto_name, "tcp") != 0) &&
            (strcmp (proto_name, "udp") != 0) )
    {
      fprintf (stderr, "Protocol must be either TCP or UDP\n");
      exit (1);
    }

  return;
}

/*------------------------------------------------- */
/* print_service_info */
/*------------------------------------------------- */

void print_service_info ( struct servent *sp )
{
  /* DATA */

  char     **cp;

  /* ACTION */

  printf ("Offical name of the service is  %s\n", sp->s_name);

  printf ("Aliases are:\n");
  cp = sp->s_aliases;
  while ( (*cp != NULL) && (strlen(*cp) > 0) )
    {
      printf ("    %s\n", *cp);
      cp++;
    }

  printf ("At port %d\n", sp->s_port);

  printf ("Protocol = %s\n", sp->s_proto);

  return;
}

/*------------------------------------------------- */
/* MAIN FUNCTION */
/*------------------------------------------------- */

#define PROTO_MAX   10  /* max length of protocol name */

int main ( int argc, char **argv)
{
  /* DATA */

  int             port;
  char            proto_name [PROTO_MAX+1];
  struct servent *sp;  /* service entry pointer */

  /* ACTION */

  printf ("%s %s\n\n",
	  "You can see a list of service names and port numbers",
	  "in /etc/services.");
  
  parse_cmd_line (argc, argv, &port, proto_name, PROTO_MAX);

  sp = getservbyport (port, proto_name);
  if ( sp == NULL )
    {
      fprintf (stderr, "no such service\n");
      exit (1);
    }

  print_service_info (sp);

  exit (0);

}

