#include "iostream.h"
class Fish
{
private:
  int priv_id;
  /*virtual*/ void funct(){cout<<"Don't run me!!";} 
protected:
  int prot_id;

public:
  int ID;
  Fish(int id):ID(id),priv_id(id+1), prot_id(id+2){}
} ;

class GoldFish : private Fish
{
public:
  void funct(){cout<<endl<<"You ran me!!";}

  int getprot_id(){return prot_id;}//can access protected (or public) parent attribute 
  GoldFish(int id):Fish(id){}
};


int main()
{
  GoldFish GF(33);
  cout<<endl<< GF.getprot_id();
  GF.funct();

  Fish *fPtr = &GF; 
  //  fPtr->funct();//this won't work whether or not parents funct is virual.

  return 1;
}
