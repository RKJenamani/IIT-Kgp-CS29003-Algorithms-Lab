#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100

int parent(int i)
{
	return i/2;
}
int left(int i)
{
	return 2*i;
}
int right(int i)
{
	return 2*i+1;
}
typedef struct _job
{
	int jobId;
	int startTime;
	int jobLength;
	int remLength;
} job;

typedef struct _heap
{
	job list[MAX_SIZE];
	int index_list[MAX_SIZE];
	int numJobs;
} heap;

typedef struct _jobPair
{
	int jobid_from;
	int jobid_to;
} jobPair;


void initHeap(heap *H)
{
	H->numJobs=0;
	for(int i=1;i<MAX_SIZE;i++)
		H->index_list[i]=-1;
}

void insertJob(heap *H,job j)
{
	int x,i;
	job temp;
	int temp_index;
	//printf("H->numJobs:%d",H->numJobs);
	H->list[++(H->numJobs)]=j;
	H->index_list[j.jobId]=H->numJobs;
	i=H->numJobs;
	//printf("i:%d",i);
	while(parent(i)>0)
	{
		if(H->list[parent(i)].remLength > H->list[i].remLength )
		{
			temp=H->list[parent(i)];
			H->list[parent(i)]=H->list[i];
			H->list[i]=temp;
			
			H->index_list[H->list[i].jobId]=i;
			H->index_list[H->list[parent(i)].jobId]=parent(i);
			

			i=parent(i);
		}
		else if( (H->list[parent(i)].remLength == H->list[i].remLength) && (H->list[parent(i)].jobId > H->list[i].jobId) )
		{
			temp=H->list[parent(i)];
			H->list[parent(i)]=H->list[i];
			H->list[i]=temp;
			
			
			H->index_list[H->list[i].jobId]=i;
			H->index_list[H->list[parent(i)].jobId]=parent(i);

			i=parent(i);
		}
		else
			break;
	}

	
}
void min_heapify(heap *H,int i)
{
	int smallest=i;
	if ( (left(i)<=H->numJobs) && ( (H->list[left(i)].remLength < H->list[i].remLength) || ( (H->list[left(i)].remLength==H->list[i].remLength) && (H->list[left(i)].jobId<H->list[i].jobId) ) )  ) 
		smallest=left(i);
	if( (right(i)<=H->numJobs) && ( (H->list[right(i)].remLength < H->list[smallest].remLength) || ( (H->list[right(i)].remLength==H->list[smallest].remLength) && (H->list[right(i)].jobId<H->list[smallest].jobId) ) ) )
		smallest=right(i);
	if(smallest!=i)
	{
		job temp;
		temp=H->list[smallest];
		H->list[smallest]=H->list[i];
		H->list[i]=temp;
		
		H->index_list[H->list[smallest].jobId]=smallest;
		H->index_list[H->list[i].jobId]=i;

		min_heapify(H,smallest);
	}
}
int extractMinJob(heap *H,job *j)
{
	if(H->numJobs==0)
		return -1;
	else
	{
		*j=H->list[1];
		H->list[1]=H->list[(H->numJobs)--];
		H->index_list[H->list[1].jobId]=1;
		min_heapify(H,1);
		return 0;
	}
}

void printHeap(heap *H,int n)
{
	int i;
	printf("\n JobId--startTime--jobLength--remLength--%d",H->numJobs);
	for(i=1;i<=H->numJobs;i++)
	{
		printf("\n %d -- %d -- %d -- %d",H->list[i].jobId,H->list[i].startTime,H->list[i].jobLength,H->list[i].remLength);
	}
	printf("\nindex_list:JobId--index_location");
	for(i=1;i<=n;i++)
	{
		printf("\n%d--%d\n",i,H->index_list[i]);
	}
}

void bubble_sort(job joblist[],int n)
{
	int i,j,flag;
	job temp;
	for(i=0;i<n-1;i++)
	{
		flag=0;
		for(j=0;j<n-i-1;j++)
			if(joblist[j].startTime>joblist[j+1].startTime)
			{
				flag=1;
				temp=joblist[j];
				joblist[j]=joblist[j+1];
				joblist[j+1]=temp;
			}
		if(flag==0)
			break;
	}
}

void bubble_sort2(jobPair pairList[],int n)
{
	int i,j,flag;
	jobPair temp;
	for(i=0;i<n-1;i++)
	{
		flag=0;
		for(j=0;j<n-i-1;j++)
			if(pairList[j].jobid_from>pairList[j+1].jobid_from)
			{
				flag=1;
				temp=pairList[j];
				pairList[j]=pairList[j+1];
				pairList[j+1]=temp;
			}
		if(flag==0)
			break;
	}
}

void decreaseKey(heap *H,int jid)
{
	//printf("K");
	//printf("%d",H->list[H->index_list[jid]].remLength);
	if(H->list[H->index_list[jid]].remLength==H->list[H->index_list[jid]].jobLength)
		H->list[H->index_list[jid]].jobLength=H->list[H->index_list[jid]].jobLength/2;
	H->list[H->index_list[jid]].remLength=(H->list[H->index_list[jid]].remLength)/2;
	//printf("---%d",H->list[H->index_list[jid]].remLength);
}




