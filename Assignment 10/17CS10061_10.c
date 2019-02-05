#include <stdio.h>
#include<stdlib.h>

typedef struct _rwd
{
	int start_time;
	int service_time;
}reqWD;

typedef struct _RWD
{
	int requestID;
	reqWD atime;	
}REQWD;

typedef struct _rsd
{
	int service_time;
	int target_time;
}reqSD;

typedef struct _RSD
{
	int requestID;
	reqSD atime;	
}REQSD;

void mergeW(REQWD a[],int lower,int middle,int upper)
{
	REQWD b[1000],c[1000];
	int i,j,k,h1,h2;
	h1=0;
	for(i=lower;i<=middle;i++)
		b[h1++]=a[i];
	h2=0;
	for(i=middle+1;i<=upper;i++)
		c[h2++]=a[i];
	i=0;
	j=0;
	k=lower;
	while(i<h1 && j<h2)
	{
		if(b[i].atime.start_time>c[j].atime.start_time || ( (b[i].atime.start_time==c[j].atime.start_time) && (b[i].atime.service_time>c[j].atime.service_time) ) )
			a[k++]=c[j++];
		else
			a[k++]=b[i++];
	}
	while(i<h1) 
		a[k++]=b[i++];
	while(j<h2) 
		a[k++]=c[j++];

}

void mergeW_sort(REQWD a[],int lower,int upper)
{
	if(lower!=upper)
	{
		int middle=(lower+upper)/2;
		mergeW_sort(a,lower,middle);
		mergeW_sort(a,middle+1,upper);
		mergeW(a,lower,middle,upper);
	}
}


void mergeS(REQSD a[],int lower,int middle,int upper)
{
	REQSD b[1000],c[1000];
	int i,j,k,h1,h2;
	h1=0;
	for(i=lower;i<=middle;i++)
		b[h1++]=a[i];
	h2=0;
	for(i=middle+1;i<=upper;i++)
		c[h2++]=a[i];
	i=0;
	j=0;
	k=lower;
	while(i<h1 && j<h2)
	{
		if(b[i].atime.target_time>c[j].atime.target_time || ( (b[i].atime.target_time==c[j].atime.target_time) && (b[i].atime.service_time>c[j].atime.service_time) ) )
			a[k++]=c[j++];
		else
			a[k++]=b[i++];
	}
	while(i<h1) 
		a[k++]=b[i++];
	while(j<h2) 
		a[k++]=c[j++];

}

void mergeS_sort(REQSD a[],int lower,int upper)
{
	if(lower!=upper)
	{
		int middle=(lower+upper)/2;
		mergeS_sort(a,lower,middle);
		mergeS_sort(a,middle+1,upper);
		mergeS(a,lower,middle,upper);
	}
}



void schedule1(REQWD activities[], int n)
{
	REQWD counters[100][100];
	int index[100];
	int numofcounters=0,i,j,flag;
	mergeW_sort(activities,0,n-1);
	numofcounters=1;
	index[0]=0;
	counters[0][0]=activities[0];
	for(i=1;i<n;i++)
	{
		flag=0;
		for(j=0;j<numofcounters;j++)
		{
			if(activities[i].atime.start_time >= (counters[j][index[j]].atime.start_time+counters[j][index[j]].atime.service_time) )
			{
				counters[j][++index[j]]=activities[i];
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			index[numofcounters]=0;
			counters[numofcounters][0]=activities[i];
			numofcounters++;
		}
	}
	printf("\nSchedule:");
	for(i=0;i<numofcounters;i++)
	{
		printf("\nCounter %d:\n",i);
		for(j=0;j<=index[i];j++)
			printf("%d %d %d\n",counters[i][j].requestID,counters[i][j].atime.start_time,counters[i][j].atime.start_time+counters[i][j].atime.service_time);
	}
}

void schedule2(REQSD activities[], int m)
{
	mergeS_sort(activities,0,m-1);
	int start_time=0,i;
	int end_time=0;
	printf("\nSchedule:");
	for(i=0;i<m;i++)
	{
		start_time=end_time;
		end_time=start_time+activities[i].atime.service_time;
		printf("\n%d %d %d",activities[i].requestID,start_time,end_time);
	}
}


int main()
{
	int n,i,m;
	printf("Enter the number of requests over weekday:");
	scanf("%d",&n);
	REQWD *activities=(REQWD *)malloc(n*sizeof(REQWD));
	printf("Enter the start time and length for each of the requests\n");
	for(i=0;i<n;i++)
	{
		printf("Request %d:",i);
		activities[i].requestID=i;
		scanf(" %d",&activities[i].atime.start_time);
		scanf(" %d",&activities[i].atime.service_time);
	}
	schedule1(activities,n);
	printf("\n \n");
	printf("Enter the number of requests over Saturday:");
	scanf("%d",&m);
	REQSD *activities2=(REQSD *)malloc(m*sizeof(REQSD));
	printf("Enter the length and deadline for each of the requests\n");
	for(i=0;i<m;i++)
	{
		printf("Request %d:",i);
		activities2[i].requestID=i;
		scanf(" %d",&activities2[i].atime.service_time);
		scanf(" %d",&activities2[i].atime.target_time);
	}
	schedule2(activities2,m);
	printf("\n");
	
	free(activities);
	free(activities2);
	
	return 0;
}
