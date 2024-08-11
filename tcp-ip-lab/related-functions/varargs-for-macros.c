/* FILE: varargs-for-macros.c*/
/* */
/*       This actually uses a GNU C extension to implement varargs for */
/*       macros.  */

#include <stdio.h>
#include <varargs.h>

#define dbg(fmt, args...)  fprintf (stderr, fmt, args)
  
char str[] = "Hello there";

int main ()
{
  int  i;

  i = 55;
  dbg ("i = %d\n", i);

  i = 23;
  dbg ("i = %d, str = /%s/\n", i, str);

  exit(0);
}
