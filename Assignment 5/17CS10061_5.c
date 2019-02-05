#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct _wordR 
{ 
	char word[100]; 
	double x, y; 
} wordR; 

typedef struct _node
{ 
	wordR w; 
	struct _node *next; 
}node, *nodePointer; 

typedef nodePointer **hashTable; 

void insertH(hashTable H, int m, wordR a)
{
	int X=floor(m*(a.x));
	int Y=floor(m*(a.y));
	nodePointer temp=NULL;
	if(H[X][Y]==NULL)
	{
		H[X][Y]=(nodePointer)malloc(sizeof(node));
		H[X][Y]->w=a;
		H[X][Y]->next=NULL;
	}
	else
	{
		temp=H[X][Y];
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=(nodePointer)malloc(sizeof(node));
		temp->next->w=a;
		temp->next->next=NULL;
	}
}

void printH(hashTable H, int m,FILE* fp)
{
	int i,j;
	nodePointer temp=NULL;
	printf("%d",m);
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			fprintf(fp,"\n[%d,%d]::(",i,j);
			temp=H[i][j];
			while(temp!=NULL)
			{
				fprintf(fp," %s ",temp->w.word);
				temp=temp->next;
			}
			
		}
	}
}

void findNN (hashTable H, int m, wordR a)
{
	int X=floor(m*(a.x));
	int Y=floor(m*(a.y));
	wordR output;
	nodePointer temp=NULL;
	int flag=0;
	double min=1000;
	double dis=0;
	int s,t,i,j;
	i=X;
	j=Y;
	printf("--%d--%d--",i,j);
	if(H[X][Y]!=NULL)
	{
		temp=H[X][Y];
		while(temp!=NULL)
		{
			if(strcmp( (temp->w.word),a.word ) !=0)
			{
				dis=sqrt( ((temp->w.x)-a.x)*((temp->w.x)-a.x) + ((temp->w.x)-a.x)*((temp->w.x)-a.x) );
				if(dis<min)
				{
					min=dis;
					output=temp->w;
				}
				flag=1; 
			}
			temp=temp->next;
		}
		if(flag==1)
		{
			printf("%s%lf%lf",output.word,output.x,output.y);
		}
	}
	if(flag==0)
	{
		int k=1;
		while(1)
		{
			for(s=i-k,t=j-k;t<=j+k;t++)
			{
				temp=H[s][t];
				while(temp!=NULL)
				{
					dis=sqrt( ((temp->w.x)-a.x)*((temp->w.x)-a.x) + ((temp->w.x)-a.x)*((temp->w.x)-a.x) );
					if(dis<min)
					{
						min=dis;
						output=temp->w;
					}
					flag=1; 
					temp=temp->next;
				}
			}
			for(s=i+k,t=j-k;t<=j+k;t++)
			{
				temp=H[s][t];
				while(temp!=NULL)
				{
					dis=sqrt( ((temp->w.x)-a.x)*((temp->w.x)-a.x) + ((temp->w.x)-a.x)*((temp->w.x)-a.x) );
					if(dis<min)
					{
						min=dis;
						output=temp->w;
					}
					flag=1; 
					temp=temp->next;
				}
			}
			for(t=j-k,s=i-k+1;s<i+k;s++)
			{
				temp=H[s][t];
				while(temp!=NULL)
				{
					dis=sqrt( ((temp->w.x)-a.x)*((temp->w.x)-a.x) + ((temp->w.x)-a.x)*((temp->w.x)-a.x) );
					if(dis<min)
					{
						min=dis;
						output=temp->w;
					}
					flag=1; 
					temp=temp->next;
				}
			}
			for(t=j+k,s=i-k+1;s<i+k;s++)
			{
				temp=H[s][t];
				while(temp!=NULL)
				{
					dis=sqrt( ((temp->w.x)-a.x)*((temp->w.x)-a.x) + ((temp->w.x)-a.x)*((temp->w.x)-a.x) );
					if(dis<min)
					{
						min=dis;
						output=temp->w;
					}
					flag=1; 
					temp=temp->next;
				}
			}
			if(flag==1)
			{
				printf("%s%lf%lf",output.word,output.x,output.y);
				break;	
			}	
		}
	}
	



}


int main()
{
	FILE *inpf, *outf; 
	int n, i,j, m,k;    
	wordR w,a;
	hashTable H;

	inpf = fopen("input.txt","r");
	if (inpf==NULL)
	{
		printf("Error opening input file input.txt\n");
		return (-1);
	}	
	
	outf = fopen("output.txt","w");
	if (outf==NULL)
	{
		printf("Error creating output file output.txt\n");
		return (-1);
	}

	fscanf(inpf,"%d",&n);
	m=ceil(sqrt(n));

	printf("%d--%d",n,m);
	//creating dynamic array
	H= (nodePointer **)malloc(m*sizeof(nodePointer*));
	for(i=0;i<m;i++)
	{
		H[i]=(nodePointer*)malloc(m*sizeof(nodePointer));
		for(j=0;j<m;j++)
			H[i][j]=NULL;
	}

	
	
	for(i=0;i<n;i++)
	{
		fscanf(inpf,"%s%lf%lf",w.word,&w.x,&w.y);
		insertH(H,m,w);
			
	}
	printH(H,m,outf);
	
	printf("Input number of words to search for:");	
	scanf("%d",&k);
	
	for(i=0;i<k;i++)
	{
		printf("Input Word");
		scanf("%s%lf%lf",a.word,&a.x,&a.y);
		findNN(H,m,a);
	}
	fclose(inpf); 
	fclose(outf); 



}

