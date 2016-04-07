#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>

class Node {
  public:
    Node* next;
    int data;
  
    Node(int d) {
      data = d;
    }
};

class Queue { //FIFO
public: 
 
 Node* first;
 Node* last;
 
 Queue(int val1, int val2){
   
   first = new Node(val1);
   last = new Node(val2);
   
   first->next = last;
   last->next = NULL;
 }
 
 void enQueue(int val) {
   Node* temp = first;
   Node* newNode = new Node(val);
   
   while( temp->next != NULL){
     temp = temp->next;
   }
   temp->next = newNode;
   last = newNode;
   
 }
 
Node* deQueue() {
  Node* temp = first;
  first = temp->next;
  return first;
   
 }
 
  void printQueue() {
  Node* temp = first;
  for (temp = first; temp->next!= NULL; temp = temp->next){
    std::cout << temp->data << " ";
  }
  std::cout << temp->data << std::endl;
}
};

int main(int argc, char* argv[]) {
  Queue* myq = new Queue(1,2);
  myq->enQueue(6);
  myq->printQueue();
  myq->deQueue();
  myq->printQueue();
  return 0;
}