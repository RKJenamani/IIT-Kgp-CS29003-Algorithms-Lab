//Rajat Kumar Jenamani
//17CS10061

#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
	int value;
	struct node *left;
	struct node *right;
	struct node *parent;
}NODE, *NODEPTR;

void preOrder(NODEPTR root)
{
	if(root!=NULL)
	{
		printf(" %d ",root->value);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(NODEPTR root)
{
	if(root!=NULL)
	{
		inOrder(root->left);
		printf(" %d ",root->value);
		inOrder(root->right);
	}
}
NODEPTR search(NODEPTR x,int k)
{
	if(x==NULL)
		return NULL;
	else if ( x->value == k)
		return x;
	else if ( x->value > k)
		return search(x->left,k);
	else
		return search(x->right,k);
}
NODEPTR right_rotate(NODEPTR root, NODEPTR x)
{
	NODEPTR y=NULL;
	y=x->left;
	x->left=y->right;
	if(y->right!=NULL)
		y->right->parent=x;
	y->parent=x->parent;
	if(x->parent==NULL)
		root=y;
	else if(x->parent->left==x)
		x->parent->left=y;
	else
		x->parent->right=y;
	y->right=x;
	x->parent=y;
	return root;
	
}

NODEPTR left_rotate(NODEPTR root, NODEPTR x)
{
	NODEPTR y=NULL;
	y=x->right;
	x->right=y->left;
	if(y->left!=NULL)
		y->left->parent=x;
	y->parent=x->parent;
	if(x->parent==NULL)
		root=y;
	else if(x->parent->right==x)
		x->parent->right=y;
	else
		x->parent->left=y;
	y->left=x;
	x->parent=y;
	return root;
	
}

NODEPTR makeRoot(NODEPTR root, NODEPTR N)
{
	if(root->left==N)
		root=right_rotate(root,root);
	else if(root->right==N)
		root=left_rotate(root,root);
	return root;
}

NODEPTR sameOrientation(NODEPTR root, NODEPTR N)
{
	if( ( N->parent->parent->left == N->parent) && (N->parent->left==N ) )
	{
		root=right_rotate(root,N->parent->parent);
		root=right_rotate(root,N->parent);
	} 
	else if ( ( N->parent->parent->right == N->parent) && (N->parent->right==N) )
	{
		root=left_rotate(root,N->parent->parent);
		root=left_rotate(root,N->parent);
	}
	return root;
}

NODEPTR oppositeOrientation(NODEPTR root, NODEPTR N)
{
	if( (N->parent->parent->left == N->parent) && (N->parent->right==N) )
	{
		root=left_rotate(root,N->parent);
		root=right_rotate(root,N->parent);
	}
	else if( (N->parent->parent->right == N->parent) && (N->parent->left==N) )
	{
		root=right_rotate(root,N->parent);
		root=left_rotate(root,N->parent);
	}
	return root;
}
NODEPTR lift_insert(NODEPTR root,NODEPTR N)
{
	while(N!=root)
	{
		if(N->parent==root)
			root=makeRoot(root,N);
		else if ( ( ( N->parent->parent->left == N->parent) && (N->parent->left==N ) ) || ( ( N->parent->parent->right == N->parent) && (N->parent->right==N) ) )
			root=sameOrientation(root,N);
		else if ( ( ( N->parent->parent->left == N->parent) && (N->parent->right==N) ) || ( (N->parent->parent->right == N->parent) && (N->parent->left==N) ) )
			root=oppositeOrientation(root,N);
	}
	return root;
}






NODEPTR insert(NODEPTR x,int key)
{
	int input=key;
	if (x==NULL)
	{
		x=(NODE*)malloc(sizeof(NODE));
		x->value = input;
		x->parent = NULL; 
		x->left=NULL;
		x->right=NULL;
		return x;
	}
	else 
	{
		NODEPTR temp=x;
		while(temp!=NULL)
		{
			if( temp->value > input ) //input < temp->value
			{
				if(temp->left == NULL)
				{
					temp->left=(NODE*)malloc(sizeof(NODE));
					(temp->left)->value=input;
					(temp->left)->parent = temp; 
					(temp->left)->left=NULL;
					(temp->left)->right=NULL;
					temp=temp->left;
					break;
				}
				else
					temp=temp->left;
			}
			else if( temp->value < input ) //input > x->value
			{
				if(temp->right == NULL)
				{
					temp->right=(NODE*)malloc(sizeof(NODE));
					(temp->right)->value=input;
					(temp->right)->parent = temp; 
					(temp->right)->left=NULL;
					(temp->right)->right=NULL;
					temp=temp->right;
					break;
				}
				else
					temp=temp->right;
			}
		}
		x=lift_insert(x,temp);
		return x;
	}
}

NODEPTR leftmost(NODEPTR root)
{
	while (root != NULL && root->left != NULL)
       		 root = root->left;
    	return root;
}
NODEPTR rightmost(NODEPTR root)
{
	while (root != NULL && root->right != NULL)
       		 root = root->right;
    	return root;
}

NODEPTR successor(NODEPTR x)
{
	if (x->right != NULL)
	{
     		return leftmost(x->right);
	}
	if(x->right==NULL)
	{
		while(x==x->parent->right)
			x=x->parent;
		return x->parent;
	}
}

NODEPTR delete(NODEPTR root, int key)
{
	NODEPTR N;
	N=search(root,key);
	NODEPTR M=N->parent;
	while(root!=NULL)
	{
		if(N->left==NULL && N->right==NULL)
		{
			if(N->parent==NULL) 
				return NULL;
			NODEPTR temp=N->parent;
			if(temp->left==N)
				temp->left=NULL;
			else
				temp->right=NULL;
			N->parent=NULL;
			break;
		}
		else if(N->left==NULL)
		{
			NODEPTR temp=N->right;
			N->right==NULL;
			temp->parent=N->parent;
			if(N->parent!=NULL)
			{
				if(temp->parent->left==N)
					temp->parent->left=temp;
				else
					temp->parent->right=temp;
			}
			else
				root=temp;
			N->parent=NULL;
			break;
		}
		else if(N->right==NULL)
		{
			NODEPTR temp=N->left;
			N->left=NULL;
			temp->parent=N->parent;
			if(N->parent!=NULL)
			{
				if(temp->parent->left==N)
					temp->parent->left=temp;
				else
					temp->parent->right=temp;
			}
			else
				root=temp;
			N->parent=NULL;
			break;
		}
		else
		{
			NODEPTR temp=successor(N);
			N->value=temp->value;
			N=temp;	
		}	
	}
	if(M!=NULL)
	{
		root=lift_insert(root,M);
	}
	return root;
	
}

void main()
{
	int n,i,s,l;
	NODEPTR root=NULL,current=NULL;
	printf("Enter the number of insertions:");
	scanf("%d",&n);
	printf("Input Numbers to be inserted:");
	for(i=0;i<n;i++)
	{
		scanf("%d",&s);
		if(search(root,s)==NULL)
		{
			root=insert(root,s);
		}
	}
	printf("\nPreorder traversal:");
	preOrder(root);
	printf("\nInorder traversal:");
	inOrder(root);
	printf("\nEnter the number of deletions:");
	scanf("%d",&l);
	for(i=0;i<l;i++)
	{
		printf("\nInput value to be deleted:");
		scanf("%d",&s);
		if(search(root,s)!=NULL)
		{
			root=delete(root,s);
			printf("\nPreorder traversal:");
			preOrder(root);
			printf("\nInorder traversal:");
			inOrder(root);
			printf("\n");
		}
		else
			printf("Number not found\n");
	}
}



















