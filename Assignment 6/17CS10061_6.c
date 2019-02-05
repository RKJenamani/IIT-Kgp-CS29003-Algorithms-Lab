#include<stdio.h>
#include<stdlib.h>

void combine(int A[],int left,int middle, int right)
{
	int length1,length2,i,j,k;
	int *temp1;
	int *temp2;
	
	temp1 = (int*)malloc((middle-left+1)*sizeof(int));
	temp2 = (int*)malloc((right-middle)*sizeof(int));

	length1=0;
	length2=0;

	for(i=left;i<=middle;i++)
		temp1[length1++]=A[i];
	for(i=middle+1;i<=right;i++)
		temp2[length2++]=A[i];
	
	i=0;
	j=0;
	k=left;
	while(i<length1 && j<length2)
	{
		if(temp1[i]>temp2[j])
			A[k++]=temp2[j++];
		else
			A[k++]=temp1[i++];
	}
	while(i<length1) 
		A[k++]=temp1[i++];
	while(j<length2) 
		A[k++]=temp2[j++];
	if(temp1!=NULL)
	{
		free(temp1);
		temp1=NULL;
	}
	if(temp2!=NULL)
	{
		free(temp2);
		temp2=NULL;
	}	
}

void superbSorting(int A[],int sizeOfA)
{
	int temp=sizeOfA,k=1,l=2,left,right,middle,i,z;
	while(temp!=1)
	{
		for(i=0;i<sizeOfA;i=i+l)
		{
			left=i;
			middle=k-1+i;
			right=l-1+i;
			//printf("\n--%d--%d--%d--",left,middle,right);
			if(right<sizeOfA)
				combine(A,left,middle,right);
			else if(middle<sizeOfA)
				combine(A,left,middle,sizeOfA-1);
				
		}
		//printf("\n");
		//for(z=0;z<sizeOfA;z++)
			//printf(" %d",A[z]);
		temp=temp/2;
		if(temp==1 && right>=sizeOfA)
		{
			//printf("\n--%d--%d--%d--",0,left-1,sizeOfA-1);
			combine(A,0,left-1,sizeOfA-1);	
		}
		k=k*2;
		l=l*2;
	}
}

int compare1(int X[],int sizeOfX,int x, int y)
{
	int i=-1,j=-1,k;
	for(k=0;k<sizeOfX;k++)
	{
		if(X[k]==x)
			i=k;
		if(X[k]==y)
			j=k;
		if((i!=-1) && (j!= -1) )
			break;
	}
	if(i<j)
		return 1;
	else
		return -1;

}

void combine1(int A[],int left,int middle, int right,int B[],int sizeOfB)
{
	int length1,length2,i,j,k;
	int *temp1;
	int *temp2;
	
	temp1 = (int*)malloc((middle-left+1)*sizeof(int));
	temp2 = (int*)malloc((right-middle)*sizeof(int));

	length1=0;
	length2=0;

	for(i=left;i<=middle;i++)
		temp1[length1++]=A[i];
	for(i=middle+1;i<=right;i++)
		temp2[length2++]=A[i];
	
	i=0;
	j=0;
	k=left;
	while(i<length1 && j<length2)
	{
		//printf("\n%d--%d--%d",compare1(B,sizeOfB,temp1[i],temp2[j]),temp1[i],temp2[j]);
		if(compare1(B,sizeOfB,temp1[i],temp2[j])==1)
			A[k++]=temp1[i++];
		else
			A[k++]=temp2[j++];
	}
	while(i<length1) 
		A[k++]=temp1[i++];
	while(j<length2) 
		A[k++]=temp2[j++];
	if(temp1!=NULL)
	{
		free(temp1);
		temp1=NULL;
	}
	if(temp2!=NULL)
	{
		free(temp2);
		temp2=NULL;
	}	
}
void superbSorting1(int A[],int sizeOfA,int B[],int sizeOfB)
{
	int temp=sizeOfA,k=1,l=2,left,right,middle,i,z;
	while(temp!=1)
	{
		for(i=0;i<sizeOfA;i=i+l)
		{
			left=i;
			middle=k-1+i;
			right=l-1+i;
			//printf("\n--%d--%d--%d--",left,middle,right);
			if(right<sizeOfA)
				combine1(A,left,middle,right,B,sizeOfB);
			else if(middle<sizeOfA)
				combine1(A,left,middle,sizeOfA-1,B,sizeOfB);
		}
		//printf("\n");
		//for(z=0;z<sizeOfA;z++)
			//printf(" %d",A[z]);
		temp=temp/2;
		
		if(temp==1 && right>=sizeOfA)
		{
			//printf("\n--%d--%d--%d--",0,left-1,sizeOfA-1);
			combine1(A,0,left-1,sizeOfA-1,B,sizeOfB);	
		}
		k=k*2;
		l=l*2;
	}
}

