/*
 * C++ Program to Implement Hash Tables with Linear Probing and more
 */
 //add .h file 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

// using dynamic resizing with exact doubling and halving of table size s, then the hash func needs to be uniform only when s is power of two. 
//the index can be computed as some range of bits of the hash function. 

//On the other hand, some hashing algorithms prefer to have s be a prime number

const int TABLE_SIZE = 10;

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
    
class hashMap {
  public:
      
    std::vector<int> table;
      
	hashMap() {
		
		table.resize(TABLE_SIZE);
	}

    ~hashMap();
  
    int hash(int value) {
    	int key = value % TABLE_SIZE;
    	return key;
    }
	void linearProbeInsert(int value) {
		/*if(table.size() == TABLE_SIZE) {
			std::cout << "error table is full" << std::endl;
			return;
		}*/
		int key = hash(value);
		if(table[key] == 0)table[key] = value;
		else {
			int probeCounter = (key + 1) % TABLE_SIZE;
			while (table[probeCounter] != 0){
				probeCounter = (probeCounter + 1) % TABLE_SIZE;
			}
			table[probeCounter] = value;
		}
	}
		
	void printTable(){
		std::cout << "table contains:";
  		for (int i=0;i<table.size();i++)
    		std::cout << ' ' << table[i];
  		std::cout << '\n';
  	}
    void remove() {
    }
    void seperateChaining(int) { //use linked list to implement chaining  
    }
    void quadraticProbing() {
    }
	void doubleHashing() {
	}
};

int main()
{
    hashMap* hashtable = new hashMap;
    hashtable->linearProbeInsert(89);
    hashtable->linearProbeInsert(18);
    hashtable->linearProbeInsert(49);
    hashtable->linearProbeInsert(58);
    hashtable->linearProbeInsert(69);
    hashtable->printTable();
    
    
}