/* Program to implement a linked list and relevant operations */
#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.h"


void append_tail(struct linkedlist* list, int data){
  struct node *new_node;
  struct node *temp = list->head;
  
  new_node = (struct node *) malloc( sizeof(struct node) ); 
  
  new_node->data = data;
  new_node->next = NULL;
  
  if(list->head == NULL) { 
    list->head = new_node;
  }
 
  else {
    //traverse the list
    while(temp->next != NULL){ //reaches 2nd to last
      temp = temp->next;
    }
    temp->next = new_node;
    
  }
}
void add_head(struct linkedlist* list, int data){
  struct node *new_node;
  //struct node *temp = list->head;
  new_node = (struct node *) malloc( sizeof(struct node) ); 
  new_node->data = data; 

  
  if(list->head == NULL){
    list->head = new_node;
    new_node->next = NULL;
  }
  else{
    new_node->next = list->head;
    list->head = new_node; //???
  }
 
}

void delete_node(struct linkedlist* list, int data){
  struct node *temp;
  struct node *prev;
  for(temp = list->head; temp != NULL; temp = temp->next){
    if(temp->data == data){
       prev->next = temp->next;
       free(temp);
       free(prev); 
    }
  }
}

void print_list(struct linkedlist* list){

  	struct node *temp;
	// for each node, print out the int attached to it
	for(temp = list->head; temp != NULL; temp = temp->next) //if we had temp->next!= NULL it would be one short
	{
		// assign f to the int of the right node
		// print the int out
		printf("%d ",temp->data);
			
	}
	printf("\n");
}


int main()
{
  /* Create a linked list */
  struct linkedlist *list = (struct linkedlist *)malloc(sizeof(struct linkedlist));
  list->head = (struct node *) malloc( sizeof(struct node) ); 
  list->head = NULL ;   

  //head->data = 0; //null or 0??
  //head->next = NULL;
 
  printf("Inserting into linked list\n");
  append_tail(list, 1);
  add_head(list, 56);
  append_tail(list, 2);
  add_head(list, 4);
  append_tail(list, 61);
  add_head(list, 334);
  print_list(list);
   
  
   
}