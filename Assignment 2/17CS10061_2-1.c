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
			temp=(list)malloc(sizeof(node));
			temp->data.hInd=i;
			temp->data.vInd=j;
			temp->next=maze[i][j];
			maze[i][j]=temp;
			

			//Printing maze linked lists
			printf("(%d,%d)::",temp->data.hInd,temp->data.vInd);	
			temp=temp->next;
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
	struct node *head ;
} STACK ;

void init(STACK **s)//initializes the head pointer
{
	(*s) = (STACK *)malloc(sizeof(STACK));
	(*s)->head=NULL;
}
int isempty(STACK *s)//prints 1 if the stack is empty, 0 otherwise
{
	int k;
	if( s->head==NULL)
	{
		k=1;
		printf("1");
	}
	else
	{
		k=0;
		printf("0");
	}
	return k;
}
void push(STACK *s, room data)
{
	list temp;
	temp=(list)malloc(sizeof(node));
	temp->data.hInd=data.hInd;
	temp->data.vInd=data.vInd;
	temp->next=s->head;
	s->head=temp;
}
	
void pop(STACK *s)
{
	list temp;
	temp=s->head;
	s->head=temp->next;
	temp->next=NULL;
}			
				
			
int strategy1(list maze[][20], int n, room start, room end)
{
	int i,j;
	STACK *st=NULL;
	init(&st);
	
	push(st,start);
	int visited[20][20];
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
			visited[i][j]=0;
	


	
	push(st,end);
	//int m=isempty(st);
	pop(st);
	pop(st);
	//int l=isempty(st);
	printf("STACK IMPLEMETED \n");
	

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
	int f=strategy1(maze,n,start,end);


	
}
	


	
