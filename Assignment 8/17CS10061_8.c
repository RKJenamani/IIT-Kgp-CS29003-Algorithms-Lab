#include<stdlib.h>
#include<stdio.h>
#include<math.h>

typedef struct score
{
	int mscore;
	int escore;
} score, *scorelist;

int distance(score a, score b)
{
	//printf("\n%d--%d--%d--%d %d\n",a.mscore,a.escore,b.mscore,b.escore,(abs(a.mscore-b.mscore)+abs(a.escore-b.escore) ));
	return (abs(a.mscore-b.mscore)+abs(a.escore-b.escore) );
}

void mergeM(score a[],int lower,int middle,int upper)
{
	score b[10000],c[10000];
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
		if(b[i].mscore>c[j].mscore)
			a[k++]=c[j++];
		else
			a[k++]=b[i++];
	}
	while(i<h1) 
		a[k++]=b[i++];
	while(j<h2) 
		a[k++]=c[j++];

}

void merge_sortM(score a[],int lower,int upper)
{
	if(lower!=upper)
	{
		int middle=(lower+upper)/2;
		merge_sortM(a,lower,middle);
		merge_sortM(a,middle+1,upper);
		mergeM(a,lower,middle,upper);
	}
}

void mergeE(score a[],int lower,int middle,int upper)
{
	score b[1000],c[1000];
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
		if(b[i].escore>c[j].escore)
			a[k++]=c[j++];
		else
			a[k++]=b[i++];
	}
	while(i<h1) 
		a[k++]=b[i++];
	while(j<h2) 
		a[k++]=c[j++];

}

void merge_sortE(score a[],int lower,int upper)
{
	if(lower!=upper)
	{
		int middle=(lower+upper)/2;
		merge_sortE(a,lower,middle);
		merge_sortE(a,middle+1,upper);
		mergeE(a,lower,middle,upper);
	}
}

int explore_strip(score strip[],int size,int current_minimum, score *score1, score *score2)
{
	//printf("IN STRIP");
	//printf("Size%d:",size);		
	int new_minimum=current_minimum;
	int i,j;
	//for(i=0;i<size;i++)
	//{
	//	printf("\nstrip--%d--%d",strip[i].mscore,strip[i].escore);
	//}
	for(i=0;i<size;i++)
	{
		for(j=i+1; (j<size) && abs(strip[i].escore-strip[j].escore)<current_minimum;j++ )
		{
			if(distance(strip[j],strip[i])<new_minimum )
			{
				new_minimum=distance(strip[j],strip[i]);
				(*score1)=strip[j];
				(*score2)=strip[i];
			}
		}
	}
	//printf("Out of strip");
	return new_minimum;
}

int closest_pair(scorelist T_M,scorelist T_E, int l, int r, score *score1, score *score2)
{
	if((r-l)==1)
	{
		*score1=T_M[l];
		*score2=T_M[r];
		return distance(T_M[l],T_M[r]);
	}
	else if((r-l)==2)
	{
		int d1=distance(T_M[l],T_M[l+1]);
		int d2=distance(T_M[l+1],T_M[l+2]);
		int d3=distance(T_M[l],T_M[l+2]);
		if(d1<d2 && d1<d3) //d1 is min
		{
			*score1=T_M[l];
			*score2=T_M[l+1];
			return d1;
		}
		else if(d2<d1 && d2<d3) //d2 is min
		{
			*score1=T_M[l+1];
			*score2=T_M[l+2];
			return d2;
		}
		else //d3 is min
		{
			*score1=T_M[l];
			*score2=T_M[l+2];
			return d3;
		}
	}
	else
	{
		int mid=(l+r)/2;
		score T_E_l[10000],T_E_r[10000];
		int i,j=0,k=0;
		
		for(i=0;i<=(r-l);i++)
		{
			if(T_E[i].mscore<=T_M[mid].mscore)
				T_E_l[j++]=T_E[i];
			else
				T_E_r[k++]=T_E[i];
		}
		//printf("\nstart--->%d--%d--%d--%d<----",score1->mscore,score1->escore,score2->mscore,score2->escore);
		score score3=(*score1);
		score score4=(*score2);
		int a=closest_pair(T_M,T_E_l,l,mid,score1,score2);
		//printf("\nmid--->%d--%d--%d--%d<----",score1->mscore,score1->escore,score2->mscore,score2->escore);
		int b=closest_pair(T_M,T_E_r,mid+1,r,&score3,&score4);
		int minimum=a;
		if(minimum>=b)
		{
			minimum=b;
			(*score1)=score3;
			(*score2)=score4;
		}
		//printf("\nend--->%d--%d--%d--%d<----",score1->mscore,score1->escore,score2->mscore,score2->escore);
		score strip[10000];
		j=0;
		for(i=0;i<=(r-l);i++)
		{
			if(abs(T_E[i].mscore-T_M[mid].mscore)<minimum)
			{
				strip[j++]=T_E[i];
				//printf("\nT_E--%d--%d",T_E[i].mscore,T_E[i].escore);
			}
		}
		return explore_strip(strip,j,minimum,score1,score2);
			

	}
	
}

int NearestProfiles(scorelist T,int n,score *score1,score *score2)
{
	int i;
	scorelist T_M,T_E;
	T_M = (scorelist)malloc((n)*sizeof(score));
	T_E = (scorelist)malloc((n)*sizeof(score));
	for(i=0;i<n;i++)
	{
		T_M[i]=T[i];
		T_E[i]=T[i];
	}
	merge_sortM(T_M,0,n-1);
	merge_sortE(T_E,0,n-1);
	
	return closest_pair(T_M,T_E,0,n-1,score1,score2);
}






