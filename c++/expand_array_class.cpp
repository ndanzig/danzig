//Nachum Danzig (Jan 2012)
#include <iostream.h>

class Paintbrush{
public:
  int width;
  int bristlecount;
  Paintbrush():width(0),bristlecount(0)
  {count++;}
  ~Paintbrush(){count--;}
  static int count;
  void print();


};

void Paintbrush::print()
{
  cout<<"Width is "<<width<<" bristle count is "<<bristlecount<<endl;
}

int Paintbrush::count = 0;

Paintbrush * expandarray(int oldsize, int newaddition, Paintbrush * array)
{
  int i=0, limit;
  Paintbrush * ptr = new Paintbrush [oldsize+newaddition];
  limit = oldsize + ( newaddition<0?newaddition:0);// subtract newadditon only if it is negative
  for ( ;i<limit ;i++ )
    {
      ptr[i]=array[i];
    }

  if (array)
    delete []array;
  return ptr;

}

void printarray(int size, Paintbrush *arr)
{
  cout<<"Array count is "<<(Paintbrush::count)<<endl;
  int i;
  for(i=0;i<size;i++)
    {
      arr[i].print();
    }

  return;
}

int main ()
{
  int size;
  int i,temp;
  Paintbrush * ar = NULL;
  cout<<"What size array do you want?";
  cin>>size;
  ar=expandarray(0,size,ar);
  for(i=0;i<size;i++)
    {
      cout<<"enter width and bristle count\n";
      cin>>ar[i].width>>ar[i].bristlecount;
    }

  printarray(size,ar);

  while (true)
    {
      cout<<"By what amount do you want to expand the array? Enter 0 to quit.";
      cin>>temp;
      if(!temp)
	break;
      ar=expandarray(size,temp,ar);
      
      for(i=size;i<size+temp;i++)
	{
	  cout<<"enter width and bristle count\n";
	  cin>>ar[i].width>>ar[i].bristlecount;
	}
      size=size+temp;
      printarray(size,ar);
    }
  if (ar)
    delete [] ar;
  return 1;

}
