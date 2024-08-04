
#include <stdio.h>
#include <iostream.h>

  
int t_to_T( char* myString ) ;
int reversePrintString( char* myString ); 

int main()
{

char charlie[100]="this is a test string."; 
//t_to_T( charlie); 
//  cout<<charlie; 
 reversePrintString( charlie ); 
 //cout<<charlie; 

  //char ar[60]="greg";
  //cout<<ar;
 //ar="hheeee";
 //cout<<ar;

 //cin>>ar;
  // cout<<ar;



  
  return 1;
}


int reversePrintString( char* myString ) 
{ 
  for (int i = 0; myString[i] != NULL; i++); 
  for ( ; i >= 0; --i) 
    { cout<<myString[i]; 
    } 
  return 1; 
} 




int t_to_T( char* myString ) 
    { 
      for (int i = 0; myString[i] != NULL; i++) 
	{ 
	  if (myString[i]== 't') 
	    { 
	      myString[i]='T';
	      } 
    } 
  return 1; 
} 

