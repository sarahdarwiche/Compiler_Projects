#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* structure of a stack node */
struct node
{
   int data;
   struct node *next;
};

struct linkedlist {
	struct node *head;
};

void append_tail(struct linkedlist* , int );
void add_head(struct linkedlist* , int );
void delete_node(struct linkedlist* , int );
void print_list(struct linkedlist* );

#endif