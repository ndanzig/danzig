#include "iostream.h"

class myInt
{
public:
  int num;
  myInt(int a):num(a){}
  float divide(int b);
  myInt operator-( const int b);//member
  friend myInt operator+(const myInt a,  const int b);//could be member, not friend
  friend myInt operator+(const int b, const myInt a); //must be friend bec. lval is not myInt
};

myInt myInt::operator-(const  int b)
{
  return myInt (num - b);
}

myInt operator+( const  int b, const myInt a)
{
    return myInt(a.num +b);
    //  return myInt(a+b);

}

myInt operator+( const myInt a, const  int b)
{

  return myInt (a.num + b);

}

float myInt::divide(int b)
{

  if (b==0)  
    throw -1;
else
  return (float)num/b;
}


int main()
{
  myInt a(17);
  
  cout<<a.divide(10)<<endl;

  a=a+10;
  cout<<a.num<<endl; 
  a=a-1;
  cout<<a.num<<endl; 
  a=10+a;
  cout<<a.num<<endl; 
 
  return 1;

}
