#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <fstream>

using namespace std;



void insert(int i);
bool lookup(int i);
int deleteMin();
void delete_element(int i);
void print();

class Node {
public:
  int value;
  int count; // count of number
  Node *next; //set to null for heap
  int *opposite; //points to opposite data structure
  
};

class LinkedList{
public:
  Node *head;
  LinkedList(){ head = NULL;}
  void addHead(int v){ //need to add opposite point in here somehow
    Node *l = new Node();
    l->value = v;
    
    if (head == NULL)
      {
	head = l;
	head->next = NULL;
      }
    else
      {
	l->next = head;
	head = l;
      }
    
  }
};

class Hash_table{
public:
 
 LinkedList ll[43];
  
};

class Heap{

public:
 Node array[80];

};

Heap hp;
Hash_table ht;

int heap_count = 1;
int* heap_ptr = &(hp.array)[1].value;
int* hash_ptr;


  int main (int argc, char* argv[])
 {
   /*if (argc != 2)
     {
       cout << "Error in file" << endl;
       return -1;
     }
 
  char* filename = argv[1];
  ifstream myfile(filename);
   */

   
   while(true){
    string line = "";
    string command = "";
    string num = "";
    bool after_space = false;
    int number_as_integer = 0;
  
    

  
      
     getline( cin, line );
     if(cin.eof()) return -1;
	      
     for(int i=0; i < line.length(); i++){
       
       if ( line[i] != ' ' && after_space == false ){
	 command = command + line[i];
       }
       else{
	 after_space = true;
       }
       if( line[i] != ' ' && after_space == true ) num = num + line[i];
     }
     number_as_integer = atoi(num.c_str());
     
     
     //string command;
     //int number_as_integer;
    
     
    // cin >> command;
     //cin >> number_as_integer;
     
     if(command == "insert") insert(number_as_integer); 
     if(command == "lookup") lookup(number_as_integer);
     if(command == "deleteMin") deleteMin();
     if(command == "delete") delete_element(number_as_integer);
     if(command == "print") print();
     
     
     //  cout << command << endl;
     // cout << number_as_integer << endl;
  
 }
   
  
   // myfile.close();
  return 0;
  
  
 }


