#include "AVL.h"
#include "node.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stack> 
#include <queue>
#include <algorithm>  

using namespace std;


AVL::AVL()
{
	root = NULL;
}

int AVL::height(node *n)
{
	if( n == NULL) return -1;
	else 
		return n->height;
}

int AVL::getBalance(node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}



void AVL::rotate_with_left(node *&k2)
{
    node *k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

void AVL::double_with_left(node *&k3)
{
	rotate_with_right(k3->left);
	rotate_with_left(k3);
}

void AVL::rotate_with_right(node *&k2)
{
    node *k1;
	k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->right), k2->height) + 1;
	k2 = k1;
}

void AVL::double_with_right(node *&k3)
{
	rotate_with_left(k3->right);
	rotate_with_right(k3);
}

void AVL::access(int value){
	access(value, root);
}

void AVL::access(int value, node* n){
	if(n == NULL){
		cout << "Element not found" << endl;
		return;
	}

	if(value == n->data){
		cout << "Element accessed" << endl;
	}
	else if(value < n->data){
		access(value, n->left);
	}
	else if (value > n->data){
	  access(value, n->right);
	}
	else
	  return;

}

void AVL::insert(int value){
  
  insert(value, root);
}

void AVL::insert(int value, node* &n){
  if(n  == NULL){
    n = new node;
    n->data = value;
    n->left = NULL;
    n->right = NULL;
    n->height = 0;
    cout << "Element inserted" << endl;
  }
   
  else if(value > n->data){
    insert(value, n->right);
    if (height(n->right) - height(n->left) == 2) // not balanced
      if (value > n->right->data) rotate_with_right(n);
      else
	double_with_right(n); 
  }
  
  else if(value < n->data){
    insert(value, n->left);
    if (height(n->left) - height(n->right) == 2) // not balanced
      if (value < n->left->data) rotate_with_left(n); 
      else
	double_with_left(n);
  }
  
  else
    cout << "Element already present" << endl;
  n->height = max(height(n->left), height(n->right)) + 1;
}
int AVL::accessfordelete(int value){
	accessfordelete(value, root);
}

int AVL::accessfordelete(int value, node* n){
	if(n == NULL){
		cout << "Element not found" << endl;
		return 0;
	}

	if(value == n->data){
	  //	cout << "Element accessed" << endl;
	}
	else if(value < n->data){
		accessfordelete(value, n->left);
	}
	else if (value > n->data){
	  accessfordelete(value, n->right);
	}
	else
	  return -1;

}

void AVL::delete_value(int value)
{
  cout << value << endl;
  if (accessfordelete(value) == 0) return;
  delete_value(value, root);
}

void AVL::delete_value(int value, node* &n) 
{ 
  if(n == NULL){
        cout << "Element not found" << endl;
        return;
    }
    
	
    if(value < n->data)
        delete_value(value, n->left);
    else if(n->data < value)
        delete_value(value, n->right);
    else if(n->left != NULL && n->right != NULL){
        node *t1 = new node;
        t1 = n->right;
        while(t1->left != NULL){
        	t1 = t1->left;
        }
        n->data = t1->data;
        delete_value(n->data, n->right);
    }
    else{
        node *oldNode = n;
        if(n->left != NULL)
            n = n->left;
        else if(n->right != NULL)
            n = n->right;
        else
            n = NULL;
         delete oldNode;
        cout << "Element deleted" << endl;
    }
    if(n == NULL){
        return;
    }
    n->height = max(height(n->left), height(n->right)) + 1;
    int balance = height(n->left) - height(n->right);
    if(balance > 1){
    	node *q;
    	if (n->left != NULL)
        	q = n->left;
        else
        	q=n;
        int leftCheck = height(q->left) - height(q->right);
        if(leftCheck >= 0)                                                                                                                                                     
            rotate_with_left(n);
        else                                                                                                                                                                     
            double_with_left(n);
    }
    if(balance < -1){
        node *q;
    	if (n->right != NULL)
        	q = n->right;
        else
        	q=n;
        int checkRight = height(q->left) - height(q->right);
        if(checkRight <= 0) 
           rotate_with_right(n);
        else                                                                                                                                                                     
           double_with_right(n);
    }

}

void AVL::breadth_first_print (){
 
  queue <node*> queue;
  node* traverse;
  
  queue.push(root);
  
  while(!queue.empty()) {
  	
  	traverse = queue.front();
  	queue.pop();
  	cout << traverse->data << " ";
  	if(traverse->left != NULL) queue.push(traverse->left);
  	if(traverse->right != NULL) queue.push(traverse->right);
 }
 cout << endl; 
 return;
    }
    
void AVL::print(){

   if(root == NULL) cout << "Empty tree" << endl;

   else{
     
                           //pre order traversal
     print_preorder(root);
     cout << endl;
     
                           //in order traversal
     print_inorder(root);
     cout << endl;
     
                            //post order traversal
     print_postorder(root);
     cout << endl;
   }
}

void AVL::print_preorder(node* n){
 
  stack<node*> stack;
  stack.push( root);
 
  while(stack.empty() == false){
    node*  node = stack.top();
    cout << node->data << " ";
    stack.pop();
    if(node->right) stack.push(node->right);
    if(node->left) stack.push(node->left);
}
}

void AVL::print_inorder(node* n){
 
  stack<node*> stack;
  node* current = root;

  while(!stack.empty() || current){
    if (current) {
      stack.push(current);
      current = current->left;
    } else {
      current = stack.top();
      stack.pop();
      cout << current->data << " ";
      current = current->right;
    }
  }
}


void AVL::print_postorder(node* n){
       
  stack<node*> child;
  stack<node*> parent;
  
  
  child.push(root);  
  
  while (!child.empty()) {  
    node  *curr = child.top();  
    parent.push(curr);  
    child.pop();  
        if (curr->left)  
	  child.push(curr->left);  
        if (curr->right)  
	  child.push(curr->right);  
  }  
  
  while (!parent.empty()) {          
    cout << parent.top()->data << " ";      
    parent.pop();  
  }  
}


 