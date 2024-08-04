#include <iostream.h>

class Int  //simple class containing one int
{
public:
	int Integer;
	Int* next;
	Int ();
	Int (int a);
};
Int::Int(int a)
{
	Integer=a;
	next='\0';
}
Int::Int()// for use in a static Int declaration
{
	Integer=0;
	next='\0';
}

void addOne(Int** current, int Integer)  // must use Int** to get the real
  // address of the head of the list
{ //We need the following check because we can't check (*current)->next 
  //if the head is NULL!
  if((*current) != '\0') //we are not at the end of the list yet.
	{
		while ((*current)->next!='\0')//same as ((*current).next!='\0')
		{
			(*current)=(*current)->next;
			//move down the list by updating current
		}
		(*current)->next=new Int(Integer);//insert the new Int
		                                  // at the end of the list
		
	}
  else     //curent is NULL, i.e. First link.
		*current=new Int(Integer);


}
void print(Int* current)
{
		while (current!='\0')//same as ((*current).next!='\0')
		{
			cout<<current->Integer;
			current=current->next;
		}
	
}
int main()
{
	//Int a(7);
	Int* Head='\0';
	//Head=&a;//you could say (*Head).Integer=75 or a.Integer=78;
	//(*Head).next=new Int(8);//a.next=new Int(8)
	//(*((*Head).next)).next=new Int(9);
	for (int x=0; x<10; x++)
		addOne(&Head, x*75);
	print(Head);
}
