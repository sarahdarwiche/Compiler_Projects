#ifndef HASH_H
#define HASH_H
#include <vector>
#include <list>

class hashEntry {
public:
      int key; //unique id for each value
      int value;

      hashEntry(int key, int value) {
            this->key = key;
            this->value = value;
      }
};

/*  Using arrays to implement hash tables - poor space complexity
    Using a BST's guarantee Olog(n) find() */
const int TABLE_SIZE = 10;

class hashMap {
  public:
      
      std::list<hashEntry*> table;
      int current_size;

	hashMap();
    hashMap(int,int);
    ~hashMap();
  
    int hash(int);
	void simpleInsert(int);
	void remove();
	
	void seperateChaining(int); //use linked list to implement chaining
	void linerProbing(int key);
	void quadraticProbing();
	void doubleHashing();
	void printTable();
     
 
      
};

#endif