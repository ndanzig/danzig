/* FILE: stdarg-regular.c -- stdarg Example.  
		stdarg is the ANSI C equivalent to the varargs
		mechanism.  It's syntax differs slightly.  This works
		in GNU C, but not in SunOS cc.
*/

#include <stdio.h>
#include <stdarg.h>

#define TYPE_INT   0
#define TYPE_FLOAT 1
#define TYPE_STR   2
#define TYPE_END   3

/*-------------------------------- */
/* display_args -- display the type & value of the arguments. */
/*                 Expects a type followed by the argument itself. */
/*-------------------------------- */
void  display_args (int type, ...)
{
  /*-------------------------------- */
  /* DATA */
  /*-------------------------------- */

  int     abort;
  va_list ap;
  int     arg_int;
  char   *arg_str;
  double  arg_float;
  /* int     type; */

  /*-------------------------------- */
  /* ACTION */
  /*-------------------------------- */

  printf ("^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
  va_start (ap, type);
  abort = 0;
  /* type = va_arg(ap, int); */
  while ( (type != TYPE_END) && ! abort )
    {
      switch (type)
	{
	case TYPE_INT:
	  arg_int = va_arg(ap, int);
	  printf ("    Integer argument: %d\n", arg_int);
	  break;
      
	case TYPE_FLOAT:
	  arg_float = va_arg(ap, double);
	  printf ("    Float argument: %f\n", arg_float);
	  break;
      
	case TYPE_STR:
	  arg_str = va_arg(ap, char *);
	  printf ("    String argument: %s\n", arg_str);
	  break;

	default:
	  printf ("    Invalid arg type %d!!!\n", type);
	  abort = 1;
	  break;
	}

      type = va_arg(ap, int);
    }
  va_end (ap);
  printf ("vvvvvvvvvvvvvvvvvvvvvvvvvvvv\n\n");

  return;
}


/*-------------------------------- */
/* MAIN */
/*-------------------------------- */
int main ()
{
  display_args (TYPE_INT, 5, TYPE_FLOAT, 2.3, TYPE_STR, "Hello", TYPE_END);

  display_args (TYPE_FLOAT, -35.23, TYPE_INT, -44, TYPE_END);

  display_args (TYPE_STR, "My IQ is", TYPE_FLOAT, 0.45, TYPE_END);

  exit(0);
}
