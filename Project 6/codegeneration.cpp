#include "codegeneration.hpp"

// CodeGenerator Visitor Functions: These are the functions
// you will complete to generate the x86 assembly code. Not
// all functions must have code, many may be left empty.
//
// NOTE: You only need to complete code for expressions,
// assignments, returns, and local variable space allocation.
// Refer to project description for exact details.

void CodeGenerator::visitProgramNode(ProgramNode* node) {
    // WRITEME: Replace with code if necessary
    //Below correct???
    std::cout<< ".data" <<std::endl;
	std::cout<< "printstr: .asciz \"%d\\n\"" <<std::endl;
	std::cout<< ".text "<< std::endl;
    
    std::cout << "  .globl Main_main" << std::endl;
    node->visit_children(this); 
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    // WRITEME: Replace with code if necessary
    
    currentClassName = node->identifier_1->name;
    currentClassInfo =(*classTable)[currentClassName];
    node->visit_children(this); 
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    // WRITEME: Replace with code if necessary
    currentMethodName = node->identifier->name;
    currentMethodInfo = (this->currentClassInfo.methods)[currentMethodName];
    std::cout << currentClassName << "_" << currentMethodName << ":" << std::endl;

    std::cout << "  # Prologue" << std::endl;
    std::cout << "  push %ebp" << std::endl;
    std::cout << "  mov %esp, %ebp" << std::endl;
    std::cout << "  sub $" << currentMethodInfo.localsSize << ", %esp" << std::endl; 
    std::cout << "  push %ebx" << std::endl;
    std::cout << "  push %edi" << std::endl;
    std::cout << "  push %esi" << std::endl;
    
    node->visit_children(this);
    
    std::cout << "  # Epilogue" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  pop %esi" << std::endl;
    std::cout << "  pop %edi" << std::endl;
    std::cout << "  pop %ebx" << std::endl;
    std::cout << "  mov %ebp, %esp" << std::endl; //deallocate space
    std::cout << "  pop %ebp" << std::endl;
    std::cout << "  ret" << std::endl;
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this); 
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this); 
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    // WRITEME: Replace with code if necessary
     node->visit_children(this);  
}

/*void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "# Assignment" << std::endl;
    node->visit_children(this); 
    std::cout << "  pop " << currentMethodInfo.variables[node->identifier->name].offset << "(%ebp)" <<std::endl; 
}*/

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    
	
	node->expression->accept(this);
std::cout << "## Assignment" << std::endl;
	
	//std::cout << " pop %eax" << std::endl;
	
	if(currentMethodInfo.variables.find(node->identifier->name) == currentMethodInfo.variables.end()){
		std::cout << "mov 8(%ebp), %ebx" << std::endl;
		std::cout << " pop 0(%ebx)" << std::endl;
	}
	else{
	  //std::cout << "mov 8(%ebp), %ebx" << std::endl; 
	  std::cout << " pop " << currentMethodInfo.variables[node->identifier->name].offset << "(%ebp)" << std::endl;
	}
       	
}


void CodeGenerator::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
     node->visit_children(this);
    // std::cout << "sub $4, (%esp)" << std::endl;
    
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    // FILL IN
    int label_one,label_two;
    label_one = nextLabel();
    label_two = nextLabel();
    
    std::cout << "# If" << std::endl;
    node->expression->accept(this);
    std::cout << "pop %eax" << std::endl;
    std::cout << "mov $0, %ebx" << std::endl;
    std::cout << "cmp %ebx, %eax" << std::endl;
    std::cout << "je " << "label" << label_one << std::endl;
    for(std::list<StatementNode*>::iterator iter = node->statement_list_1->begin(); iter != node->statement_list_1->end(); iter++) { 
    	(*iter)->accept(this);
    }
    std::cout << "jmp label" << label_two << std::endl;
    std::cout << "label" << label_one << ":"<< std::endl; 
    if(node->statement_list_2 != NULL) {
    	for(std::list<StatementNode*>::iterator iter = node->statement_list_2->begin(); iter != node->statement_list_2->end(); iter++) { 
    		(*iter)->accept(this);
   		 }
   	}
    std::cout << "label"<<label_two << ":" << std::endl; // blank label
}

