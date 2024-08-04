#include "iostream.h"

int main()

{
  int Gues = 10, response, ul=20, ll=0;
  cout<<"pick a number from 0 to 20\n";
  cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
  cin>>response;
  if (response == 1)
    {
      ll=Gues+1;
      Gues=(ll+ul)/2;
      cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
      cin>>response;
      if (response == 1)
	{
	  ll=Gues+1;
	  Gues=(ll+ul)/2;
	  cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	  cin>>response;
	  if (response == 1)
	    {
	      ll=Gues+1;
	      Gues=(ll+ul)/2;
	      cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	      cin>>response;
	    }
	  else if (response == 2)
	    {
	      ul=Gues-1;
	      Gues=(ll+ul)/2;
	      cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	      cin>>response;
	      
	    }
	  else
	    {
	      cout<<"Yes, I got it it right!!\n";
	      
	    }
	}
      else if (response == 2)
	{
	  ul=Gues-1;
	  Gues=(ll+ul)/2;
	  cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	  cin>>response;
	  if (response == 1)
	    {
	      ll=Gues+1;
	      Gues=(ll+ul)/2;
	      cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	      cin>>response;
	    }
	  else if (response == 2)
	    {
	      ul=Gues-1;
	      Gues=(ll+ul)/2;
	      cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	      cin>>response;
	      
	    }
	  else
	    {
	      cout<<"Yes, I got it it right!!\n";
	      
	    }
	  
	}
      else
	{
	  cout<<"Yes, I got it it right!!\n";
	  
	}
      
    }
  else if (response == 2)
    {
      ul=Gues-1;
      Gues=(ll+ul)/2;
      cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
      cin>>response;
      if (response == 1)
	{
	  ll=Gues+1;
	  Gues=(ll+ul)/2;
	  cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	  cin>>response;
	}
      else if (response == 2)
	{
	  ul=Gues-1;
	  Gues=(ll+ul)/2;
	  cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	  cin>>response;
	  
	}
      else
	{
	  cout<<"Yes, I got it it right!!\n";
	  
	}
      if (response == 1)
	{
	  ll=Gues+1;
	  Gues=(ll+ul)/2;
	  cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	  cin>>response;
	  if (response == 1)
	    {
	      ll=Gues+1;
	      Gues=(ll+ul)/2;
	      cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	      cin>>response;
	    }
	  else if (response == 2)
	    {
	      ul=Gues-1;
	      Gues=(ll+ul)/2;
	      cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	      cin>>response;
	      
	    }
	  else
	    {
	      cout<<"Yes, I got it it right!!\n";
	      
	    }
	}
      else if (response == 2)
	{
	  ul=Gues-1;
	  Gues=(ll+ul)/2;
	  cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	  cin>>response;
	  if (response == 1)
	    {
	      ll=Gues+1;
	      Gues=(ll+ul)/2;
	      cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	      cin>>response;
	    }
	  else if (response == 2)
	    {
	      ul=Gues-1;
	      Gues=(ll+ul)/2;
	      cout<<"Is your number (1)higher than "<<Gues<< " or (2)lower or (3) am I right?\n";
	      cin>>response;
	      
	    }
	  else
	    {
	      cout<<"Yes, I got it it right!!\n";
	      
	    }
	}
      else
	{
	  cout<<"Yes, I got it it right!!\n";
	  
	}
      
    }
  else
    {
      cout<<"Yes, I got it it right!!\n";
      
    }
  return 1;
}
