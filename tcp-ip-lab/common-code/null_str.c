/* FILE: null_str.c -- return TRUE either if pointer is null, or if it
 * points to a null string.
 **************************************************************/

#include <string.h>

int null_str (char *ptr)
{
  if      (ptr == NULL)       {return (1);}
  else if (strlen (ptr) == 0) {return (1);}
  else                        {return (0);}
		      
}
