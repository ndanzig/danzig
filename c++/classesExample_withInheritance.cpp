#include "iostream.h"

class fish
{

  fish();
protected:
  fish(char * theName, int theAge); //must not be private, else goldfish can't call it.
  static int NumofInstances; 
public:
  char* name;
  int age;
  static fish * create(){
    if (NumofInstances == 0)
      {
	NumofInstances++;
	return (new fish());
      }
    else
      return ((fish*)NULL);

}
};

int fish:: NumofInstances = 0;


class goldfish : public fish
{
public:
  int size;
  goldfish(char * theName, int theAge, int theSize) :size(theSize) , fish (theName, theAge)
  {
  }
};


fish::fish()
{ 
  age=50;
  name=NULL;
}


fish::fish(char * theName, int theAge)

{
  age=theAge;
  int len=strlen(theName);
  name = new char[len+1];
  strcpy(name, theName);
}




int main()
{

  goldfish nemo("Nemo",9,10);
  
  fish * marlin =  fish::create();
  fish * tarpon =  fish::create(); // will not create another instance

  cout<<nemo.name<<endl;
  cout<<nemo.age<<endl;
  cout<<nemo.size<<endl;

  if (marlin !=NULL) //will print 50.
    cout<<(marlin->age);
  if (tarpon !=NULL)  // will fail since tarpon will be NULL
    cout<<(marlin->age);

  goldfish spotty("Spotty",19,110); // will get created because goldfish can call 
                                  //fish parameterized constructor many times.
}