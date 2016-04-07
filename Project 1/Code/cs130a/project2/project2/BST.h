#ifndef BST_H
#define BST_H
#include "node.h"
class BST {

 public:
  node* root;
  BST();
  // ~BST();
  
  void insert(int value);
  void access(int value);
  int accessfordelete(int value);
  void delete_value(int value);
  void print(); 
  
  
  void insert(int value, node* &n);
  void access(int value, node* n);
  int accessfordelete(int value, node* n);
  void delete_value(int value, node *&n);
  void print_preorder(node* n);
  void print_inorder(node* n);
  void print_postorder(node* n);
  void breadth_first_print ();

};

#endif
