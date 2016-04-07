#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <algorithm>  

// add min function in O(1) time
class Node {
  public:
    Node* next;
    int value;
  
    Node(int d) {
      value = d;
    }
};

class Stack { //LIFO
public:
 Node* top;
 
 Stack(){
   top = new Node(0);
   top->next = NULL;
 }
 Stack(int value){
   top = new Node(value);
   top->next = NULL;
 }
 
Node* pop(){
   
   if(top != NULL){
   	  Node* temp = top;
      top = top->next;
      return temp;
   }
	return NULL;
 }
 int min() {
  return 0; 
 }
 void push(int value){
      int newMin = std::min(value,min());
      Node* newtop = new Node(value);
      newtop->next = top;
      top = newtop;
 }
 
 void peek(){
   std::cout << "peeking at top value "  << top->value << std::endl;
 }
 
 void findmin(){
   std::cout << "min value is  " << std::endl;
 }

//you may only use one additional stack but no toher data structures 
 void sortSmalltoLarge() {
   Stack* helperStack = new Stack();
   
   
 }
 
  void smartSort() {
   Stack* helperStack = new Stack();
    
 }
 
 void printStack() {
  Node* temp = top;
  for (temp = top; temp->next!= NULL; temp = temp->next){
    std::cout << temp->value << std::endl;
  }
  std::cout << temp->value << std::endl;
}

};

int main(int argc, char* argv[]) {
  Stack* stackOne = new Stack(5);
  stackOne->push(6);
  stackOne->push(3);
  stackOne->push(7);
  stackOne->findmin();
  stackOne->pop();
  stackOne->findmin();
  stackOne->pop();
  stackOne->printStack();
  stackOne->findmin();
  //stackOne->printStack();
  return 0;
  
}