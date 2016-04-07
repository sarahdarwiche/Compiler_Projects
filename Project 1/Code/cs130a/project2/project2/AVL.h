#ifndef AVL_H
#define AVL_H
#include "node.h"

class AVL {

 public:
  node* root;
  AVL();
  
  
  void insert(int value);
  void access(int value);
  void delete_value(int value);
  void print(); 
  int getBalance(node *N);
  
  
  void insert(int value, node* &n);
  void access(int value, node* n);
  int accessfordelete(int value);
  void delete_value(int value, node *&n);
  void print_preorder(node* n);
  void print_inorder(node* n);
  void print_postorder(node* n);
  
  int accessfordelete(int value, node* n);
  int height(node *n);
  void rotate_with_left(node *&k2);
  void double_with_left(node *&k3);
  void rotate_with_right(node *&k2);
  void double_with_right(node *&k3);
  void breadth_first_print ();

};

#endif
