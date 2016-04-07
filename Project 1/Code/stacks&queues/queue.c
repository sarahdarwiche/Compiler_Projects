/* Program to implement a queue using two stacks */
#include<stdio.h>
#include<stdlib.h>
 
/* structure of a stack node */
struct sNode
{
   int data;
   struct sNode *next;
};
  
/* Function to push an item to stack*/
void push(struct sNode** top_ref, int new_data);
  
/* Function to pop an item from stack*/
int pop(struct sNode** top_ref);
  
/* structure of queue having two stacks */
struct queue
{
   struct sNode *stack1;
   struct sNode *stack2;
};
 
/* Function to enqueue an item to queue */
void enQueue(struct queue *q, int x){
  //push onto stack one 
  push(&q->stack1, x);
  
}
/* Function to dequeue an item from queue */
int deQueue(struct queue *q){ 
  //if stack two is empty pop x from stack 1 and push x to stack two
  //then pop stack two
  
  int data;
  
  /* If both stacks are empty then error */
   if(q->stack1 == NULL && q->stack2 == NULL)
   {
      printf("Q is empty");
      getchar();
      exit(0);
   }
  
  if(q->stack2 == NULL){
    while(q->stack1 != NULL){
      data = pop(&q->stack1);
      push(&q->stack2, data);
    }  
  }
   data = pop(&q->stack2);
   return data;
}

/* Function to push an item to stack*/
void push(struct sNode** top_ref, int new_data){

  struct sNode* newNode = (struct sNode*)malloc(sizeof(struct sNode));

  if(newNode == NULL)
  {
     printf("Stack overflow \n");
     getchar();
     exit(0);
  }   

  
  newNode->data = new_data;
  newNode->next = (*top_ref);
  (*top_ref) = newNode;
   
}

/* Function to pop an item from stack*/
int pop(struct sNode** top_ref){
  int result;
  struct sNode *top_temp;
  
   /*If stack is empty then error */
  if(*top_ref == NULL)
  {
     printf("Stack overflow \n");
     getchar();
     exit(0);
  }
  else
  {
  
  	top_temp = *top_ref;
  	result = top_temp->data;
  	*top_ref = top_temp->next;
  	free(top_temp);
  	return result;
  }
}

/* Driver function to test anove functions */
int main()
{
   /* Create a queue with items 1 2 3*/
   struct queue *q = (struct queue*)malloc(sizeof(struct queue));
   q->stack1 = NULL;
   q->stack2 = NULL;
   printf("Inserting into queue\n");
   enQueue(q, 1);
   enQueue(q, 5);
   enQueue(q, 2);
   enQueue(q, 8);
   enQueue(q, 3);
   enQueue(q, 5);    
  
   /* Dequeue items */
   printf("Removing from queue\n");
   printf("%d  ", deQueue(q));
   printf("%d  ", deQueue(q));
   printf("%d  ", deQueue(q)); 
   printf("%d  ", deQueue(q));
   printf("%d  ", deQueue(q));
   printf("%d  ", deQueue(q)); 
  
   
}