int closest_cluster_pair(scorelist section1_M,scorelist section1_E,int l1,int r1, scorelist section2_M, scorelist section2_E,int l2,int r2,score *score1,score *score2)
{
	if((r1-l1)==0)
	{
		int i;
		int minimum=distance(section1_M[l1],section2_M[l2]);
		*score1=section1_M[l1];
		*score2=section2_M[l2];
		for(i=l2+1;i<=r2;i++)
		{
			if(distance(section1_M[l1],section2_M[i])<minimum)
			{
				minimum=distance(section1_M[l1],section2_M[i]);
				*score2=section1_M[l1];
				*score1=section2_M[i];
			}
		}
		return minimum;
	}
	else if((r2-l2)==0)
	{
		int i;
		int minimum=distance(section2_M[l2],section1_M[l1]);
		*score1=section2_M[l2];
		*score2=section1_M[l1];
		for(i=l1+1;i<=r1;i++)
		{
			if(distance(section2_M[l2],section1_M[i])<minimum)
			{
				minimum=distance(section2_M[l2],section1_M[i]);
				*score1=section2_M[l2];
				*score2=section1_M[i];
			}
		}
		return minimum;
	}
	else
	{
		int mid1=(l1+r1)/2;
		score section1_E_l[10000],section1_E_r[10000];
		int i,j=0,k=0;
		
		for(i=0;i<=(r1-l1);i++)
		{
			if(section1_E[i].mscore<=section1_M[mid1].mscore)
				section1_E_l[j++]=section1_E[i];
			else
				section1_E_r[k++]=section1_E[i];
		}


		int mid2=(l2+r2)/2;
		score section2_E_l[10000],section2_E_r[10000];
		j=0;
		k=0;
		
		for(i=0;i<=(r2-l2);i++)
		{
			if(section2_E[i].mscore<=section2_M[mid2].mscore)
				section2_E_l[j++]=section2_E[i];
			else
				section2_E_r[k++]=section2_E[i];
		}

		score score3=(*score1);
		score score4=(*score2);
		int a=closest_cluster_pair(section1_M,section1_E_l,l1,mid1,section2_M,section2_E_l,l2,mid2,score1,score2);

		int b=closest_cluster_pair(section1_M,section1_E_r,mid1+1,r1,section2_M,section2_E_l,mid2+1,r2,&score3,&score4);
		int minimum=a;
		if(minimum>=b)
		{
			minimum=b;
			(*score1)=score3;
			(*score2)=score4;
		}
/*
		//printf("\nend--->%d--%d--%d--%d<----",score1->mscore,score1->escore,score2->mscore,score2->escore);
		score strip[10000];
		j=0;
		for(i=0;i<=(r-l);i++)
		{
			if(abs(T_E[i].mscore-T_M[mid].mscore)<minimum)
			{
				strip[j++]=T_E[i];
				//printf("\nT_E--%d--%d",T_E[i].mscore,T_E[i].escore);
			}
		}
		return explore_strip(strip,j,minimum,score1,score2);*/
		
		return minimum;
			

	}
	
}


int ClusterDist(scorelist section1,int n, scorelist section2,int m,score *score1,score *score2)
{
	int i;
	scorelist section1_M,section1_E;
	section1_M = (scorelist)malloc((n)*sizeof(score));
	section1_E = (scorelist)malloc((n)*sizeof(score));
	for(i=0;i<n;i++)
	{
		section1_M[i]=section1[i];
		section1_E[i]=section1[i];
	}
	merge_sortM(section1_M,0,n-1);
	merge_sortE(section1_E,0,n-1);


	scorelist section2_M,section2_E;
	section2_M = (scorelist)malloc((m)*sizeof(score));
	section2_E = (scorelist)malloc((m)*sizeof(score));
	for(i=0;i<n;i++)
	{
		section2_M[i]=section2[i];
		section2_E[i]=section2[i];
	}
	merge_sortM(section2_M,0,n-1);
	merge_sortE(section2_E,0,n-1);

	return closest_cluster_pair(section1_M,section1_E,0,n-1,section2_M,section2_E,0,m-1,score1,score2);

	
}


int main()
{
	score profile1,profile2;
	score T1[10000],T2[10000];
	int n,m,i;
	printf("Enter number of students:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter math and english scores:");
		scanf("%d",&T1[i].mscore);
		scanf("%d",&T1[i].escore);
	}
	int minimum=NearestProfiles(T1,n,&profile1,&profile2);
	printf("\nClosest pair: (%d,%d) and (%d,%d)",profile1.mscore,profile1.escore,profile2.mscore,profile2.escore);
	printf("\nDistance: %d",minimum);
	printf("\n\n");
	printf("Enter the size of the second cluster:");
	scanf("%d",&m);
	for(i=0;i<m;i++)
	{
		printf("Enter math and english scores:");
		scanf("%d",&T2[i].mscore);
		scanf("%d",&T2[i].escore);
	}
	minimum=ClusterDist(T1, n, T2,m,&profile1,&profile2);
	printf("\nClosest pair: (%d,%d) and (%d,%d)",profile1.mscore,profile1.escore,profile2.mscore,profile2.escore);
	printf("\nDistance: %d",minimum);
	
	return 0;
}
