void CodeGenerator::visitForNode(ForNode* node) {
    int label_one, label_two;
    label_one = nextLabel();
    label_two = nextLabel();
    
    std::cout << "# For" << std::endl;
    node->assignment_1->accept(this);
    std::cout << "label" << label_one <<  ":" << std::endl;
    node->expression->accept(this);
    std::cout << "pop %eax" << std::endl;
    std::cout << "mov $0, %ebx" << std::endl;
    std::cout << "cmp %eax, %ebx " << std::endl; //$0 to top of stack
    std::cout << "je label" << label_two << std::endl;
    for(std::list<StatementNode*>::iterator iter = node->statement_list->begin(); iter != node->statement_list->end(); iter++) { 
    	(*iter)->accept(this);
    }
    node->assignment_2->accept(this);
    std::cout << "jmp label" << label_one<< std::endl; 
    std::cout << "label" << label_two <<  ":" << std::endl;
    
    
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
	node->visit_children(this);
	std::cout << "# Print" << std::endl;
    std::cout << "push $printstr" << std::endl; 
    std::cout << "call printf" << std::endl;
}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    std::cout << "  # Plus" << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  add %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    std::cout << "  # Minus" << std::endl;
    std::cout << "  pop %edx" << std::endl; 
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  sub %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    std::cout << "  # Times" << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  imul %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);  
    std::cout << "  # Divide" << std::endl;
    std::cout << "  pop %ebx" << std::endl;  
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  cdq" << std::endl;
    std::cout << "  idiv %ebx" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitLessNode(LessNode* node) {
    // FILL IN
    // 1 as true
     int label_one, end_label;
    label_one = nextLabel();
    end_label = nextLabel();
    std::cout << "  # Less Than" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "pop %ebx" << std::endl;
    std::cout << "cmp %eax, %ebx" << std::endl;
	std::cout << "jl " << label_one << std::endl;
	std::cout << "push $0" << std::endl;
	std::cout << "jmp label" << end_label << std::endl;
	std::cout << label_one << ": push $1" << std::endl;
	std::cout << "label" << end_label << ":" << std::endl;
	
	
}

void CodeGenerator::visitLessEqualNode(LessEqualNode* node) {
    int label_one, end_label;
    label_one = nextLabel();
    end_label = nextLabel();
    node->visit_children(this);
    std::cout << "  # Less Than or Equal" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "pop %ebx" << std::endl;
    std::cout << "cmp %eax, %ebx" << std::endl;
	std::cout << "jle label" <<label_one << std::endl;
	std::cout << "  push $0" << std::endl;
	std::cout << "jmp label" << end_label << std::endl;
	std::cout << "label" <<label_one << ": push $1" << std::endl;
	std::cout << "label" << end_label << ":" << std::endl;
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    // FILL IN
     int label_one, end_label;
    label_one = nextLabel();
    end_label = nextLabel();
    node->visit_children(this);
    std::cout << "  # Equal" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "pop %ebx" << std::endl;
    std::cout << "cmp %eax, %ebx" << std::endl;
	// je equal
	std::cout << "je " << label_one << std::endl;
	std::cout << " push $0" << std::endl;
	std::cout << "jmp label" << end_label << std::endl;
	std::cout << label_one << ": push $1" << std::endl;
	std::cout << "label" << end_label << ":" << std::endl;
}

void CodeGenerator::visitAndNode(AndNode* node) {
     //and src, dest
     std::cout << "# And" << std::endl;
     node->visit_children(this);
     std::cout << "pop %eax" << std::endl;
     std::cout << "pop %ebx" << std::endl;
	 std::cout << "and  %eax, %ebx" << std::endl;
	 std::cout << "push %ebx" << std::endl;
}

void CodeGenerator::visitOrNode(OrNode* node) {
     //or src, dest
     std::cout << "# Or" << std::endl;
     node->visit_children(this);
     std::cout << "pop %eax" << std::endl;
     std::cout << "pop %ebx" << std::endl;
	 std::cout << "or  %eax, %ebx" << std::endl;
	 std::cout << "push %ebx" << std::endl;

}

