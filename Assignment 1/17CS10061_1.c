#include <stdio.h>
#include<time.h>
#include<stdlib.h>
int n;
typedef struct node	
{
        int data;
        struct node* next;
}node,*list;

void traverse_from_front_to_end(list head)
{
	int i;
	list first=head;
	printf("%d ",head->data);
	list second=head->next;
	list display=NULL;
	printf("%d ",second->data);
	for(i=1;i<n-1;i++)		
	{
		display=(list)(((long long)first)^((long long)second->next));
		printf("%d ",display->data);
		first=second;
		second=display;
		
	}
}

void traverse_from_end_to_front(list head)
{
	int i;
	list first=head;
	printf("%d ",head->data);
	list second=head->next;
	list display=NULL;
	printf("%d ",second->data);
	for(i=1;i<n-1;i++)		
	{
		display=(list)(((long long)first)^((long long)second->next));
		printf("%d ",display->data);
		first=second;
		second=display;
		
	}
}

void reverse(list *head, list *tail)
{

	list temp = *head;
	*head=*tail;
	*tail=temp;
}
int main()
{
	
	int array[100],i;
	srand(time(0));
	printf("Input Size :");
	scanf("%d",&n);

	list head=NULL;
	list tail=NULL;

	head=(list)malloc(sizeof(node));
	head->data = rand()%100;
	list previous=head;
	list preprevious=NULL;
	list newpointer=NULL;
	
	for(i=1;i<n;i++)
	{
		newpointer=(list)malloc(sizeof(node));
		newpointer->data = rand()%100;
		previous->next=(list)(((long long)preprevious)^((long long)newpointer));
		printf("%p %p %p %p \n",previous->next,newpointer,previous, preprevious);
		printf("%d \n",previous->data);
		
		preprevious=previous;
		previous=newpointer;
	}
	
	newpointer->next=preprevious;
	tail=newpointer;
	printf("%p \n",tail->next);
	printf("%d \n",tail->data);

	printf("LINKED LIST: \n");	
	
	traverse_from_front_to_end(head);
	printf("\n");
	traverse_from_end_to_front(tail);

	reverse(&head,&tail);
	printf("\n REVERSED \n");

	traverse_from_front_to_end(head);
	printf("\n");
	traverse_from_end_to_front(tail);


	

}


		
	