void insert(int i){

  //////////////////////////////////////////
  ////////////////insert in heap////////////

  hp.array[heap_count].value = i;
  // cout << "heap contains value******** " << hp.array[heap_count].value << endl;
  int t_count = heap_count;
  int key;

  if(heap_count ==1){
   
    
      /////////////insert in hash ///////////
    if(i>=0) key = i % 43;
    else
      key = (i % 43) + 43;
    ht.ll[key].addHead(i);
    // cout << "key: "<< key << " value: " << ht.ll[key].head->value << endl;
    ht.ll[key].head->count = 1;
    ht.ll[key].head->opposite = &( hp.array)[heap_count].value;
    // cout << "when one element is in the quash, hash table value" << ht.ll[key].head->value <<  "points to " << *(ht.ll)[key].head->opposite << endl;
    // cout << "heap contains value " << hp.array[t_count].value << "points to" <<*( hp.array)[t_count].opposite <<  endl;
    hp.array[heap_count].opposite = &(ht.ll)[key].head->value;
    heap_count++;
    heap_ptr++;
    cout << "item successfully inserted, count = 1" << endl;
    return ;
    //////////////////////////////////////
  }
  while( hp.array[t_count].value < hp.array[t_count/2].value){
    if(hp.array[t_count/2].value < 1) break; ///////////////what?
    
  
    int t_value = hp.array[t_count/2].value;
    hp.array[t_count/2].value = hp.array[t_count].value;
    hp.array[t_count].value = t_value;
    t_count = t_count / 2;
  
  }
 
 
  heap_count++;
  heap_ptr++;

  /////////////////////////////////////////
  //////////////////insert in hash////////
  if(i>=0) key = i % 43;
  else
    key = (i % 43) + 43;
  Node *l;
  if( ht.ll[key].head == NULL){
    ht.ll[key].addHead(i);
    ht.ll[key].head->count = 1;
    //cout << "key: "<< key << " value: " << ht.ll[key].head->value << endl;
    ht.ll[key].head->opposite = &( hp.array)[t_count].value;
    // cout << " hash table contains value " << ht.ll[key].head->value <<  " points to " << *(ht.ll)[key].head->opposite << endl;
     hp.array[t_count].opposite = &(ht.ll)[key].head->value;
    // cout << "heap contains value " << hp.array[t_count].value << " points to" <<*( hp.array)[t_count].opposite <<  endl;
   cout << "item successfully inserted, count = " << ht.ll[key].head->count << endl;
    return;
  }
  else{
    for(l =  ht.ll[key].head; l != NULL; l = l->next){
      if(l->value == i){
	l->count = l->count + 1;
	//	cout << "key: "<< key << " value: " << ht.ll[key].head->value << endl;
	ht.ll[key].head->opposite = &( hp.array)[t_count].value;
	//	cout << " hash table contains value " << ht.ll[key].head->value <<  " points to " << *(ht.ll)[key].head->opposite << endl;
	hp.array[t_count].opposite = &(ht.ll)[key].head->value;
	//	cout << "heap contains value " << hp.array[t_count].value << " points to" <<*( hp.array)[t_count].opposite <<  endl;
	cout << "item already present, new count = " << l->count << endl;
	return;
      }
      ht.ll[key].addHead(i);
      // cout << "key: "<< key << " value: " << ht.ll[key].head->value << endl;
      ht.ll[key].head->count = 1;
    }
    ht.ll[key].head->opposite = &( hp.array)[t_count].value;
    // cout << " hash table contains value " << ht.ll[key].head->value <<  " points to " << *(ht.ll)[key].head->opposite << endl;
    //  cout << "heap contains value " << hp.array[t_count].value << " points to" <<*( hp.array)[t_count].opposite <<  endl;
    hp.array[t_count].opposite = &(ht.ll)[key].head->value;
    cout << "item successfully inserted, count = " << ht.ll[key].head->count << endl;
    return;
  }
}
bool lookup(int i){
  int key;
  if(i>=0) key = i % 43;
  else
    key = (i % 43) + 43;
 
 Node* l;
  if(ht.ll[key].head  == NULL) {
    cout << "item not found" << endl;
    return false;
  }
  
  else{ 
    for(l =  ht.ll[key].head; l != NULL; l = l->next){
      if(l->value == i) {
	cout << "item found, count = " << l->count << endl;
	return true;
      }
    }
    cout << "item found, count = " <<  ht.ll[key].head->count << endl;
    return false;
    
  }
}
int deleteMin(){

 //cout << "here?" << endl;
  int t_count = 1;
  int t_value;
  bool isLeft;
  int minimum;
  int key;
  Node* l;
  
  int return_value = hp.array[1].value;
  if(heap_count == 1){
    cout << "min item not present since table is empty" << endl;
    return 0;
  }
  
  if(return_value >=0) return_value = return_value % 43;
  else
    key = ( return_value % 43) + 43;
  
  for(l =  ht.ll[return_value].head; l != NULL; l = l->next){
    if(l->next == NULL){
      l->count--;
      if(l->count == 0) ht.ll[return_value].head = NULL;
      else {
	Node * temp = l->next;
	l->value = l->next->value;
	l->next = temp->next;
	free(temp);
      }
    }
    
    heap_count--;
    heap_ptr--;
    
    hp.array[1].value = hp.array[heap_count].value; //place last value in first index
    
    
    
    while(t_count <= (heap_count-1)/2){
      if((t_count*2) +1 <= heap_count-1){ //check for right child
	minimum = min( hp.array[t_count*2].value, hp.array[t_count*2 +1].value );
	if(minimum == hp.array[t_count*2].value) isLeft = true;
	else isLeft = false; 
	
      }
      else {
	minimum = hp.array[t_count *2].value;
	isLeft = true;
      }
      if(hp.array[t_count].value > minimum)
	if(isLeft){
	  t_value = hp.array[t_count*2].value;
	  hp.array[t_count*2].value = hp.array[t_count].value;
	  hp.array[t_count].value = t_value;
	  t_count = t_count *2; // jump to next parent
	}
	else{
	  t_value = hp.array[t_count*2 + 1].value;
	  hp.array[t_count*2 + 1].value = hp.array[t_count].value;
	  hp.array[t_count].value = t_value;
	  t_count = t_count *2 + 1; //jump to next parent
	}
      else break;
    }
    
    cout << "min item " << return_value << " successfully deleted" << endl;
    return 0;
    
  }
}

void delete_element(int i){
  Node *l;
  int key;

  if(i>=0) key = i % 43;
  else
    key = key + 43;
  
  for(int a=1; a<heap_count; a++){
    if( hp.array[a].value  == i ) break;
    else 
      cout << "item not present in table" << endl;
  }
  
  for(l =  ht.ll[key].head; l != NULL; l = l->next){
    if(l->next == NULL){
      l->count--;
      if(l->count == 0) ht.ll[key].head = NULL;
      else {
	Node * temp = l->next;
	l->value = l->next->value;
	l->next = temp->next;
	free(temp);
      }
    }
    
  }
}
void print(){
  for(int i=1; i<heap_count; i++){
    cout << hp.array[i].value  << " ";
  }
  cout << "\n";
} 


