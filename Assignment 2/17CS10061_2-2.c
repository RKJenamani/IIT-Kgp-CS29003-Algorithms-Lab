#include<stdio.h>
#include<stdlib.h>

void printmaze(int H[][20], int V[][21], int n)
{
	int i,j;
	for(i=0;i<=2*n;i++)
	{
		if(i%2==0)
		{
			printf("+");
			for(j=0;j<n;j++)
			{
				if(H[i/2][j]==0)
					printf("---");
				else
					printf("   ");
				printf("+");
			}
			printf("\n");
		}
		else
		{
			for(j=0;j<=n;j++)
			{
				if(V[i/2][j]==0)
					printf("|   ");
				else
					printf("    ");
			}
			printf("\n");
		}
	}
}
					


typedef struct rm 
{
	int hInd;
	int vInd;
} room;

struct node 
{
	room data;
	struct node *next;
};

typedef struct node node, *list;
list maze[20][20];

void createmaze(list maze[][20], int n, int H[][20], int V[][21])
{
	list temp;
	int i,j;
	printf("The linked list representation looks like \n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			maze[i][j]=NULL;
			if( H[i][j] == 1)
			{
				temp=(list)malloc(sizeof(node));
				temp->data.hInd=i-1;
				temp->data.vInd=j;
				temp->next=maze[i][j];
				maze[i][j]=temp;
			}
			if( H[i+1][j] == 1)
			{
				temp=(list)malloc(sizeof(node));
				temp->data.hInd=i+1;
				temp->data.vInd=j;
				temp->next=maze[i][j];
				maze[i][j]=temp;
			}
			if( V[i][j] == 1)
			{
				temp=(list)malloc(sizeof(node));
				temp->data.hInd=i;
				temp->data.vInd=j-1;
				temp->next=maze[i][j];
				maze[i][j]=temp;
			}
			if( V[i][j+1] == 1)
			{
				temp=(list)malloc(sizeof(node));
				temp->data.hInd=i;
				temp->data.vInd=j+1;
				temp->next=maze[i][j];
				maze[i][j]=temp;
			}
			
			//Printing maze linked lists
			printf("(%d,%d)::",i,j);
			temp=maze[i][j];
			while(temp)	
        		{
                		printf("-->(%d,%d)",temp->data.hInd,temp->data.vInd);	
                		temp=temp->next;
        		}
			printf("\n");
		}
}
typedef struct 
{
	struct node *front, *rear ;
} QUEUE ;

void init(QUEUE **qP)//initializes the front and rear pointers
{
	(*qP) = (QUEUE *)malloc(sizeof(QUEUE));
	(*qP)->front=NULL;
	(*qP)->rear=NULL;
}
int isempty(QUEUE *qP)//prints 1 if the queue is emptry, else 0
{
	int k;
	if( qP->front==NULL && qP->rear==NULL)
		k=1;
	else
		k=0;
	return k;

}
void enqueue(QUEUE *qP, room data)
{
	list temp;
	temp=(list)malloc(sizeof(node));
	temp->data.hInd=data.hInd;
	temp->data.vInd=data.vInd;
	temp->next=NULL;
	if(qP->front==NULL)
		qP->front=qP->rear=temp;
	else
	{
		(qP->rear)->next=temp;
		qP->rear=temp;
	}
}
room dequeue(QUEUE *qP)
{
	if (qP->front == NULL)
		printf("Queue Empty ");
	else
	{
		list temp;
		room val;
		temp = qP->front;
		val=(qP->front)->data;
		qP->front = (qP->front)->next;
		temp->next = NULL;
		if (qP->front == NULL)
			qP->rear = NULL;
		return val;
	}
}	

int strategy2(list maze[][20], int n, room start, room end)
{
	printf("\nUsing Strategy 1 ...\n");
	int i,j;
	room val;
	list temp;

	int visited[20][20];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			visited[i][j]=0;

	QUEUE *qP=NULL;
	init(&qP);
	enqueue(qP,start);
	visited[start.hInd][start.vInd]=1;
	while((!isempty(qP)))
	{
		val=dequeue(qP);
		if( val.hInd==end.hInd && val.vInd==end.vInd)
		{
			return 1;
		}
		for(temp=maze[val.hInd][val.vInd];temp!=NULL;temp=temp->next)
		{
			if (visited[(temp->data).hInd][(temp->data).vInd]==0)
			{
				visited[(temp->data).hInd][(temp->data).vInd]=1;
				enqueue(qP,temp->data);
			}
		}
	}		
	return 0;
}
	


int main()
{
	int i,j, n,s,t,u,v,H[21][20], V[20][21];
	scanf("%d",&n);
	room start,end;
	
	for(i=0;i<=n;i++)	//H is 5*4
		for(j=0;j<n;j++)
			scanf("%d",&H[i][j]);
	for(i=0;i<n;i++)	//V is 4*5
		for(j=0;j<=n;j++)
			scanf("%d",&V[i][j]);
	scanf("%d %d",&s,&t);
	scanf("%d %d",&u,&v);

	start.hInd=s;
	start.vInd=t;
	end.hInd=u;
	end.vInd=v;


	printf("Enter the value of n \n%d \n",n);
	printf("Enter the horizontal doors H \n");
	for(i=0;i<=n;i++)	//H is 5*4
	{
		for(j=0;j<n;j++)
			printf("%d ",H[i][j]);
		printf("\n");
	}
	printf("Enter the vertical doors V \n");
	for(i=0;i<n;i++)	//V is 4*5
	{
		for(j=0;j<=n;j++)
			printf("%d ",V[i][j]);
		printf("\n");
	}
	printf("Enter the indices of the start room s,t");
	printf(" \n%d %d \n",s,t);
	printf("Enter the indices of the end room u,v");
	printf(" \n%d %d \n",u,v);

	printmaze(H,V,n);
	createmaze(maze, n,H,V);

	int g=strategy2(maze,n,start,end);

	if (g==1)
		printf("A path is found using strategy 1 from (%d,%d) to (%d,%d)",start.hInd,start.vInd,end.hInd,end.vInd);
	else
		printf("Path not found");

}
	


	
