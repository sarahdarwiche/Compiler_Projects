#ifndef BINARYTREE_H
#define BINARYTREE_H

class node
{
  public:
  int  value;
  node *left;
  node *right;
  
  node(int d) {
      value = d;
    }
};

class binaryTree {
  
  public:
   node* root;
  
   binaryTree();
   binaryTree(int value);
   ~binaryTree();
   
   void insert(int ); //done
   void insertRecursive(int key, node* &parent);//done
   
   void search(int);//done
   void searchRecursive(int value , node* &curr );//done
   
   void printpre(node* node);//done
   void printpost(node* node);//done
   void printin(node* node);//done
   
   void preOrderPrint(node*);//done
   void postOrderPrint(node*);//done
   void inOrderPrint(node*);//done
   
   /* searches a tree (or graph) by searching levels of the tree first, starting at the root.
      It finds every node on the same level, most often moving left to right.
      While doing this it tracks the children nodes of the nodes on the current level.
      When finished examining a level it moves to the left most node on the next level.
      The bottom-right most node is evaluated last (the node that is deepest and is farthest right of it's level).
      
      Optimal for searching a tree that is wider than it is deep
   */
   
   bool breadthFirstSearch(); //use queue (iterative)
   
  /* Optimal for searching a tree that is deeper than it is wide.
    Uses a stack to push nodes onto.
    Because a stack is LIFO it does not need to keep track of the nodes pointers so less memory intensive than BFS
    Once it cannot go further left it begins evaluating the stack. 
    Optimal for searching a tree that is deeper than it is wide.
     
  */
   
   bool depthFirstSearch(node * node); //basically pre order traversal (recursive) - use stack?
   bool isBalanced(); //heights of two subtrees can never differ by more than 1 
   bool isBinarySearchTree();
   
   
   //given directed graph find route between two nodes
   //given a sorted array with unique ints crate binary search tree with min height
   //find next node
   //find first common ancestor
   //print sum of path start node is passed in
  
};
#endif