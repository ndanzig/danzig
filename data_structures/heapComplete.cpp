//Heap Binary Tree

    #include <math.h>
    #include <cstdlib>
    #include <iostream>
    using namespace std;

    class Node
    {
    public:
      int value;
      Node *parent;
      Node *left; 
      Node *right;
      Node(int value);
      Node(Node *);
      ~Node(){};

      void swap(Node *);
    };

void Node::swap(Node * other)
{
  int hold = other->value;
  other->value=value;
  value= hold;
}

Node::Node(int value)
{
  this->value = value;
  parent = NULL;
  right = NULL;
  left = NULL;
}

Node::Node(Node  * other)
{
  this->value = other->value;
  parent = other->parent;
  right = other->right;
  left = other->left;
}

    class heap
    {
      Node *head;
      int counter;
      bool insertedflag;      
      bool promotedflag;      
    public:
      heap() {head = NULL; counter = 0; insertedflag=0; promotedflag=0;}
      ~heap(); 
      bool insert(Node *newnode);
      bool inserthelper (Node *nn, Node *cn, int level); 
      void upHeap(Node *nn);

      Node * pop( );
      bool pophelper(Node *, int);
      void downHeap(Node *);
      void printhelper(Node *c);
      void print();
    };


heap::~heap()
{

}

bool heap::inserthelper(Node *nn, Node *cn, int level)
{
  if (insertedflag) return 0;
         
  if (counter < (pow(2, level)-1)) return 0;//is current level too low down to be used
         
  if (!(cn->left))
    {
      cn->left = nn;
      nn->parent = cn;
      counter++;
      insertedflag = 1;
      return 1;
    }
  if (!(cn->right))
    {
      cn->right = nn;
      counter++;
      nn->parent = cn;
      insertedflag = 1;
      return 1;
    }
         
  /*if (*/
  inserthelper(nn, cn->left, level + 1);       //) == 0)
  inserthelper(nn, cn->right, level + 1);
  return 0;
}

bool heap::insert(Node *newnode)
{
  if (!head)
    {
      head = newnode;
      cout<<"Head was added."<<endl;
      counter++;
      return 1;
    }     
  inserthelper(newnode, head, 1);
  insertedflag = 0;
  upHeap(newnode);
  return 1;        
}//end insert function



void heap::upHeap(Node *nn)
{
  int hold;
  if (nn->parent == 0)
    return;
  if (nn->value < nn->parent->value)
    return;
  hold = nn->value;
  nn->value = nn->parent->value;
  nn->parent->value = hold;
  upHeap(nn->parent);
  return;
}
void heap::downHeap(Node *cn)
{
  if(cn->left && cn->right  )
    {
      if (cn->left->value >  cn->right->value )
      {
	if (cn->value < cn->left->value)
	  {
	    cn->swap(cn->left);//swap cn with cn->left
	    downHeap(cn->left);
	  }
	else
	  return;
      }

      else
      {
	if (cn->value < cn->right->value)
	  {
	    cn->swap(cn->right);//swap cn with cn->right
	    downHeap(cn->right);
	  }
	else
	  return;
      }
    }
 else //at least one child is NULL  
  {
    if (cn->left && cn->left->value > cn->value)
	    cn->swap(cn->left);//swap cn->left->value with cn->value 
    if (cn->right &&  cn->right->value > cn->value)
 	    cn->swap(cn->right);
    return;
  }
}

void heap::printhelper(Node *c)
{
  if (c == NULL) return;
  printhelper(c->left);
  cout<<c->value<<", ";
  printhelper(c->right);
}

void heap::print()
{
printhelper(head);
}

Node* heap::pop()
    {
      if (!head)
	return ((Node*)0);
      Node *temp =  new Node(head);
  pophelper(head, 1);
  promotedflag = 0;
  downHeap(head);
  return temp    ;
    }

bool heap::pophelper(Node *cn, int level)
{
  if (promotedflag) return 0;
         
  if (cn == NULL) return 0;

  if (pow(2,level) > counter ) // current level is down far enough
    {

      if(cn->parent->right==cn) //detatch cn
	cn->parent->right=NULL;
      else
	cn->parent->left=NULL;

      head->value= cn->value;//copy value of cn into head
      delete cn; //free memeory of cn
      promotedflag = 1;
      return 1;
    }


  pophelper(cn->right, level + 1);
  pophelper(cn->left, level + 1);  
  return 0;
}


int main(int argc, char *argv[])
{
  heap myheap;
  Node *ptr50 = new Node(50);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  ptr50 = new Node(60);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  ptr50 = new Node(70);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  ptr50 = new Node(80);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  ptr50 = new Node(160);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  ptr50 = new Node(170);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  myheap.pop();
  myheap.print();
  cout<<endl;


     
  return 1;
}