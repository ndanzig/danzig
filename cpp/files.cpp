#include <iostream>

using std::cout;
using std::cin;
using std::ios;
using std::cerr;
using std::endl;
#include <fstream>
using std::ofstream;
using std::ostream;
using std::fstream;
using std::ifstream;
#include <cstdlib>


struct account
{
  int number;
  char name[30];
  double balance;

};

int main()
{
  account temp;

  fstream ClientFile( "data.dat", ios::out | ios::in);

  cout << " enter account number, name, balance. \n (eof (^Z) to end)";

  while ( cin >> temp.number >> temp.name >> temp.balance )
   {
     ClientFile <<temp.number<<' '<<temp.name <<' ' <<temp.balance<<'\n';
     cout<<":";

   }

  cout<< "now we read the file\n";

  ClientFile.seekg(0);
  while (ClientFile >>temp.number>> temp.name >> temp.balance)
    {
      if (strcmp(temp.name, "mary")==0)
	{ 
	  cout << "I like the name Mary"<<endl;
	} 
      cout << "account number "<<temp.number
	   << ", name " << temp.name <<", balance "<<temp.balance<<endl;

    }


 return (1);
}
