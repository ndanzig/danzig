#include "iostream.h"

class Fish
{
public:
  int ID;
  static const int stam=9; //const static can be initialized inline 
  class scales  //nested class
  {
  public:
    int NumScales;
    static char color;
    scales(){NumScales=Fish::stam;      }

  }; //create an instance
  scales s;
  Fish():ID(1){}
}a ;//create a Fish instance

char Fish::scales::color='g';

int main()
{




  Fish myF;
  cout<<(Fish::scales::color);
  cout<<endl<< a.s.color;
  cout<<endl<< myF.ID;
  cout<<endl<< myF.s.NumScales<<endl;


  Fish::scales *ptr= new Fish::scales();
  cout<<(ptr->NumScales);

  return 1;
}

