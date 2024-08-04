#include "iostream.h"
class Fish
{
private:
  int priv_id;

protected:
  int prot_id;

public:
  int ID;
  Fish(int id):ID(id),priv_id(id+1), prot_id(id+2){}
} ;

class GoldFish : public Fish
{
public:
  //  int getpriv_id(){return priv_id;}//illegal, cannot access private parent attribute 
  int getprot_id(){return prot_id;}//can access protected (or public) parent attribute 
  GoldFish(int id):Fish(id){}
};

class BlowFish : private Fish
{
public:
  int getprot_id(){return prot_id;}//can access protected (or public) parent attribute 
  BlowFish(int id):Fish(id){}
};


class SwordFish : protected Fish
{
public:
  int getprot_id(){return prot_id;}//can access protected (or public) parent attribute 
  SwordFish(int id):Fish(id){}
};



int main()
{




  Fish myF(19);
  cout<<endl<< myF.ID; //can access public attribute
  //  cout<<endl<< myF.prot_id; //illegal, cannot acces private/protected data through the instance
  GoldFish GF(33);
  cout<<endl<< GF.getprot_id();
  cout<<endl<<GF.ID;//can access parent's public attribute but not its private/protected attributes
  BlowFish BF(890);
  //cout<<endl<< BF.ID; //can't access even the  parent's public attribute because it is now private    
  cout<<endl<< BF.getprot_id() ;//but member function can access the public/protected attributes
  SwordFish SF(73);
  cout<<endl<< BF.getprot_id() <<endl;// member function can access the public/protected attributes
  //cout<<endl<< SF.ID; //can't access parent's public attribute because it is now protected 
  // (i.e grandchildren functions could potentially access them)
 


  return 1;
}