void extremeCombine(int A[],int left,int middle, int right,int count[])
{
	int length1,length2,i,j,k;
	int *temp1;
	int *temp2;
	
	temp1 = (int*)malloc((middle-left+1)*sizeof(int));
	temp2 = (int*)malloc((right-middle)*sizeof(int));

	length1=0;
	length2=0;

	for(i=left;i<=middle;i++)
		temp1[length1++]=A[i];
	for(i=middle+1;i<=right;i++)
		temp2[length2++]=A[i];
	
	i=0;
	j=0;
	k=left;
	while(i<length1 && j<length2)
	{
		//printf("\n %d--%d--%d--%d",count[temp1[i]],count[temp2[i]],temp1[i],temp2[j]);
		if(count[temp1[i]]<count[temp2[j]])
			A[k++]=temp1[i++];
		else
			A[k++]=temp2[j++];
	}
	while(i<length1) 
		A[k++]=temp1[i++];
	while(j<length2) 
		A[k++]=temp2[j++];
	if(temp1!=NULL)
	{
		free(temp1);
		temp1=NULL;
	}
	if(temp2!=NULL)
	{
		free(temp2);
		temp2=NULL;
	}	
}

void extremeSort(int A[],int sizeOfA,int B[],int sizeOfB)
{
	int temp=sizeOfA,k=1,l=2,left,right,middle,i,z;

	int *count = (int*)malloc((10*sizeOfA)*sizeof(int));
	for(i=0;i<(10*sizeOfA);i++)
		count[i]=-1;
	for(i=0;i<sizeOfB;i++)
	{
		count[B[i]]=i;
	}	
	//for(i=0;i<(10*sizeOfA);i++)
		//printf(" %d",count[i]);

	while(temp!=1)
	{
		for(i=0;i<sizeOfA;i=i+l)
		{
			left=i;
			middle=k-1+i;
			right=l-1+i;
			//printf("\n--%d--%d--%d--",left,middle,right);
			if(right<sizeOfA)
				extremeCombine(A,left,middle,right,count);
			else if(middle<sizeOfA)
				extremeCombine(A,left,middle,sizeOfA-1,count);
		}
		//printf("\n");
		//for(z=0;z<sizeOfA;z++)
			//printf(" %d",A[z]);
		temp=temp/2;
		
		if(temp==1 && right>=sizeOfA)
		{
			//printf("\n--%d--%d--%d--",0,left-1,sizeOfA-1);
			extremeCombine(A,0,left-1,sizeOfA-1,count);	
		}
		k=k*2;
		l=l*2;
	}
	if(count!=NULL)
	{
		free(count);
		count=NULL;
	}
}

void main()
{
	int i,n,m;
	int *A;
	int *B;
	printf("Enter number of numbers in the array A:");
	scanf("%d",&n);
	A = (int*)malloc((n)*sizeof(int));
	printf("Enter numbers in the array A:");
	for(i=0;i<n;i++)
		scanf("%d",&A[i]);
	superbSorting(A,n);
	printf("\nArray A sorted in non-decreasing order:");
	for(i=0;i<n;i++)
		printf(" %d",A[i]);

	printf("\n\nEnter numbers in the array A:");
	for(i=0;i<n;i++)
		scanf("%d",&A[i]);
	printf("\nEnter number of numbers in the array B:");
	scanf("%d",&m);
	B = (int*)malloc((m)*sizeof(int));
	printf("Enter numbers in the array B:");
	for(i=0;i<m;i++)
		scanf(" %d",&B[i]);
	superbSorting1(A,n,B,m);
	printf("\nArray A after rearranging:");
	for(i=0;i<n;i++)
		printf(" %d",A[i]);

	if(B!=NULL)
	{
		free(B);
		B=NULL;
	}


	printf("\n\nEnter numbers in the array A:");
	for(i=0;i<n;i++)
		scanf("%d",&A[i]);
	printf("\nEnter number of numbers in the array B:");
	scanf("%d",&m);
	B = (int*)malloc((m)*sizeof(int));
	printf("Enter numbers in the array B:");
	for(i=0;i<m;i++)
		scanf(" %d",&B[i]);
	extremeSort(A,n,B,m);
	printf("\nArray A after rearranging:");
	for(i=0;i<n;i++)
		printf(" %d",A[i]);
	printf("\n");

	if(A!=NULL)
	{
		free(A);
		A=NULL;
	}
	if(B!=NULL)
	{
		free(B);
		B=NULL;
	}


}






























