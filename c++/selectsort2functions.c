#include <stdio.h>
int biggest(int *a , int size)
{
  int big=0, i;
  for (i=1;i<size;i++)
    {
      if(a[i]>a[big])
	big=i;
    }
  return big;
}

void select(int *a , int size)
{
  int i;
  int big, hold;
  for (i=0; i<size  ;i++)
    {
      big =biggest(a, size-i);
      hold = a[big]; //swap
      a[big]=a[size-i-1];
      a[size-i-1]=hold;
    }
}


int main()
{
  int i=0;
  int array[]={14,5,6,2,1,7,9,0};
  select(array,8);
  return 0;
}