void CodeGenerator::visitNotNode(NotNode* node) {
     //xor src, dest
     std::cout << "# Not" << std::endl;
     node->visit_children(this);
     std::cout << "pop %ecx" << std::endl;
     std::cout << "mov $1, %edx" << std::endl;
	 std::cout << "xor %edx, %ecx" << std::endl;
	 std::cout << "push %ecx" << std::endl;
	 
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    std::cout << "  # Negation" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  neg %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
     //Pre-Call
     int stack_space = 4;
     std::cout << "  push %ecx" << std::endl;
     std::cout << "  push %edx" << std::endl;
     //push arguments in reverse order(from right end to left end)
     std::list<ExpressionNode*>::reverse_iterator rit;
     for (rit=node->expression_list->rbegin(); rit!=node->expression_list->rend(); ++rit){
       (*rit)->accept(this);
       stack_space = stack_space + 4;
     }
     
     	std::cout << "  push 8(%ebp)" << std::endl;
     	if(node->identifier_2 == NULL) std::cout << "  push 8(%ebp)" << std::endl; 
     	else {
     		if(currentMethodInfo.variables.count(node->identifier_1->name)) {
     			std::cout << "  push "<< currentMethodInfo.localsSize << "(%ebp)" << std::endl;
     			}
     		else {
     			std::cout << "  push " << currentClassInfo.members[node->identifier_1->name].offset << "(%ebp)" << std::endl;
     			}
     	}
     
	//inheritance
     //determine which class contains the method 
     //(use class table to access super class to check for called method)
     //remember: unlimited levels of hierarchy
    
    /*if (currentClassInfo.members.count(node->identifier_1->name))  { //if current class contains method (change to methods!!!)
    	std::cout << "call" <<currentClassName << "_" << currentMethodName << std::endl;

    }
    else { //current class does not contain method
    	//std::cout << "call" <<currentMethodInfo.variables[node->identifier_1->name].type.objectClassName << "_" << currentMethodName << std::endl;
    }*/
    
  
	if(node->identifier_2 != NULL){

		std::string x = currentClassInfo.methods[currentMethodName].variables[node->identifier_1->name].type.objectClassName;
	 	
	  	if((*classTable)[x].methods.count(node->identifier_2->name)){
	    	//std::cout<< " call "<< (*classTable)[currentClassName].members[node->identifier_1->name] << "_" << node->identifier_2->name<<std::endl;
	   	}
	  	else {
	    	//std::cout<<" call "<< (*classTable)[currentClassName].methods[currentMethodName].variables[node->identifier_1->name].type.objectClassName<<"_"<< node->identifier_2->name<<std::endl;
	  	}
	  }
	
	else {
	  std::cout << " call " << currentClassName << "_" << node->identifier_1->name << std::endl;
	}
    
    //Post-Call
    std::cout << "  add $"<< stack_space <<", %esp" << std::endl; 
    std::cout << "  pop %edx" << std::endl;
	std::cout << "  pop %ecx" << std::endl;
    std::cout << "  push %eax" << std::endl;        
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    /*
    if(currentMethodInfo.variables.count(node->identifier_1->name)){
    	std::cout << "  mov " << currentMethodInfo.variables[node->identifier_1->name].offset << ", (%ebp)" <<std::endl;  
    	std::cout << "  push " << currentClassInfo.members[node->identifier_2->name].offset << "(%ebx)" <<std::endl;
    	} 
    	
    else {
    	std::cout << " mov 8(%ebp), (%ebx)" << std::endl;
    	std::cout << "push "<< currentClassInfo.members[node->identifier_1->name].offset << "(%ebx)" << std::endl;
    	std::cout << "  push " << currentClassInfo.members[node->identifier_2->name].offset  << "(%ebx)" << std::endl;
    	
    	}*/
    	
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    // WRITEME: Replace with code if necessary
    
    // LOCAL OFFSETS
    node->visit_children(this);
    std::cout << "  push " << currentMethodInfo.variables[node->identifier->name].offset << "(%ebp)" <<std::endl; 
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "  push $" << node->integer->value << std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "push $" << node->integer->value << std::endl;
}

void CodeGenerator::visitNewNode(NewNode* node) {
    node->visit_children(this);
    std::cout << "  push $" << currentMethodInfo.localsSize << std::endl; 
    std::cout << "  call malloc" << std::endl; 
    std::cout << "  add $4, %esp" << std::endl; 
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
}