void newScheduler(job joblist[], int n,jobPair pairList[],int m)
{
	heap H;
	initHeap(&H);
	job current;
	current.remLength=-1;
	int time=0,i;
	int index=0;
	int job_flag=0;
	float turn=0;
	float number=0;
	int pairList_index[MAX_SIZE];
	int j=0;
	for(i=1;i<=n;i++)
	{
		if(i==pairList[j].jobid_from)
		{
			pairList_index[i]=pairList[j].jobid_to;
			j++;
		}
		else
			pairList_index[i]=0;
	}
	//for(i=1;i<=n;i++)
	//{
	//	printf("\n%d--%d",i,pairList_index[i]);
	//}
	
	printf("Jobs scheduled at each timestep are:");
	do
	{
		
		if(joblist[index].startTime==time)
		{
			do
			{
			if(time==0)
				insertJob(&H,joblist[index]);
			else
			{
				if(joblist[index].remLength<current.remLength || (joblist[index].remLength==current.remLength && joblist[index].jobId<current.jobId) )
				{
					insertJob(&H,current);
					current=joblist[index];
					
				}
				else
				{
					insertJob(&H,joblist[index]);
				}
			}
			index++;	
			}while( index<n && joblist[index].startTime==joblist[index-1].startTime);
		}
		if(current.remLength==0)
		{
			//printf(" ->%d",current.jobId-1);
			if(pairList_index[current.jobId]!=0)
			{
				//printf("-%d-",pairList_index[current.jobId]);
				decreaseKey(&H,pairList_index[current.jobId]);
				i=H.index_list[pairList_index[current.jobId]];
				job temp;
				while(parent(i)>0)
				{
					if(H.list[parent(i)].remLength > H.list[i].remLength )
					{
						temp=H.list[parent(i)];
						H.list[parent(i)]=H.list[i];
						H.list[i]=temp;
				
						H.index_list[H.list[i].jobId]=i;
						H.index_list[H.list[parent(i)].jobId]=parent(i);
				
	
						i=parent(i);
					}	
					else if( (H.list[parent(i)].remLength == H.list[i].remLength) && (H.list[parent(i)].jobId > H.list[i].jobId) )
					{
						temp=H.list[parent(i)];
						H.list[parent(i)]=H.list[i];
						H.list[i]=temp;
						
				
						H.index_list[H.list[i].jobId]=i;
						H.index_list[H.list[parent(i)].jobId]=parent(i);
		
						i=parent(i);
					}
					else
						break;
				}
				
			}
			extractMinJob(&H,&current);
			//printf("--%d %d--",current.jobLength,current.remLength);
			
		}
		if(time==0)
		{
			extractMinJob(&H,&current);
		}
		if(current.jobLength==current.remLength)
		{
				
				turn=turn+time-current.startTime;
		}
		current.remLength--;
		time++;	
		printf(" %d ",current.jobId);	
	}while( current.remLength!=0 || H.numJobs!=0);	
	printf("\n Average Turnaround time is: %f",turn/n); 
}

void main()
{
	
	int n,i,m;
	job temp;
	job temp2;
	printf("Enter number of jobs (n): ");
	scanf("%d",&n);

	job *joblist= (job*)malloc((n)*sizeof(job));
	for(i=0;i<n;i++)
	{
		scanf("%d",&(joblist[i].jobId));
		scanf(" %d",&(joblist[i].startTime));
		scanf(" %d",&(joblist[i].jobLength));
		joblist[i].remLength=joblist[i].jobLength;
	}
	bubble_sort(joblist,n);
	printf("Input number of job-dependancies:");
	scanf("%d",&m);
	jobPair *pairList= (jobPair*)malloc((m)*sizeof(jobPair));
	for(i=0;i<m;i++)
	{
		scanf("%d",&pairList[i].jobid_from);
		scanf("%d",&pairList[i].jobid_to);
		
	}
	bubble_sort2(pairList,m);
	newScheduler(joblist,n,pairList,m);

	if(joblist!=NULL)
	{
		free(joblist);
		joblist=NULL;
	}
	if(pairList!=NULL)
	{
		free(pairList);
		pairList=NULL;
	}


	/*
	printf("\nJobid_from,Jobid_to");
	for(i=0;i<m;i++)
		printf("\n%d--%d",pairList[i].jobid_from,pairList[i].jobid_to);
		
	heap H;
	initHeap(&H);
	for(i=0;i<n;i++)
	{
		scanf("%d",&(temp.jobId));
		scanf(" %d",&(temp.startTime));
		scanf(" %d",&(temp.jobLength));
		temp.remLength=temp.jobLength;
		insertJob(&H,temp);
		printf("\n \n");
		printHeap(&H,n);
	}
	printf("\n \n");
	extractMinJob(&H,&temp);
	printf("\n %d -- %d -- %d -- %d",temp.jobId,temp.startTime,temp.jobLength,temp.remLength);
	printf("\n \n");
	printHeap(&H,n);
	printf("\n \n");
	extractMinJob(&H,&temp);
	printf("\n %d -- %d -- %d -- %d",temp.jobId,temp.startTime,temp.jobLength,temp.remLength);
	printf("\n \n");
	printHeap(&H,n);*/
	
}





















