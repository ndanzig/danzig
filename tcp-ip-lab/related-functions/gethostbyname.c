/* FILE: gethostbyname.c 
/* 
/* SYNTAX: gethostbyname host 
/* 
/* description: 
/* 
/* This program demonstrates the gethostbyname function.  It also
/* demonstrates the inet_ntoa function.  This program essentially acts
/* like the nslookup command.
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

void parse_cmd_line (int argc, char **argv, char *hostname,
		     int hostnamemax)
{
  if ( argc != 2 )
    {
      fprintf (stderr, "Must specify exactly 1 host\n");
      exit (1);
    }
  else if ( strlen(argv[1]) > hostnamemax )
    {
      fprintf (stderr, "Host name must be no more than %d characters\n",
	       hostnamemax);
      exit (1);
    }
  else   {strncpy ( hostname, argv[1], hostnamemax);}

  return;
}

/*------------------------------------------------- */
/* print_host_info */
/*------------------------------------------------- */

void print_host_info ( struct hostent *hp )
{
  /* DATA */

  char     **cp;

  /* ACTION */

  printf ("Canonical name is %s\n", hp->h_name);

  printf ("Aliases are:\n");
  cp = hp->h_aliases;
  while ( (*cp != NULL) && (strlen(*cp) > 0) )
    {
      printf ("    %s\n", *cp);
      cp++;
    }

  printf ("Address type = %d (AF_INET = %d)\n", hp->h_addrtype, AF_INET);

  printf ("Address length = %d\n", hp->h_length);
  if ( hp->h_length != 4 )
    {
      fprintf (stderr, "Cannot deal with this length address\n");
      exit (2);
    }

  printf ("Addresses are:\n");
  cp = hp->h_addr_list;
  while ( (*cp != NULL) && (strlen(*cp) > 0) )
    {
      printf ( "    %s\n", inet_ntoa (*cp) );
      cp++;
    }

  return;
}

/*------------------------------------------------- */
/* MAIN FUNCTION */
/*------------------------------------------------- */

int main ( int argc, char **argv)
{
  /* DATA */

  char            hostname [MAXHOSTNAMELEN+1];
  struct hostent *hp;

  /* ACTION */

  parse_cmd_line (argc, argv, hostname, MAXHOSTNAMELEN);

  hp = gethostbyname (hostname);
  if ( hp == NULL )
    {
      fprintf (stderr, "no such host\n");
      exit (1);
    }

  print_host_info (hp);
}
