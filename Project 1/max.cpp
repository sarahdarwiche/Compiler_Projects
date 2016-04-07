#include "max.hpp"


// You will need to implement a complete visitor that
// finds the maximum element in the tree. You can use
// the print and sum visitors for reference.

// WRITEME


void MaxVisitor::visitNode(Node* node) {
	// Hint: for this function, you will need to to use the max
	// member of the object.
	
	// WRITEME
	if(max < node->value) max = node->value;
	node->visit_children(this);
}
