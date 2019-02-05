#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct treenode
{
	char word[100];
	struct treenode *leftchild;
	struct treenode *rightchild;
	struct treenode *parent;
} NODE, *NODEPTR;

NODEPTR insert(NODEPTR x)
{
	char input[100];
	printf("Input String:");
	scanf("%s",input);
	if (x==NULL)
	{
		x=(NODE*)malloc(sizeof(NODE));
		strcpy(x->word,input);
		x->parent = NULL; 
		x->leftchild=NULL;
		x->rightchild==NULL;
		return x;
	}
	else 
	{
		NODEPTR temp=x;
		while(temp!=NULL)
		{
			if( strcmp(temp->word,input) > 0 ) //input < temp->word
			{
				if(temp->leftchild == NULL)
				{
					temp->leftchild=(NODE*)malloc(sizeof(NODE));
					strcpy((temp->leftchild)->word,input);
					(temp->leftchild)->parent = temp; 
					(temp->leftchild)->leftchild=NULL;
					(temp->leftchild)->rightchild==NULL;
					return x;
				}
				else
					temp=temp->leftchild;
			}
			else if( strcmp(temp->word,input) < 0 ) //input > x->word
			{
				if(temp->rightchild == NULL)
				{
					temp->rightchild=(NODE*)malloc(sizeof(NODE));
					strcpy((temp->rightchild)->word,input);
					(temp->rightchild)->parent = x; 
					(temp->rightchild)->leftchild=NULL;
					(temp->rightchild)->rightchild==NULL;
					return x;
				}
				else
					temp=temp->rightchild;
			}
		}
		
	}
	
}

void inorder(NODEPTR x)
{
	if(x!=NULL)
	{
		inorder(x->leftchild);
		printf("%s ",x->word);
		inorder(x->rightchild);
	}
}
int prefix( char A[100],char B[100]) //returns 1 if B is a prefix
{
	int a,b,i;
	a=strlen(A);
	b=strlen(B);
	if(b>a)
		return 0;
	else
	{
		for(i=0;i<b;i++)
		{
			if(A[i]!=B[i])
				return 0;
		}
		return 1;
	} 
}
NODEPTR leftmost(NODEPTR root)
{
	while (root != NULL && root->leftchild != NULL)
       		 root = root->leftchild;
    	return root;
}
NODEPTR rightmost(NODEPTR root)
{
	while (root != NULL && root->rightchild != NULL)
       		 root = root->rightchild;
    	return root;
}
NODEPTR successor(NODEPTR x)
{
	if (x->rightchild != NULL)
	{
     		return leftmost(x->rightchild);
	}
	if(x->rightchild==NULL)
	{
		while(x==x->parent->rightchild)
			x=x->parent;
		return x->parent;
	}
}
void find_extensions(NODEPTR root, char pattern[100])
{
	while(root!=NULL)
	{
		if(prefix(root->word,pattern)==1)
		{
			if(root->leftchild==NULL)
			{
				printf(" %s",root->word);
				root=root->rightchild;
				
			}
			else if(root->rightchild==NULL)
				root=root->leftchild;
			else
			{
				NODEPTR temp1,temp2;
				temp1=root->leftchild;
				temp2=root->leftchild;
				while(temp1!=NULL && temp1->leftchild!=NULL)
					temp1=temp1->leftchild;
				while(temp2!=NULL && temp2->rightchild!=NULL)
					temp2=temp2->rightchild;
				while(temp1!=temp2)
				{
					if(prefix(temp1->word,pattern)==1)
						printf(" %s",temp1->word);
					temp1=successor(temp1);	
				}
				printf(" %s",temp2->word);
				printf(" %s",root->word);
				root=root->rightchild;
			}
		}
		else if ( strcmp(root->word,pattern)>0)
			root=root->leftchild;
		else
			root=root->rightchild;
	}
}

void main()
{
	int n,i;
	char input[100];
	NODEPTR root=NULL;
	printf("Enter the number of words:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		root=insert(root);
	}
	inorder(root);
	printf("\n\n");
	find_extensions(root,"pag");
}



























	
