#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 200
int main()
{
  FILE *pfp;
  char buf[BUFSIZE];
  char command[BUFSIZE];
  int c=1;

  while(1)
    {
      getcwd(buf,BUFSIZE);
      printf("%s>",buf);

      fgets(command,BUFSIZE, stdin);
      command[strlen(command)-1]=0;//remove \n
      strcpy(buf,getenv("HOME"));
      if (strcmp(command,"cd")==0 ||strcmp(command,"cd ~")==0 ||strcmp(command,"cd ~ ")==0 )
	{
	  if(-1==chdir(buf))
	    printf("cant chdir\n");
	  //	  else
	  //printf ("changed dir!\n");
	  continue;
	}
      else
	{
	  if (command[0]=='c'&&command[1]=='d'&&command[2]==' ')
	    {
	      if(-1==chdir(&(command[3])))
		printf("cant change dir");
	      continue;
	    }
	}
 if ( ( pfp=popen ( command, "r" ) ) == NULL )
    {
      fprintf ( stderr, "The command failed\n" );
      exit ( 1 );
    }
  else
    {
      while ( fgets ( buf , BUFSIZE , pfp ) != NULL )
	{
	printf ( "%s",  buf );
	}
      pclose ( pfp );
    }


    }
  return 0;
}
