#include <iostream.h>


class process
{
  int burstTimeOrig;
  int arrivalTimeOrig;
  int priorityOrig;

public:
  int priority;
  int usingCPU;
  int timeslice; //how much time of my slice I have used so far
  int burstTime;
  int pid;
  int arrivalTime;
  int waitTime; 
  int RRwaitTime; //how much I have waited since I last had CPU

  process * next;

  process(int bt, int pid, int at, int pr)
  {
    priority=priorityOrig=pr;
    usingCPU=0; 
    burstTime=burstTimeOrig=bt;
    this->pid=pid;
    arrivalTime=arrivalTimeOrig=at;
    waitTime=0;
    timeslice=0;
  }
  void print()
  {
    if (usingCPU==1)
       cout<<"Using CPU ";
    cout<<" pid:"<<pid;
    cout<<" burstTime:"<<burstTime;
    cout<<" timeslice:"<<timeslice;
    cout<<" priority:"<<priority;
    cout<<" arrivalTime:"<<arrivalTime;
    cout<<" waitTime:"<<waitTime<<endl; 
  }

  void reset()
  {
    priority=priorityOrig;
    arrivalTime=arrivalTimeOrig;
    burstTime=burstTimeOrig;
    waitTime=0; 
    usingCPU=0;
    timeslice=0;
  }


};

class PList
{
private:
  int Time;
  int TimeSlice;
  int agingTime;

public:
  process * head;


  PList (int num, int ts, int ag)
  {
    Time = 0;
    TimeSlice=ts;
    agingTime=ag;
    head=NULL;
    int pid=1;
    while (num)
      {
	int bt,at, pr;
	cout<<"enter process's burst time \n";
	cin>>bt; 
	cout<<"enter process's arrival time \n";
	cin>>at;
	cout<<"enter process's priority \n";
	cin>>pr;
	if (head==NULL)
	  {
	    head=new process(bt,pid,at,pr);
	  pid++;
	  num--;
	  }
	else
	  {
	    process *temphead=head;
	    while (temphead->next)
	      temphead=temphead->next;
	    temphead->next=new process(bt,pid,at,pr);
	    pid++;
	    num--;
	  }
      }
  }//end constructor

  //  PList(int num) : PList(num, 2, 2)  {   }


  ~PList()
  {
    process * temp=head, *del;
    while(temp)
      {
	del=temp;
	temp=temp->next;
	delete del;
      }

  }
  void print()
  {
    process * temp=head;
    while(temp)
      {
	temp->print();
	temp=temp->next;
      }
  }

  void reset()
  {
    process * temp=head;
    while(temp)
      {
	temp->reset();
	temp=temp->next;
      }
    Time=0;
  }

  process * findPriorityJob()
  {

    process * highestPr= NULL;
    process * temp=head;
    while(temp)
      {
	if (temp->arrivalTime <= Time  &&  temp->burstTime > 0 ) //eligable to get CPU
	  {
	    if (highestPr==NULL)
	      highestPr=temp;
	    else if (temp->priority  < highestPr->priority)
	      highestPr=temp;
	  }
	temp=temp->next;
      }
    return highestPr;
}

  process * findRRJob()
  {

    process * job= NULL;
    process * temp=head;
    while(temp)
      {
	if (temp->arrivalTime <= Time  &&  temp->burstTime > 0 ) //eligable to get CPU
	  {
	    if (temp->timeslice!=0 ) // it is still his turn to use cpu
	      return (temp);
	    if (job==NULL)
	      job=temp;
	    else if (temp->RRwaitTime > job->RRwaitTime) //temp has been waiting longer
	      job=temp;
	  }
	temp=temp->next;
      }
    return job;
}


  process * findShortestJob()
  {
    process * shortest= NULL;
    process * temp=head;
    while(temp)
      {
	if (temp->arrivalTime <= Time  &&  temp->burstTime > 0 ) //eligable to get CPU
	  {
	    if (shortest==NULL)
	      shortest=temp;
	    else if (temp->burstTime < shortest->burstTime)
	      shortest=temp;
	  }
	temp=temp->next;
      }
      return shortest;
}
  void assignCPUtoProcess(process *p)
  {
    process * temp=head;
    while(temp)
      {
	if (temp == p)
	  {
	    p->usingCPU=1;
	  }
	else
	  temp->usingCPU=0;
	temp=temp->next;
      }
  }

  void updateProcessesandTime()
  {
    process * temp=head;
    while(temp)
      {
	if (temp->usingCPU==1)
	  {
	    temp->burstTime--;
	    temp->timeslice++;
	    temp->timeslice=temp->timeslice%TimeSlice;//reset timeslice to zero if needed
	    temp->RRwaitTime=0;//reset to zero since previous waiting is not relevant
	  }
	else if (temp->arrivalTime <= Time &&  (temp->burstTime)>0 )
	  {
	    temp->waitTime++;
	    temp->RRwaitTime++;
	    if ((temp->waitTime)%agingTime==0  && temp->priority>0)
	      temp->priority--;
	  }
	temp=temp->next;
      }
    Time++;
    
  }

  void fillArray(int ** ar, int index)
  {
    ar[1][index]=Time;
    process * temp=head;
    while(temp)
      {
	if (temp->usingCPU==1)
	  {
	    ar[0][index]=temp->pid;
	    return;
	    }
	temp=temp->next;
      }
    return;
  }


};//end class PList

void printArray(int ** ar, int size)
{
  int i=0;
  for (i=0; i<size;i++)
    {
      cout<<ar[0][i];
      if (i>=8)
	cout<<" "; 
    }
  cout<<endl;
  for (i=0; i<size;i++)
    {
      cout<<ar[1][i];
    }
  cout<<endl;

}


int main()
{

  int num, seconds,i,ts,ag;
  int **array = new int* [2];
  cout<<"hello, how many processes?\n";
  cin>>num;
  //  PList mylist(num);
  cout<<"enter time slice\n";
  cin>>ts;
  cout<<"enter aging time\n";
  cin>>ag;

  PList mylist(num, ts, ag);

  process * shortest;

  cout<<"how many seconds to run?"<<endl;
  cin >>seconds;
  array[0]=new int [seconds];
  array[1]=new int [seconds];

  for (i=0;i<seconds;i++)
    {
      shortest=mylist.findShortestJob();
      mylist.assignCPUtoProcess(shortest);
      mylist.updateProcessesandTime();      
      mylist.fillArray(array,i);

    }

  printArray(array,seconds);

  mylist.reset();
  cout<<"Now do priority"<<endl;
  for (i=0;i<seconds;i++)
    {
      shortest=mylist.findPriorityJob();
      mylist.assignCPUtoProcess(shortest);
      mylist.updateProcessesandTime();      
      mylist.fillArray(array,i);

    }

  printArray(array,seconds);
  mylist.reset();
  cout<<"Now do Round Robin"<<endl;
  for (i=0;i<seconds;i++)
    {
      shortest=mylist.findRRJob();
      mylist.assignCPUtoProcess(shortest);
      mylist.updateProcessesandTime();      
      mylist.fillArray(array,i);
    }

  printArray(array,seconds);


  return 1;
}












