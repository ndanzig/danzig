
#include <iostream>
using namespace std;

class student
{
private:
  char* name;
public:

  int age;
  student * next;
  student();
  ~student();
  student(char * theName, int theAge);
  void copy( student other);
  char * getName();
  void assignName(char * name);
};

void printArray(student *);
student * removeStudent(char * name, student ** start);

student::student()
{ 
  age=0;
  name=NULL;
  next = NULL;
}
student::~student()
{ 
  if(name!=NULL)
    delete [] name;
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
   int flag;
  int i =0,age;
  start=new student();
  cout<<"enter name";
  cin>>name;
  start->assignName(name);
  cout<<"enter age";  
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
      cout<<"enter non-zero to continue";
      cin>>flag;
    }
  
  printArray(start);
      cout<<"enter name of student to delete";
      cin>>name;
      temp=removeStudent(name, &start);
      if(temp)
	{
	  cout<<"We deleted student "<<temp->getName()<<endl;
	  delete temp;
	}
      else
	cout<<"Not found"<<endl;
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


student * removeStudent(char * name, student ** startPtr)
{
  student * temp, *previous;
  if( *startPtr==NULL)//null list
    return *startPtr;
  previous=temp=*startPtr;
  if (strcmp(name, (*startPtr)->getName())==0)// remove head
    {
      *startPtr=(*startPtr)->next;
    }
  else
    {
      temp=temp->next;
      while(temp?(strcmp(name, temp->getName())!=0):0)   //didn't find it //could also just use &&
	{
	  previous=temp;
	  temp=temp->next;

	}//end while
      if (temp)//we found it and it's temp! 
	{
	  previous->next=temp->next;
	}
    }   //end else
  return temp;
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
