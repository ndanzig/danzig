///by vered rosengarten
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
bool safty(vector<int> ava ,vector<vector<int>>alloc ,vector<vector<int>> need,int m,int n)
{
	vector<int> work;
	vector<bool> finish; //to sign which process allready changed
	for (int y=0;y<n;y++)//initilize
		finish.push_back(0);
	bool check=1;
	for (int i=0;i<m;i++)
		work.push_back(ava[i]);//work=available

	for (int i=0;i<n;i++){
		check=1;
		//if the process didn't change yet
		if (finish[i]==0){
			for (int j=0;j<m&&check==1;j++){
				//if the need bigger than work
				if (need[i][j]>work[j])
					//not good & check the next process
					check=0;
			}
			//to sign if the process smaller than the work
			finish[i]=check;	
			//if it smaller
			if (finish[i]==1){
				for (int k=0;k<m;k++)
					//update the work values
					work[k]=work[k]+alloc[i][k];
				//next time check the processes from the begining
				i=-1;
			}}
	}
	for (int k=0;k<n;k++)
		//if there is a process that didn't changed
		if(finish[k]==0){
			//deadlock!
			cout<<"not safe!"<<endl;
			break;
		}
		else 
		{cout<<"the algoritem is safe!!"<<endl;
	return 1;}
	//if there is deadlock
	return 0;
}
void calling(vector<int> available,vector<vector<int>> max,vector<vector<int>>allocation,vector<vector<int>>need,vector<int>request, int m,int n)
{
	int num;
	srand  ((unsigned)time (NULL) );
	//check safty
	safty(available,allocation,need,m,n);
	//enter request
	for (int i=0;i<m;i++)//random request ,what usage from the resources(avail vaector) the process the user will select after that will request from the avail vector
	{
		num=rand()%10+1;
		request.push_back(num);
	}
	cout<<"the request is:"<<endl;
	for (int i=0;i<m;i++)
		cout<<request[i]<<" ";
	cout<<endl;
	//request for which process
	cout<<"which process to change?"<<endl;
	cin>>num;
	//change values after recieving the request
	for (int i=0;i<m;i++)
	{
		available[i]-=request[i];
		allocation[num][i]+=request[i];
		need[num][i]-=request[i];
	}
	bool dead;
	//check safty
	dead=safty(available,allocation,need,m,n);
	//if there is a deadlock
	if (dead==0)
	{
		//return to values before the request's changes
		for (int i=0;i<m;i++){
			available[i]+=request[i];
			allocation[num][i]-=request[i];
			need[num][i]+=request[i];
		}
	}
}
int main()
{
	//initilize
	int n;
	int m;
	int num,num2,num3;
	cout<<"enter number of processes and number of resources\n";
	cin>>n>>m;
	vector<int> available;
	vector<vector<int>> max;
	vector<vector<int>>allocation;
	vector<vector<int>>need;
	vector<int>request;
	max.resize(n);
	allocation.resize(n);
	need.resize(n);



	cout<<"enter available:"<<endl;
	//enter available values
	for (int i=0; i<m;i++){
		cin>>num;	
		available.push_back(num);
	}
	cout<<"enter max"<<endl;
	//enter max values
	for(int j=0;j<n;j++)
		for (int i=0; i<m;i++)
		{
			cin>>num2;
			max[j].push_back(num2);
		}
		cout<<"enter allocation"<<endl;
		//enter allocation values
		for(int j=0;j<n;j++){
			for (int i=0; i<m;i++){	
				cin>>num3;
				allocation[j].push_back(num3);

			}}
		//build "need"
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++)		
				need[i].push_back(max[i][j]-allocation[i][j]);
		}

		calling(available,max,allocation,need,request,m,n);
		cout<<endl<<endl;
		cout<<"do you want to check another one? press 1 to positive answer, press 0 to quit\n";
		cin>>num3;
		while(num3)
		{
			calling(available,max,allocation,need,request,m,n);
			cout<<endl<<endl;
			cout<<"do you want to check another one? press 1 to positive answer, press 0 to quit\n";
			cin>>num3;
		}


}
/*
enter number of processes and number of resources
5 3
enter available:
3 3 2
enter max
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
enter allocation
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
the algoritem is safe!!
the request is:
1 10 5
which process to change?
1
the algoritem is safe!!


do you want to check another one? press 1 to positive answer, press 0 to quit
1
the algoritem is safe!!
the request is:
10 2 3
which process to change?
2
not safe!


do you want to check another one? press 1 to positive answer, press 0 to quit
1
the algoritem is safe!!
the request is:
2 3 9
which process to change?
4
not safe!


do you want to check another one? press 1 to positive answer, press 0 to quit
1
the algoritem is safe!!
the request is:
5 3 2
which process to change?
3
the algoritem is safe!!


do you want to check another one? press 1 to positive answer, press 0 to quit
0
Press any key to continue . . .
*/


