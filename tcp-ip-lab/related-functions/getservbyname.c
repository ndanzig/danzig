/* FILE: getservbyname.c 
/* 
/* SYNTAX: getservbyname  service  protocol 
/* 
/* DESCRIPTION: 
/* 
/* This program demonstrates the getservbyname function. 
/* 
/* service	name of the service (e.g., ftp, http) 
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

void parse_cmd_line (int argc, char **argv, char *serv_name, int serv_max,
		     char *proto_name, int proto_max)
{
  static char usage[] = "Usage: getservbyname  service  protocol";

  if ( argc != 3 )
    {
      fprintf (stderr, "%s\n", usage);
      exit (1);
    }
  else if ( strlen(argv[1]) > serv_max )
    {
      fprintf (stderr, "Service name must be no more than %d characters\n",
	       serv_max);
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
      strncpy ( serv_name,  argv[1], serv_max);
      strncpy ( proto_name, argv[2], proto_max);
    }

  if ( (strcmp (proto_name, "tcp") != 0) &&
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

#define SERVICE_MAX 64  /* max length of service name */
#define PROTO_MAX   10  /* max length of protocol name */

int main ( int argc, char **argv)
{
  /* DATA */

  char            proto_name [PROTO_MAX+1];
  char            service_name [SERVICE_MAX+1];
  struct servent *sp;  /* service entry pointer */

  /* ACTION */

  printf ("%s %s\n\n",
	  "You can see a list of service names and port numbers",
	  "in /etc/services.");
  
  parse_cmd_line (argc, argv, service_name, SERVICE_MAX,
		  proto_name, PROTO_MAX);

  sp = getservbyname (service_name, proto_name);
  if ( sp == NULL )
    {
      fprintf (stderr, "no such service\n");
      exit (1);
    }

  print_service_info (sp);
}

exit (0);
