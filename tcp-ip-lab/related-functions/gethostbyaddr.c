/* FILE: gethostbyaddr.c
/* 
/* SYNTAX: gethostbyaddr  ip_address
/* 
/* description: 
/* 
/* This program demonstrates the getaddrbyaddr function.  It also
/* demonstrates the inet_addr function.
/*========================================================*/

#include <stdio.h>
#include <sys/param.h>    /* needed for MAXHOSTNAMELEN */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*------------------------------------------------- */
/* parse_cmd_line */
/*------------------------------------------------- */

void parse_cmd_line (int argc, char **argv, char *addr_str,
		     int addr_str_max)
{
  if ( argc != 2 )
    {
      fprintf (stderr, "Must specify exactly 1 host\n");
      exit (1);
    }
  else if ( strlen(argv[1]) > addr_str_max )
    {
      fprintf (stderr, "Host name must be no more than %d characters\n",
	       addr_str_max );
      exit (1);
    }
  else   {strncpy ( addr_str, argv[1], addr_str_max);}

  return;
}

/*------------------------------------------------- */
/* get_host_entry -- convert IP address string to host entry */
/*------------------------------------------------- */

struct hostent *get_host_entry (char *addr_str)
{
  /* DATA */

  unsigned long   addr_num;
  struct hostent *hp;

  /* ACTION */

  /* convert the address string to an address number */
  addr_num = inet_addr (addr_str);
  if ( addr_num <= 0 )
    {
      fprintf (stderr, "inet_addr call failed, addr_num = %lu\n", addr_num);
      exit (2);
    }

  /* conver the address number to the hostent structure.  Note that we
     must pass the ADDRESS of variable addr_num. */
  hp = gethostbyaddr ( (char *) &addr_num,  sizeof addr_num, AF_INET);
  if ( hp == NULL )
    {
      fprintf (stderr, "gethostbyaddr call failed\n");
      exit (1);
    }

  return (hp);
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

#define IPADDR_MAX 15  /* (4 * 3 digits) + 3 dots */

int main ( int argc, char **argv)
{
  /* DATA */

  char            addr_str[IPADDR_MAX+1];
  struct hostent *hp;

  /* ACTION */

  parse_cmd_line (argc, argv, addr_str, IPADDR_MAX);

  hp = get_host_entry (addr_str);

  print_host_info (hp);
}
