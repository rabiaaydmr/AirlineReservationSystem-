#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

int turn=0;
int Count=0;

int mat[2][50]={0};
void rabis(int &seatnumber,int &threadids)                 
{                
									        //This function write the agency number on the seat
	int row=seatnumber;
	int column=seatnumber/2-1;
	int column1=(seatnumber+1)/2-1;
	
	if(row%2==0)
	{
		
		mat[1][column]=threadids;
		
	}
	else
	{
		mat[0][column1]=threadids;
	}
	
	Count++;
}

void printmatrix()	//this function print the id
{
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 50; j++)
		{
        cout << mat[i][j];
	    }
	cout<<endl;
	}
}



int randomseatnumberfunc() // this function determines the seat number randomly
{
	int value = rand() %100+1; 
	return value;
}




bool check(int &seatnumber)                 // It checks the seat is full or not
{                
									
	int row=seatnumber;
	int column=seatnumber/2-1;
	int column1=(seatnumber+1)/2-1;
	
	if(row%2==0)
	{
		
		if(mat[1][column]==0)
			return true;
		else 
			return false;
		
	}
	else
	{
		if(mat[0][column1]==0)
			return true;
		else
			return false;
	}

}




void*func1(void*)     //The function of agency1
{
	int i;
	int idfirst=1;
	
	while(Count!=100)
	{
		
		while(turn!=0);
		cout<<"Thread1 is in the critical region"<<endl;
		int seatnbr=randomseatnumberfunc();
		
		while(Count!=100&&!check(seatnbr))
		{
			seatnbr=randomseatnumberfunc();
		}
		if (Count!=100)
		{
			rabis(seatnbr,idfirst);
		}
		
		cout<< "Seat number " << seatnbr << " is reserved by Travelagency1"<<endl;
		cout <<" Thread1 leaves the critical region"<<endl;
		turn=1;
	}
		
	   
	
}
	



void*func2(void*)   // The function of agency2
{
	int i;
	int idsecond=2;
	
	while(true&&Count!=100)
	{
		
		while(turn!=1);
		cout<<"Thread2 is in the critical region"<<endl;
		int seatnbr=randomseatnumberfunc();
		
		while(Count!=100&&!check(seatnbr))
		{
			seatnbr=randomseatnumberfunc();
		}
		
		if (Count!=100)
		{
			rabis(seatnbr,idsecond);
		}
		cout<< "Seat number " << seatnbr << " is reserved by Travelagency2"<<endl;
		cout <<" Thread2 leaves the critical region"<<endl;
		turn=2;
	}
		
	   
	
}

void*func3(void*)  // The function of agency3
{
	int i;
	int idthird=3;
	
	while(Count!=100)
	{
		
		while(turn!=2);
		cout<<"Thread3 is in the critical region"<<endl;
		int seatnbr=randomseatnumberfunc();
		
		while(Count!=100&&!check(seatnbr))
		{
			seatnbr=randomseatnumberfunc();
		}
		
		if (Count!=100)
		{
			rabis(seatnbr,idthird);
		}
		cout<< "Seat number " << seatnbr << " is reserved by Travelagency3"<<endl;
		cout <<" Thread3 leaves the critical region"<<endl;
		turn=0;
	}
		
	   
	
}



int main()
{
	
	pthread_t thread1, thread2, thread3;
	int id1,id2,id3;
	id1=1;
	id2=2;
	id3=3;
	pthread_create(&thread1,NULL, func1,NULL);
	pthread_create(&thread2,NULL, func2,NULL);
	pthread_create(&thread3,NULL, func3,NULL);


	while(Count!=100);
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);

	printmatrix();
	return 0;
}
