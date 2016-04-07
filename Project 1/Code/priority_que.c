/* Program to implement a priority queue */
#include<stdio.h>
#include<stdlib.h>

/* structure of a stack node */
struct sNode
{
   int data;
   struct sNode *next;
};

/* Driver function to test above functions */
int main()
{
   /* Create a queue with items 1 2 3 */
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
  
  
   
}