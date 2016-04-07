#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include "binaryTree.h"


binaryTree::binaryTree()
{
   root = new node(-1);
   root->left = NULL;
   root->right = NULL;
}

binaryTree::binaryTree(int value)
{
	root = new node(value);
    root->left = NULL;
    root->right = NULL;
}

binaryTree::~binaryTree()
{
}

void binaryTree::insert(int key)
{
	
	return insertRecursive(key,root);
}
void binaryTree::insertRecursive(int key, node* &currnode)
{
	if(currnode == NULL){
	   currnode = new node(key);
	   return;
	}
	else {
		if(key < currnode->value) 
			return insertRecursive(key, currnode->left);
		else
         	return insertRecursive(key, currnode->right);
    }
		  
}

void binaryTree::search(int key)
{
  return searchRecursive(key,root);
}
void binaryTree::searchRecursive(int value , node* &curr ){
   if(curr->value == value) {
   	  std::cout<< "found " << value << std::endl;
   	  return;
   }
   else if(curr->value < value) {
   	   searchRecursive(value, curr->right);
   }
   else if (curr->value > value) {
   	  searchRecursive(value, curr->left);
   }
   else
   	std::cout<< value << "not found" <<std::endl;
   	  return;
   
}

void binaryTree::printpre(node* node){
	std::cout << "pre order: ";
	return preOrderPrint(root);
	
}
void binaryTree::printpost(node* node){
	std::cout << "post order: " ;
	return postOrderPrint(root);
	
}
void binaryTree::printin(node* node){
	std::cout << "in order: ";
	return inOrderPrint(root);
	
}
void binaryTree::preOrderPrint(node* node)
{
	if(node == NULL) return;
    std::cout << node->value << " ";
  	preOrderPrint(node->left);
  	preOrderPrint(node->right);
  	 
}
void binaryTree::postOrderPrint(node* node)
{
	if(node == NULL) return;
  	postOrderPrint(node->left);
  	postOrderPrint(node->right);
  	std::cout << node->value << " ";
  	 
}
void binaryTree::inOrderPrint(node* node)
{
	if(node == NULL) return;
  	inOrderPrint(node->left);
  	std::cout << node->value << " ";
  	inOrderPrint(node->right);
  	 
}

bool binaryTree::depthFirstSearch(node * node){ //basically pre order traversal (recursive)
	
	if(root == NULL) return false;
	return false;
}
int main(int argc, char*argv[]){
	
	binaryTree* tree = new binaryTree(4);
	tree->insert(2);
	tree->insert(5);
	tree->insert(1);
	tree->insert(3);
	tree->printpre(tree->root);
	std::cout<< "" <<std::endl;
	tree->printpost(tree->root);
	std::cout<< "" <<std::endl;
	tree->printin(tree->root);
	std::cout<< "" <<std::endl;
	tree->search(3);
	
	return 0;
}