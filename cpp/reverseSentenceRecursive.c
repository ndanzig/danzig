#include <stdio.h>

void reverse(char *p, int i);
int main()
{
  char array[200]={"This is a very long sentence."};
  reverse(array, 29);
  printf("%s \n",array);
  return;
}

void reverse(char *p, int i)

{
  char hold;
  if (i < 1)

     return;
  else
    {
      hold = *p;
      *p=p[i-1];
      p[i-1]=hold;
      reverse(p+1,i-2);

    }






}
