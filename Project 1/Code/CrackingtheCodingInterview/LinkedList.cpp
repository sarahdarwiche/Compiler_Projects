#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include "LinkedList.h"



LinkedList::LinkedList() {
  head = new Node(1);
  head->next = NULL;
  head->prev = NULL;
}

LinkedList::LinkedList(int data) {
  head = new Node(data);
  head->next = NULL;
  head->prev = NULL;
}

LinkedList::~LinkedList() {
  
}

void LinkedList::addHead(int data) { //use only for linked list
  if(head == NULL) {
    std::cout << "error list not instantiated" << std::endl;
    return;	
  }
  Node* newnode = new Node(data);
  newnode->next = head;
  head = newnode;
}
void LinkedList::AddNodeForward(int data){
	Node* temp = head;
	Node* newnode = new Node(data);
	if(head == NULL) {
		newnode->prev = NULL;
		newnode->next = NULL;
  	    head = newnode;
	}
	else {
		while(temp->next!=NULL){
			temp = temp->next;
		}
		temp->next = newnode;
		newnode->next = NULL;
		newnode->prev = temp;
	}
}

void LinkedList::AddNodeReverse(int data){
	Node* temp = head;
	Node* newnode = new Node(data);
	if(head == NULL) {
		newnode->prev = NULL;
		newnode->next = NULL;
  	    head = newnode;
	}
	else {
		while(temp->prev!=NULL){
			temp = temp->prev;
		}
		newnode->prev = NULL;
		newnode->next = temp;
		temp->prev = newnode;
		head = newnode;
	}
}

void LinkedList::removeNode(int data) {
	Node* temp = head;
   if(temp->data == data) {
  	temp = head->next;
  	head = temp;
  	head->prev = NULL;
  	return;
   }
   else {
  	while(temp->next != NULL){
  		if(temp->next->data == data){
  			temp->next = temp->next->next;
  			temp->prev = temp;
  			return;
  		}	
  		temp = temp->next;
  		
  	}
  }
}

void LinkedList::removeDuplicates() { //not working with dll
  Node* currptr;
  Node* fastptr;
	for(currptr = head; currptr->next!= NULL; currptr = currptr->next){
		for(fastptr = head->next; fastptr->next!= NULL; fastptr = fastptr->next){
			if((currptr->data == fastptr->data) && (currptr!=fastptr)) { //second check necessary so both duplicates aren't removed
			  this->removeNode(currptr->data);
			  std::cout << currptr->data << std::endl;
			}
		}
	}
}

int LinkedList::find_cycle(){
	 Node* currptr  = head;
	 Node* fastptr = currptr;
	 while(currptr->next != NULL){
	 	if(fastptr == currptr) return currptr->data;
	 	currptr = currptr->next;
	 }
	 return 0;	 	
}

void LinkedList::printList() {
  Node* temp;
  for (temp = head; temp->next!= NULL; temp = temp->next){
    std::cout << temp->data << " ";
  }
  std::cout << temp->data << std::endl;
}

int main(int argc, char* argv[]) {

  LinkedList* List = new LinkedList();
  List->AddNodeForward(1);
  List->AddNodeForward(6);
  List->AddNodeForward(3);
  List->AddNodeForward(9);
  List->AddNodeReverse(4);
  List->removeNode(4);
  List->removeDuplicates();
  List->printList();
  int cycle = List->find_cycle();
  if(cycle != 0) std::cout << "Found cycle in list starting at " << cycle <<  std::endl;
  
}