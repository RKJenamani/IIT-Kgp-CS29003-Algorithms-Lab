//NAME: Rajat Kumar Jenamani
//ROLL NO: 17CS10061
//PC NO: 71

/*
	Definition of subproblem used:
I have defined DP[i][j] as the max success probability that a project has with i essential components and j number of people.
For storing the components I have used a 2D array 'comp'. comp[i][j] stores the number of people assigned to the ith essential component such that we can get the max success probability with i essential components and j number of people.

base cases:

	DP[k][0]=0 for 1<=k<=N because its given p[k][0]=0
	DP[1][j]=p[1][j] for 1<=j<=P as if there is only one essential component, all the j people available must be assigned to it (as p(k,j) values are non decreasing for increasing values of j)

	comp[1][j]=j for 1<=j<=P as for only 1 task all people available must be set to that task

Recursive formulation:
	
	for 2<=x<N, x<=y<=P : 
		if(x==y) : DP[x][y]=D[x-1][y-1]*a[x][1] (as all essential components must have one person each)
			   comp[x][y]=1 as xth essential task will be assigned 1 person
		else     : DP[x][z]=max(DP[x-1][y-z]*a[x][z]) where 1<=z<=(y-1) ( 1 as each essential component must have atleast 1 person)
			   comp[x][y]=tempz where tempz=value of z for which maximum is found above (as this means xth essential component must have tempz people)
	
Answer: maximum success probability: DP[N][P]
	components: components printed using 2D array comp.
*/

#include<stdio.h>
#include<stdlib.h>

int main()
{
	int N,P,j,k,x,y,z,i,tempz,res;
	float q,max;
	float a[100][100];
	float DP[100][100];
	int output[100];
	int comp[100][100];
	printf("\nEnter N:");
	scanf(" %d",&N);
	printf("\nEnter P:");
	scanf(" %d",&P);
	printf("\nEnter the probabilities:\n");
	for(k=1;k<=N;k++)
		for(j=1;j<=P;j++)
			scanf(" %f",&a[k][j]);
	//DP array initialized to 0
	for(x=0;x<=N;x++)
		for(y=0;y<=P;y++)
			DP[x][y]=0;
	for(k=1;k<=N;k++)
		DP[k][0]=0;
	for(j=1;j<=P;j++)
		DP[1][j]=a[1][j];
	
	for(x=2;x<=N;x++)
		for(y=1;y<=P;y++)	
		{
			comp[i][j]=0;
		}
	for(j=1;j<=P;j++)
	{
		comp[1][j]=j;
	}
	for(x=2;x<=N;x++)
		for(y=x;y<=P;y++)
		{
			if(x==y)
			{	
				DP[x][y]=DP[x-1][y-1]*a[x][1];
				comp[x][y]=1;
			}
			else
			{
				
				max=0;
				for(z=1;z<=(y-1);z++)
				{
					q=DP[x-1][y-z]*a[x][z];
					if(q>max)
					{
						tempz=z;
						max=q;
					}
				}
				DP[x][y]=max;
				comp[x][y]=tempz;
			}
		}
	printf("\nThe maximum success probability is: %f\n",DP[N][P]);
	printf("Assignment of people for max success probability:\n");
	res=P;
	for(x=N;x>0;x--)
	{
		output[x]=comp[x][res];
		res=res-output[x];
	}
	for(i=1;i<=N;i++)
		printf("Component %d: %d\n",i,output[i]);
	
	return 0;
}
