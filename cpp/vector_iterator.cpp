// stl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" 
#include <iostream> 
#include <vector> 
#include <ctime> 

using namespace std; 

int _tmain(int argc, _TCHAR* argv[]) 
{
	int	p, n =10,w=0; 
	vector<int> v; 				//Populate v here...
	for	(int y=0; y<n; y++)		//initilize 
		v.push_back(y);
	vector<int>::iterator i; 
	vector<int>::reverse_iterator j; 
	int	total = 0; 
	for (i = v.begin(); i != v.end(); i++,w++) 
	{
		total += *i; 
		//v[w]; 
	}
	cout<<total<<endl;
	for	(j = v.rbegin(); j != v.rend(); j++) 
	{
		p=*j;
		cout<<p<<endl;
	}
	v.push_back(200);
//	v.erase(total=0;
	for	(i = v.begin(); i != v.end(); i++,w++) 
	{
		total += *i; 
		//v[w]; 
	}
	cout<<total<<endl;
	for	(j = v.rbegin(); j != v.rend(); j++) 
	{
		p=*j;
		cout<<p<<endl;
	}
	return 0; 
}



int main ()
{
  // constructors used in the same order as described above:
  list<int> first;                                // empty list of ints
  list<int> second (4,100);                       // four ints with value 100
  list<int> third (second.begin(),second.end());  // iterating through second
  list<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  cout << "The contents of fifth are: ";
  for (list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
    cout << *it << " ";

  cout << endl;

  return 0;
}
