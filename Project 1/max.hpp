#ifndef _MAX_HPP
#define _MAX_HPP

#include "tree.hpp"
# include <limits.h>

// You will need to implement a complete visitor that
// finds the maximum element in the tree. You can use
// the print and sum visitors for reference.

// WRITEME
// A visitor which sums all the node values in
// the tree. You need to implement the visitNode
// function for this visitor.
class MaxVisitor : public Visitor {
public:
	int max;
	MaxVisitor() : max(INT_MAX) {}
	
	void visitNode(Node* node);
};



#endif
