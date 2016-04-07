using namespace std;
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stack> 
#include <queue> 
#include "BST.h"

 int main (int argc, char* argv[])
 {
   BST *binary_search_tree = new BST();

   while(true){
    string line = "";
    string command = "";
    string num = "";
    string second_half = "bfs";
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
     if (num.compare(second_half) == 0) command = command + num;
     number_as_integer = atoi(num.c_str());
     
     if(command == "insert") binary_search_tree->insert(number_as_integer); 
     if(command == "access") binary_search_tree->access(number_as_integer);
     if(command == "print")  binary_search_tree->print();
     if(command == "printbfs")  binary_search_tree->breadth_first_print();
     if(command == "delete") binary_search_tree->delete_value(number_as_integer);
     
   }
   
   return 0;
   
 }
