#include <stdio.h>
#include <string.h>

#define BUFMAX 128

int main ()
{
  int i;
  union myunion {
    double mydouble;
    int myint;
    char buff[8];
  };
  unsigned int c;

  union myunion number;
  number.mydouble= 360565656;
  for (i=0;i<8;i++)
    {
      c = number.buff[i];
      printf("byte %d is in octal %02x \n", i, c   ); 
    }
      printf("double is %f \n",  number.mydouble   );
       printf("int is %d \n",  number.myint   ); 
       ///-------------
  number.myint= 64;
  for (i=0;i<8;i++)
    {
      printf("byte %d is in hex %02x \n", i, number.buff[i]   ); 
    }
      printf("double is %f \n",  number.mydouble   );
       printf("int is %d \n",  number.myint   ); 
       printf("the int as hex is %02X \n",  number.myint   ); 
       printf("the int as octal is %04o\n",  number.myint   ); 

       // Now convert the number 







  return 1;
}