#include "iostream.h"

/*template <typename   var>
var multiply ( var var1 , var var2)
{

var result;

result = var1 * var2;


 return result;
  }
*/

template <typename   var , typename varvar>
var  multiply ( var var1 , varvar var2)
{

var result;

result = var1 * var2;


 return result;
  }


int main()
{

  int a=10, b=20;
  float c=3.5, d=5.5;
  a=multiply (a,b);
  
  cout<<a<<endl;
  c=multiply(c,d);
  cout<<c<<endl;
  c=3.5;
  c=multiply(c,a);
  cout<<c<<endl;

  return 1;
}



