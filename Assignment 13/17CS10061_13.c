#include<stdio.h>
#include<stdlib.h>

typedef int **graph;

typedef struct _node
{
	int data;
	struct _node* next;
}node,*list;

typedef struct q
{
	node *front, *rear ;
} QUEUE ;


typedef struct _edge
{
	int a,b,weight;
}edge;

void merge(edge a[],int lower,int middle,int upper)
{
	edge b[1000],c[1000];
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
		if(b[i].weight<c[j].weight)
			a[k++]=c[j++];
		else
			a[k++]=b[i++];
	}
	while(i<h1) 
		a[k++]=b[i++];
	while(j<h2) 
		a[k++]=c[j++];

}

void merge_sort(edge a[],int lower,int upper)
{
	if(lower!=upper)
	{
		int middle=(lower+upper)/2;
		merge_sort(a,lower,middle);
		merge_sort(a,middle+1,upper);
		merge(a,lower,middle,upper);
	}
}

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
void enqueue(QUEUE *qP, int data)
{
	list temp;
	temp=(list)malloc(sizeof(node));
	temp->data=data;
	temp->next=NULL;
	if(qP->front==NULL)
		qP->front=qP->rear=temp;
	else
	{
		(qP->rear)->next=temp;
		qP->rear=temp;
	}
}
int dequeue(QUEUE *qP)
{
	if (qP->front == NULL)
		printf("Queue Empty ");
	else
	{
		list temp;
		int val;
		temp = qP->front;
		val=(qP->front)->data;
		qP->front = (qP->front)->next;
		temp->next = NULL;
		if (qP->front == NULL)
			qP->rear = NULL;
		return val;
	}
}

int isConnectedUsingBFS(graph G,int numberOfNodes)
{
	int i,visited[1000];
	int distance[1000],parent[1000];
	int current;
	int v=0;
	for(i=0;i<numberOfNodes;i++)
	{
		parent[i]=-1;
		visited[i]=0;
		distance[i]=0;
	}
	
	QUEUE *qP=NULL;
	init(&qP);
	enqueue(qP,v);
	visited[v]=1;
	distance[v]=0;
	parent[v]=-1;
	//printf("\nBFS Traversal:");
	while(!isempty(qP))
	{
		current=dequeue(qP);
		//printf(" %d",current);
		for(i=0;i<numberOfNodes;i++)
		{
			if(G[current][i]!=0)
			{
				if(visited[i]==0)
				{
					visited[i]=1;
					parent[i]=current;
					distance[i]=distance[current]+1;
					enqueue(qP,i);
				}	
			}
		}
	}
	for(i=0;i<numberOfNodes;i++)
		if(visited[i]==0)
			return 0;
	return 1;
}
void findMST(graph G, int numberOfNodes)
{
	int i,j;
	edge edgeset[1000];
	int size=0;
	for(i=0;i<numberOfNodes;i++)
		for(j=0;j<i;j++)
		{
			if(G[i][j]!=0)
			{
				edgeset[size].a=i;
				edgeset[size].b=j;
				edgeset[size].weight=G[i][j];
				size++;
			}
		}
	/*printf("Unsorted:");
	for(i=0;i<size;i++)
		printf("\n %d---%d==%d",edgeset[i].a,edgeset[i].b,edgeset[i].weight);*/
	merge_sort(edgeset,0,size-1);
	/*printf("\nSorted:");
	for(i=0;i<size;i++)
		printf("\n %d---%d==%d",edgeset[i].a,edgeset[i].b,edgeset[i].weight);*/
	for(i=0;i<size;i++)
	{
		G[edgeset[i].a][edgeset[i].b]=0;
		G[edgeset[i].b][edgeset[i].a]=0;
		if(isConnectedUsingBFS(G,numberOfNodes)==0)
		{
			G[edgeset[i].a][edgeset[i].b]=edgeset[i].weight;
			G[edgeset[i].b][edgeset[i].a]=edgeset[i].weight;
		}	
	}
	//printf("MST:");
	/*for(i=0;i<size;i++)
		if(ans[i]==1)
			printf("\n %d---%d==%d",edgeset[i].a,edgeset[i].b,edgeset[i].weight);*/
	printf("\nThe neighbors of each node in the MST I computed and corresponding weights:");
	for(i=0;i<numberOfNodes;i++)
	{
		printf("\nvertex %d: ",i);
		for(j=0;j<numberOfNodes;j++)
		{
			if(G[i][j]!=0)
				printf("%d %d ",j,G[i][j]);
		}
	}
}
int main()
{
	graph G;
	int n,m,i,j,k,d,w;
	printf("Input the number of nodes and edges: ");
	scanf(" %d",&n);
	scanf(" %d",&m);
	//int G[100][100];
	G=(int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
		G[i]=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		for(k=0;k<n;k++)
			G[i][k]=0;
	printf("Enter the neighbours of each node and corresponding weights:\n");
	for(i=0;i<n;i++)
	{
		printf("Degree of vertex %d: ",i);
		scanf(" %d",&d);
		printf("Neighbours of %d: ",i);
		for(k=0;k<d;k++)
		{
			scanf(" %d",&j);
			scanf(" %d",&w);
			G[i][j]=w;
		}
	}
	printf("\nThe neighbors of each node in the input graph and corresponding weights:");
	for(i=0;i<n;i++)
	{
		printf("\nvertex %d: ",i);
		for(j=0;j<n;j++)
		{
			if(G[i][j]!=0)
				printf("%d %d ",j,G[i][j]);
		}
	}
	findMST(G,n);
	for(i=0;i<n;i++)
		free(G[i]);
	free(G);
	return 0;
}
