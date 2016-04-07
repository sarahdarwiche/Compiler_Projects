#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node {
  public:
    Node* next;
    Node* prev;
    int data;
  
    Node(int d) {
      data = d;
    }
};

class LinkedList {
  Node* head;
  
  public:
    LinkedList(void);
    LinkedList(int data);
    ~LinkedList(void);
    void addHead(int);
    void addTail(int);
    void removeNode(int);
    void AddNodeForward(int);
    void AddNodeReverse(int );
    void removeDuplicates();
    void sortwithPartition(int);
    LinkedList* addDigitsandSum(LinkedList*);
    void printList();
    int find_cycle();
    void isPalindrome();
  
};

#endif