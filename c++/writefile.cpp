#include <iostream>

using std::cout;
using std::cin;
using std::ios;
using std::cerr;
using std::endl;
#include <fstream>
using std::ofstream;
#include <cstdlib>



int main()
{
  int account;
  char name[30];
  double balance;

  ofstream ClientFile( "data.dat", ios::out );

  cout << " enter account number, name, balance. \n (eof (^Z) to end)";

  while ( cin >> account >> name >> balance )
   {
     ClientFile <<account<<' '<<name <<' ' <<balance<<'\n';
     cout<<":";

   }

 return (1);
}
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



int main()
{
  int account;
  char name[30];
  double balance;

  fstream ClientFile( "data.dat", ios::out | ios::in);

  cout << " enter account number, name, balance. \n (eof (^Z) to end)";

  while ( cin >> account >> name >> balance )
   {
     ClientFile <<account<<' '<<name <<' ' <<balance<<'\n';
     cout<<":";

   }

  cout<< "now we read the file\n";

  ClientFile.seekg(0);
  while (ClientFile >>account >> name >> balance)
    {
      if (strcmp(name, "mary")==0)
	{ 
	  cout << "I like the name Mary"<<endl;
	} 
      cout << "account number "<<account
	   << " name " <<name <<" balance "<<balance<<endl;

    }


 return (1);
}
