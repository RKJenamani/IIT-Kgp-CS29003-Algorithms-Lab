#include<stdio.h>
#include<stdlib.h>

typedef struct _node
{
	int vno;
	struct _node *next;
} node;

typedef struct _vertex
{
	node *adjlist;
	int visited;
	int discovery;
	int low;
	int parent;
	int isap; // stores articulation points
} vertex;

typedef vertex *graph;

int DFSVisit(graph G,int n,int rem,int s)
{
	//printf("%d ",s);
	G[s].visited=1;
	node* temp=G[s].adjlist;
	while(temp)
	{
		if(temp->vno!=rem)
		{
			if(G[temp->vno].visited==0)
				DFSVisit(G,n,rem,temp->vno);
		}
		temp=temp->next;	
	}
}

int DFSComp(graph G, int n, int rem)
{
	int i,count=0;
	for(i=0;i<n;i++)
		G[i].visited=0;
	for(i=0;i<n;i++)
	{
		if(i!=rem)
		{
			if(G[i].visited==0)
			{
				DFSVisit(G,n,rem,i);
				count++;
			}
		}
	}
	return count;
}

void findCritical(graph G, int n)
{
	printf("\nCritical junctions using the simple algorithm:"); 
	int i,count=0;
	for(i=0;i<n;i++)
	{
		count=DFSComp(G,n,i);
		if(count>1)
		{
			printf("\nVertex %d: %d components",i,count);
		}
	}
}


int DFSVisitFast(graph G,int n,int s,int* time)
{
	//printf("%d ",s);
	G[s].visited=1;
	(*time)=(*time)+1;
	G[s].discovery=(*time);
	G[s].low=(*time);
	node* temp=G[s].adjlist;
	int child=0;
	while(temp)
	{
		if(G[temp->vno].visited==0)
		{
			child++;
			G[temp->vno].parent=s;
			DFSVisitFast(G,n,temp->vno,time);
			if(G[s].low>G[temp->vno].low)
				G[s].low=G[temp->vno].low;
			if(G[s].parent!=-2 && G[s].discovery<=G[temp->vno].low)//non-root node
				G[s].isap=1;
		}
		else if(G[temp->vno].visited==1 && G[temp->vno].parent!=-1)// 1 backnode possible
		{
			if(G[s].low>G[temp->vno].discovery)
				G[s].low=G[temp->vno].discovery;
		}
		temp=temp->next;	
	}
	if(child>1 && G[s].parent==-2)//root node
		G[s].isap=1;
	(*time)=(*time)+1;
}

int DFSCompFast(graph G, int n)
{
	int i;
	int time=0;
	for(i=0;i<n;i++)
	{
		G[i].visited=0;
		G[i].discovery=0;
		G[i].low=0;
		G[i].parent=-1;
		G[i].isap=0;
	}
	for(i=0;i<n;i++)
		G[i].visited=0;
	for(i=0;i<n;i++)
	{
		if(G[i].visited==0)
		{
			G[i].parent=-2;
			DFSVisitFast(G,n,i,&time);
		}
	}
	//for(i=0;i<n;i++)
	//	printf("\n %d: parent:%d dis:%d low:%d",i,G[i].parent,G[i].discovery,G[i].low);
}


void findCriticalFast(graph G,int n)
{
	int i;
	printf("\nCritical Junction using the fast algorithm:");
	DFSCompFast(G,n);
	for(i=0;i<n;i++)
		if(G[i].isap==1)
			printf("\nVertex %d is a critical junction",i);
		
}



int main()
{
	int n,e,degree,i,k,l;
	graph G;
	node *temp;
	printf("Enter the number of vertices and edges: ");
	scanf(" %d",&n);
	scanf(" %d",&e);
	G=(graph)malloc(n*sizeof(vertex));
	for(i=0;i<n;i++)
	{
		G[i].adjlist=NULL;
		G[i].visited=0;
		G[i].discovery=0;
		G[i].low=0;
		G[i].parent=0;
		G[i].isap=0;
	}
	printf("Enter the neighbors for each of the vertex:\n");
	for(i=0;i<n;i++)
	{
		printf("Degree of vertex %d: ",i);
		scanf(" %d",&degree);
		printf("Neighbors of %d: ",i);
		while(degree--)
		{
			scanf(" %d",&k);
			if(G[i].adjlist==NULL)
			{
				G[i].adjlist=(node*)malloc(sizeof(node));
				G[i].adjlist->vno=k;
				G[i].adjlist->next=NULL;
			}
			else
			{
				temp=(node*)malloc(sizeof(node));
				temp->vno=k;
				temp->next=G[i].adjlist;
				G[i].adjlist=temp;
			}
		}
	}
	printf("\nAdjacency list of the graph:");
	for(i=0;i<n;i++)
	{
		printf("\nVertex %d: ",i);
		temp=G[i].adjlist;
		while(temp)
		{
			printf("%d ",temp->vno);
			temp=temp->next;
		}
	}
	printf("\n");
	findCritical(G,n);
	findCriticalFast(G,n);
	
	free(G);
	return 0;
}
	



































