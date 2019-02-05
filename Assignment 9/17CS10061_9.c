#include<stdio.h>
#include<stdlib.h>
int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
	
}
int min(int a, int b)
{
	if(a<b)
		return a;
	else
		return b;
}
int findMinimumDays(int N,int T) //N is number of trucks and T is capacity
{
	int r=N+1;
	int c=T+1;
	int i,j,x,minimum;
	//int DP[1000][1000];
	int **DP=(int **)malloc(r*sizeof(int*));
	for(i=0;i<r;i++)
		DP[i]=(int *)malloc(c*sizeof(int));
	for(i=1;i<=N;i++)
	{
		DP[i][0]=0;
		DP[i][1]=1;
	}
	for(i=1;i<=T;i++)
	{
		DP[1][i]=i;
	}
	for(i=2;i<=N;i++)
	{
		for(j=2;j<=T;j++)
		{
			minimum=10000;
			for(x=1;x<=j;x++)
			{
				if(minimum>max(DP[i-1][x-1],DP[i][j-x]))
					minimum=max(DP[i-1][x-1],DP[i][j-x]);
			}
			DP[i][j]=minimum+1;
		}
	}
	//for(i=1;i<=N;i++)
	//{	
	//	printf("\n");
	//	for(j=1;j<=T;j++)
	//		printf(" %d",DP[i][j]);
	//}
	int value=DP[N][T];
	for(i=0;i<r;i++)
		free(DP[i]);
	free(DP);

	return value;
}
int findMinimumDaysFaster(int N,int T) //N is number of trucks and T is capacity
{
	int r=N+1;
	int c=T+1;
	int i,j,x,minimum,first,last,middle,temp,temp2;
	//int DP[1000][1000];
	int **DP=(int **)malloc(r*sizeof(int*));
	for(i=0;i<r;i++)
		DP[i]=(int *)malloc(c*sizeof(int));
	for(i=1;i<=N;i++)
	{
		DP[i][0]=0;
		DP[i][1]=1;
	}
	for(i=1;i<=T;i++)
	{
		DP[1][i]=i;
	}
	for(i=2;i<=N;i++)
	{
		for(j=2;j<=T;j++)
		{
			first=1;
			last=j;
			minimum=0;
			while(1)
			{
				//printf("k");
				middle=(first+last)/2; 
				if( ( max(DP[i-1][middle-1],DP[i][j-middle])<max(DP[i-1][middle-1+1],DP[i][j-middle-1]) ) && ( max(DP[i-1][middle-1],DP[i][j-middle])<max(DP[i-1][middle-1-1],DP[i][j-middle+1]) ) || first<=last )
				{
					minimum=max(DP[i-1][middle-1],DP[i][j-middle]);
					break;
				}
				else if( ( max(DP[i-1][middle-1],DP[i][j-middle])<max(DP[i-1][middle-1+1],DP[i][j-middle-1]) ) && ( max(DP[i-1][middle-1],DP[i][j-middle])>max(DP[i-1][middle-1-1],DP[i][j-middle+1]) ) ) //left<middle<right
					last=middle-1;
				else if( ( max(DP[i-1][middle-1],DP[i][j-middle])>max(DP[i-1][middle-1+1],DP[i][j-middle-1]) ) && ( max(DP[i-1][middle-1],DP[i][j-middle])<max(DP[i-1][middle-1-1],DP[i][j-middle+1]) ) ) //right<middle<left
					first=middle+1;
				else
				{
					temp=middle-1;
					if(( max(DP[i-1][temp-1],DP[i][j-temp])==max(DP[i-1][middle-1],DP[i][j-middle]) ))
					{
					while( ( max(DP[i-1][temp-1],DP[i][j-temp])==max(DP[i-1][temp-1-1],DP[i][j-temp+1]) ) ) // if middle=left go left
						temp--;
					}
					temp2=middle+1;
					if(( max(DP[i-1][temp2-1],DP[i][j-temp2])==max(DP[i-1][middle-1],DP[i][j-middle]) ))
					{
					while( ( max(DP[i-1][temp2-1],DP[i][j-temp2])==max(DP[i-1][temp2-1+1],DP[i][j-temp2-1]) ) ) // if middle=right go right
						temp2++;
					}
					if( ( max(DP[i-1][temp-1],DP[i][j-temp])>max(DP[i-1][middle-1],DP[i][j-middle]) ) && ( max(DP[i-1][temp2-1],DP[i][j-temp2])>max(DP[i-1][middle-1],DP[i][j-middle]) ) )
					{
						minimum=max(DP[i-1][middle-1],DP[i][j-middle]);
						break;
					}
					else if( ( max(DP[i-1][temp-1],DP[i][j-temp])>max(DP[i-1][middle-1],DP[i][j-middle]) ) && ( max(DP[i-1][temp2-1],DP[i][j-temp2])<max(DP[i-1][middle-1],DP[i][j-middle]) ) )//left>middle>right
						first=temp2;
					else
						last=temp;
				}
			
			}
			DP[i][j]=minimum;
		}
	}
	int value=DP[N][T];
	for(i=0;i<r;i++)
		free(DP[i]);
	free(DP);

	return value;
}	

int main()
{
	int N,T,L,M;
	printf("Input number of trucks: ");
	scanf(" %d",&N);
	printf("Input capacity: ");
	scanf(" %d",&T);
	printf("Minimum number of days required are: %d",findMinimumDays(N,T));
	printf("\nInput number of trucks: ");
	scanf(" %d",&L);
	printf("Input capacity: ");
	scanf(" %d",&M);
	printf("\nMinimum number of days required are: %d",findMinimumDaysFaster(L,M));
	return 0;
}
