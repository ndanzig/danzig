/* FILE: varargs-pass-it-on.c

	This demonstrates a subroutine getting a varargs argument &
	passing on the varargs argument to another routine.   To do
	this, we must call vfprintf instead of fprintf.

	This compiled under both SunOS cc & GNU C.  But I tested it
	only under SunOS.
*/

#include <stdio.h>
#include <varargs.h>

#define TYPE_INT   0
#define TYPE_FLOAT 1
#define TYPE_STR   2
#define TYPE_END   3

char prefix[] = "DEBUG>> ";
char suffix[] = "\n\n";

/*-------------------------------- */
/* dbg -- print debug message.  Same arguments as printf. */
/*-------------------------------- */
/*VARARGS0*/
void  dbg (va_alist)
     va_dcl
{
  /*-------------------------------- */
  /* DATA */
  /*-------------------------------- */

  va_list   ap;
  char     *format;

  /*-------------------------------- */
  /* ACTION */
  /*-------------------------------- */

  va_start (ap);
  format = va_arg (ap, char *);
  fprintf (stderr, prefix);
  vfprintf (stderr, format, ap);  /* Need vfprint instead of frpintf! */
  fprintf (stderr, suffix);
  va_end (ap);

  return;
}


/*-------------------------------- */
/* MAIN */
/*-------------------------------- */
int main ()
{
  int age;

  dbg ("My name is %s & I'm %d years old", "Haim", 40);
  dbg ("%f * %d / %d = %f\n", 55.55, 5, 10, (55.55 * 5 / 10) );

  exit(0);
}
