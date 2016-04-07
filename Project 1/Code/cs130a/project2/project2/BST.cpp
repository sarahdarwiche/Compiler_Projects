using namespace std;
#include "node.h"
#include "BST.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stack> 
#include <queue> 


BST::BST(){
  root = NULL;
}

void BST::insert(int value){
  
  insert(value, root);
}

void BST::insert(int value, node* &n){
  if(n  == NULL){
    n = new node;
    n->data = value;
    n->left = NULL;
    n->right = NULL;
    cout << "Element inserted" << endl;
  }
   
  else if(value > n->data){
    insert(value, n->right);
  }

 else if(value < n->data){
    insert(value, n->left);
  }
  
  else
    cout << "Element already present" << endl;
  
}


void BST::access(int value){
	access(value, root);
}

void BST::access(int value, node* n){
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

int BST::accessfordelete(int value){
	accessfordelete(value, root);
}

int  BST::accessfordelete(int value, node* n){
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


void BST::delete_value(int value)
{
  if (accessfordelete(value) == 0) return;
  delete_value(value, root);
}

void BST::delete_value(int value, node* &n) 
{ 
   if(n->left == NULL && n->right == NULL){
		cout << "Element not found" << endl;
		return;
	}

	if(value == root->data){
		node *l = root->left;
		node *r = root->right;

		//root has 0 or 1 children
		if(l== NULL || r == NULL){
			if(l == NULL && r == NULL){
				root = NULL;
			}
			else if(l == NULL){
				root = r;
			}
			else if(r == NULL){
				root = l;
			}
		}

		//root has 2 children
		else{
			node *t1 = root->right;
			node *t2 = root->right;
			if(t1->left != NULL){
				t1 = t1->left;
			}
			while(t1->left != NULL){
				t1 = t1->left;
				t2 = t2->left;
			}
			if(t1->data == t2->data){
				root->right->left = root->left;
				root = root->right;
			}
			else{
				root->data = t1->data;
				t2->left = NULL;
			}
		}

		cout << "Element deleted" << endl;
	}
	else if(n->left != NULL && value == n->left->data){
		node *left = n->left->left;
		node *right = n->left->right;

		//node has 0 or 1 children
		if(left == NULL || right == NULL){
			if(left == NULL && right == NULL){
				n->left = NULL;
			}
			else if(left == NULL){
				n->left = n->left->right;
			}
			else if(right == NULL){
				n->left = n->left->left;
			}
		}

		//node has 2 children
		else{
			node *t1 = n->left->right;
			node *t2 = n->left->right;
			if(t1->left != NULL){
				t1 = t1->left;
			}
			while(t1->left != NULL){
				t1 = t1->left;
				t2 = t2->left;
			}
			if(t1->data == t2->data){
				n->left->right->left = n->left->left;
				n->left = n->left->right;
			}
			else{
				n->left->data = t1->data;
				t2->left = NULL;
			}
		}

		cout << "Element deleted" << endl;
	}
	else if(n->right != NULL && value == n->right->data){
		node *left = n->right->left;
		node *right = n->right->right;

		//node has 0 or 1 children
		if(left == NULL || right == NULL){
			if(left == NULL && right == NULL){
				n->right = NULL;
			}
			else if(left == NULL){
				n->right = n->right->right;
			}
			else if(right == NULL){
				n->right = n->right->left;
			}
		}

		//node has 2 children
		else{
			node *t1 = n->right->right;
			node *t2 = n->right->right;
			if(t1->left != NULL){
				t1= t1->left;
			}
			while(t1->left != NULL){
				t1 = t1->left;
				t2 = t2->left;
			}
			if(t1->data == t2->data){
				n->right->right->left = n->right->left;
				n->right = n->right->right;
			}
			else{
				n->right->data = t1->data;
				t2->left = NULL;
			}
		}
		cout << "Element deleted" << endl;
	}
	else if(value < n->data){
		delete_value(value, n->left);
	}
	else if(value > n->data){
		delete_value(value, n->right);
	}



  if(n == NULL){ //should I get rid of this?
    cout << "Element not found" << endl;
    return;
  }

  if (accessfordelete(value) == 0) return;
  
  
  if(value == root->data){ // if value to be deleted is at root
    node *left = root->left;
    node *right = root->right;
    
    //root has 0 or 1 children
    if(left == NULL || right == NULL){
      if(left == NULL && right == NULL){
	root = NULL;
	cout << "Element deleted" << endl;
	return;
      }
      else if(left == NULL){
	root = right;
	cout << "Element deleted" << endl;
	return;
      }
      else if(right == NULL){
	root = left;
	cout << "Element deleted" << endl;
	return;
      }
    }
    
    //root has 2 children
    else{
      node *temp_parent = root->right; //leftmost side of right subtree
      node *temp = root->right;
      if(temp->left != NULL){
	temp = temp->left;
      }
      while(temp->left != NULL){
	temp = temp->left;
	temp_parent = temp_parent->left;
      }
      if(temp->data == temp_parent->data){
	root->right->left = root->left;
	root = root->right;
	cout << "Element deleted" << endl;
	return;
      }
      else{
	root->data = temp->data;
	temp_parent->left = NULL;
	cout << "Element deleted" << endl;
	return;
      }
    }
  }
    
    
  //if value is not at node

  node* current;
  node* parent;
  current = root;

  //put parent pointer in the right place
  while(current != NULL){
    if(current->data == value){
      //cout << current->data << endl;
      break;
    }
    else{
      parent = current;
      if(value > current->data) current = current->right;
      else
	current = current ->left;
    }
  }
 
  //leaf node
  if(current->left == NULL && current->right == NULL){
    if(parent->left == current){
      parent->left = NULL;
    }
    else{
      parent->right = NULL;
    }
    cout << "Element deleted" << endl;
    return;
    }

 //one child
    if((current->left == NULL && current->right!= NULL) || (current->right == NULL && current->left!= NULL))
      {
	if(current->left == NULL && current-> right != NULL){ //right child present with no left
	  if(parent->left == current) parent->left = current->right;
	  else 
	    parent->right = current->right;
	}
	else{
	  //left child present with no right child
	  if(parent->left == current) parent->left = current->left;
	  else 
	    parent->right = current->right;
	}
	cout << "Element deleted" << endl;
	return;
      }

    //two children
    if(current->left != NULL && current->right != NULL){
      node* temp;
      temp = current->right;

      if((temp->left == NULL) && (temp->right == NULL)){
	current = temp;
	current->right = NULL;
	cout << "Element deleted" << endl;
	return;
      }
      else{  // if right child has children
	if((current->right)->left != NULL){
	  node* current_right;
	  node* current_right_left;
	  current_right = current->right;
	  current_right_left = current->right->left;

	  while(current_right_left->left != NULL){
	    current_right = current_right_left;
	    current_right_left = current_right_left->left;
	  }
	  current->data = current_right_left->data;
	  current_right->left = NULL;
	  cout << "Element deleted" << endl;
	  return;
	}
	else{
	  node* tmp;
	  tmp = current->right;
	  current->data = tmp->data;
	  current->right = tmp->right;
	  cout << "Element deleted" << endl;
	  return;
	}
      }
      
    }
    //should never reach this
    cout << "Element not found" << endl;
    return;
}

void BST::breadth_first_print (){
 
  
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

void BST::print(){

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

void BST::print_preorder(node* n){
 
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

void BST::print_inorder(node* n){
 
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


void BST::print_postorder(node* n){
       
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

