#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int subpartID;
	int cost_per_day;
	int duration;
} subpart_data;

typedef struct{
	int predecessorID;
	int successorID;
} dependency_info;

void merge(subpart_data a[],int lower,int middle,int upper)
{
	subpart_data b[100],c[100];
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
		if(b[i].cost_per_day*c[j].duration>c[j].cost_per_day*b[i].duration)
			a[k++]=b[i++];
		else
			a[k++]=c[j++];
	}
	while(i<h1) 
		a[k++]=b[i++];
	while(j<h2) 
		a[k++]=c[j++];

}

void merge_sort(subpart_data a[],int lower,int upper)
{
	if(lower!=upper)
	{
		int middle=(lower+upper)/2;
		merge_sort(a,lower,middle);
		merge_sort(a,middle+1,upper);
		merge(a,lower,middle,upper);
	}
}	

void print_schedule(subpart_data *A, int K)
{
	merge_sort(A,0,K-1);//sort in descending based on cost/duration
	int no_of_days=0;	
	int i,cost=0;
	for(i=0;i<K;i++)
	{
		printf("%d ",A[i].subpartID);
		no_of_days=no_of_days+A[i].duration;
		cost=cost+no_of_days*A[i].cost_per_day;
	}
	printf("\nCost:%d",cost);	
}

void print_schedule1(subpart_data *A,int K,dependency_info *B,int l)
{
	int i,j,m,col,flag;
	int number_of_chains;
	int chain[100][100];
	int dependent[100];
	int high[100];
	for(i=0;i<K;i++)
		dependent[i]=0;
	for(i=0;i<l;i++)
		dependent[B[i].successorID-1]=1;
	printf("\n");
	for(i=0;i<K;i++)
		printf("%d ",dependent[i]);
	for(i=0;i<K;i++)
	{
		high[i]=0;
		for(j=0;j<K;j++)
			chain[i][j]=0;
	}
	j=0;
	for(i=0;i<K;i++)
	{
		if(dependent[i]==0)
		{
			chain[j][0]=i+1;
			col=0;
			while(1)
			{
				flag=0;
				for(m=0;m<l;m++)
					if(B[m].predecessorID==chain[j][col])
					{
						chain[j][++col]=B[m].successorID;
						flag=1;
						break;
					}
				if(flag==0)
					break;
			}
			high[j]=col+1;
			j++;
		}
	}
	number_of_chains=j;
	for(i=0;i<K;i++)
	{
		printf("\n %d -  ",high[i]);
		for(j=0;j<K;j++)
			printf("%d ",chain[i][j]);
	}
	printf("\n");
	
	//merge number_of_chains chains

	float max_value=0;
	int max_index;
	int r,c;
	
	int output[100];
	int output_index=0;
	
	int low[100];
	int duration_sum,cost_sum;

	int active_chain[100];
	for(i=0;i<number_of_chains;i++)
		active_chain[i]=1;
	for(i=0;i<number_of_chains;i++)
		low[i]=0;
	for(i=0;i<number_of_chains;i++)
		high[i]--;
	while(1)
	{
		max_value=0;
		for(i=0;i<number_of_chains;i++)
		{
			if(active_chain[i]==1)
			{
				duration_sum=0;
				cost_sum=0;
				for(j=low[i];j<=high[i];j++)
				{
					duration_sum=duration_sum+A[chain[i][j]-1].duration;
					cost_sum=cost_sum+A[chain[i][j]-1].cost_per_day;
					if(max_value< ((float)cost_sum)/((float)duration_sum) )
					{
						max_value=((float)cost_sum)/((float)duration_sum);
						r=i;
						c=j;
					}
				}
			}
		}
		for(m=low[r];m<=c;m++)
			output[output_index++]=chain[r][m];
		low[r]=c+1;
		printf(" %d",output_index);
		if(output_index==K)
			break;
	}
	printf("\n Scheduled Index: ");
	for(i=0;i<K;i++)
		printf("%d ",output[i]);

	int cost=0;
	int no_of_days=0;
	for(i=0;i<K;i++)
	{
		no_of_days=no_of_days+A[output[i]-1].duration;
		cost=cost+no_of_days*A[output[i]-1].cost_per_day;
	}
	
	printf("\nCost:%d",cost);
}

int main()
{
	subpart_data* A;
	dependency_info* B;
	int K,i,l;
	printf("Input number of subparts (K) :");
	scanf("%d",&K);
	A = (subpart_data*)malloc((K)*sizeof(subpart_data));
	for(i=0;i<K;i++)	
	{
		A[i].subpartID=i+1;
		scanf("%d",&A[i].duration);
	}
	for(i=0;i<K;i++)
		scanf("%d",&A[i].cost_per_day);
	print_schedule(A,K);
	
	printf("\nInput number of dependencies (l) :");
	scanf("%d",&l);
	
	B = (dependency_info*)malloc((l)*sizeof(dependency_info));
	for(i=0;i<l;i++)
	{
		scanf("%d",&B[i].predecessorID);
		scanf("%d",&B[i].successorID);
	}
	print_schedule1(A,K,B,l);
	
	
	return 0;	
}





























