
#include "iostream.h"

class student
{
private:
  char* name;
public:

  int age;
  student * next;
  student();
  student(char * theName, int theAge);
  void copy( student other);
  char * getName();
  void assignName(char * name);
};

void printArray(student *);

student::student()
{ 
  age=0;
  name=NULL;
  next = NULL;
}

char * student::getName()
{
  return name;
}
void student::assignName(char * theName)
{

  if(this->name!=NULL)
    delete [] name;
  int len=strlen(theName);
  this->name = new char[len+1];
  strcpy(this->name, theName);

}

void student::copy( student  other)
{
  if(name!=NULL)
    delete [] name;
  int len=strlen(other.getName());
  name = new char[len+1];
  strcpy(name, other.getName());
  age=other.age;
  next=other.next;
}


student::student(char * theName, int theAge)

{
  age=theAge;
  int len=strlen(theName);
  name = new char[len+1];
  strcpy(name, theName);
  next=NULL;
}




int main()
{
  student * start, *temp;
  char* name = new char(100);
  int flag=true;
  int i =0,age;
  start=new student;
  cout<<"enter name";
  cin>>name;
  start->assignName(name);
  cin>>start->age;
  cout<<"enter non-zero to continue";
  temp=start;
  cin>>flag;
  while(flag)
    {
      cout<<"enter name";
      cin>>name;
      cout<<"enter age";
      cin>>age;
      temp->next=new student(name,age);
      temp=temp->next;
      cout<<"enter 0 to continue";
      cin>>flag;
    }
  
  printArray(start);
 
}

void printArray(student * theStart)
{
  while ( theStart!=NULL)
    {
      cout<<theStart->getName()<<endl;
      cout<<theStart->age<<endl;
      theStart=theStart->next;
   }
}

/*
void sort(student * array)
{
  int i =0;
  while ( (array[i+1].getName())!=NULL)
    {
      for( int j=0;(array[j+1].getName())!=NULL;j++)
	{
	  if( strcmp(array[j].getName(),array[j+1].getName())>0)
	    swap(array, j, j+1);
	} 
      i++;
    }
  
}
*/
