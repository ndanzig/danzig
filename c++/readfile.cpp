#include <iostream>

using std::cout;
using std::cin;
using std::ios;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;
#include <cstdlib>



int main()
{
  int account;
  char name[30];
  double balance;

  ifstream ClientFile( "data.dat" , ios::in);

  cout<< "now we read the file\n";

  while (ClientFile >>account >> name >> balance)
    {
      cout << "account number "<<account
	   << " name " <<name <<" balance "<<balance<<endl;

    }


 return (1);
}