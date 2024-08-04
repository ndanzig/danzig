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
      ~Node();
    };

Node::Node(int value)
{
  this->value = value;
  parent = NULL;
  right = NULL;
  left = NULL;
}

    class heap
    {
      Node *head;
      int counter;
      bool insertedflag;  //flag to prevent inserting twice
    public:
      heap() {head = NULL; counter = 0; insertedflag=0;}
      ~heap(); 
      bool insert(Node *newnode);
      bool inserthelper (Node *nn, Node *cn, int level); 
      void upHeap(Node *nn);
      /*      
      Node *pop();
      void downHeap(Node *);
      */     
      void printhelper(Node *c);
      void print();
    };

heap::~heap()
{
}

bool heap::inserthelper(Node *nn, Node *cn, int level) //params: new_node , current_node, current_level
{
  if (insertedflag) return 0; //stop if already inserted in another recurse
         
  if (counter < (pow(2, level)-1)) return 0;//is current level too low down to be used
         
  if (!(cn->left))// we are not too low down and we found a free spot, must be on lowest acceptable level
    {
      cn->left = nn; //insert on left
      nn->parent = cn;
      counter++;//we added a node
      insertedflag = 1;//idicate that we inserted
      return 1;
    }
  if (!(cn->right))
    {
      cn->right = nn;//insert on right
      counter++;
      nn->parent = cn;
      insertedflag = 1;
      return 1;
    }
         
  //if we got this far we need to recurse , i.e. go down one more level
  inserthelper(nn, cn->left, level + 1);       //go left first since we always fill left side first
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
  insertedflag = 0;//after inserting , reset the static variable
  upHeap(newnode);
  return 1;        
}//end insert function



void heap::upHeap(Node *nn)//pointer to new_node in its new location
{
  int hold;
  if (nn->parent == 0)//it must be in head position
    return;
  if (nn->value < nn->parent->value)// it is smaller than parent, finished
    return;
  hold = nn->value;//swap the values, leave the nodes intact, this proves to be easier
  nn->value = nn->parent->value;
  nn->parent->value = hold;
  upHeap(nn->parent);
  return;
}
/*
    void heap::downHeap()
    {
    }
*/
void heap::printhelper(Node *c)
{
  if (c == NULL) return;
  printhelper(c->left);
  cout<<c->value<<", ";
  printhelper(c->right);
}

void heap::print()
{printhelper(head);}
/*
    Node* heap::pop()
    {
    }
*/
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
  ptr50 = new Node(90);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  ptr50 = new Node(100);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  ptr50 = new Node(110);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  ptr50 = new Node(120);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  ptr50 = new Node(130);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  ptr50 = new Node(140);
  myheap.insert(ptr50);
  myheap.print();
  cout<<endl;
  ptr50 = new Node(150);
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
     
  system("PAUSE");
  return EXIT_SUCCESS;
}
