#include <stdio.h>

movetower(int discs, int start, int hold, int end);

main()
{
   int discs;
  while(1){
   printf("how many numbers?\n");
  scanf("%d",&discs);
  movetower(discs,1,2,3);
    }
}

movetower(int discs, int start, int hold, int end)
{
  if(discs==1)
    {
      printf("%d -> %d\n ",start,end);
      return;
    }
  else
    {
      movetower(discs-1,start,end,hold);
      movetower(1,start,hold,end);
      movetower(discs-1,hold,start,end);

    }

}
