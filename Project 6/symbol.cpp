#include "symbol.hpp"

// Symbol Visitor Functions: These are the functions you will
// complete to build the symbol table. Not all functions must
// have code, many may be left empty.

void Symbol::visitProgramNode(ProgramNode* node) {
    // WRITEME: Replace with code if necessary
    classTable = new  ClassTable ; 
    node->visit_children(this);
}

void Symbol::visitClassNode(ClassNode* node) {
    // WRITEME: Replace with code if necessary
    ClassInfo class_info;
    ClassInfo superclass_info;
    currentMemberOffset = 0; 
   
       
    currentMethodTable = &(class_info.methods);
    currentVariableTable = &(class_info.members);
    
   
    node->visit_children(this);
  
   
    if(node->identifier_2) {
    	class_info.superClassName = node->identifier_2->name; 
    	//insert superclass
    	class_info.members.insert(superclass_info.members.begin(), superclass_info.members.end());
    }	
    else {
    	class_info.superClassName = "";
    }
 
    class_info.membersSize = (4 * node->declaration_list->size()); 
    classTable->insert(std::pair<std::string, ClassInfo> (node->identifier_1->name, class_info)); 
   
}

void Symbol::visitMethodNode(MethodNode* node) {
    // WRITEME: Replace with code if necessary
    //set method table
    

    currentLocalOffset = -4;
    currentParameterOffset = 8;
    
   VariableTable variableTable;
   currentVariableTable = &(variableTable);
   node->visit_children(this);
   
   CompoundType compound_type;
   //set node baseType in visitor
   compound_type.baseType =  node->basetype;
   if(compound_type.baseType == bt_object) {
    
   		compound_type.objectClassName = ((ObjectTypeNode *)(node->type))->identifier->name;
   	}
   
   
 
   MethodInfo method_info;
   method_info.returnType = compound_type;
   method_info.variables = variableTable;
   method_info.localsSize = ((-1) * currentLocalOffset-4);
   currentMethodTable->insert(std::pair<std::string, MethodInfo> (node->identifier->name, method_info)); 
    
 
}

void Symbol::visitMethodBodyNode(MethodBodyNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

void Symbol::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
    
    node->visit_children(this);
    
    VariableInfo variable_info;
    CompoundType compound_type;
    compound_type.baseType = node->basetype;
    if(compound_type.baseType == bt_object) {
    
   		compound_type.objectClassName = ((ObjectTypeNode *)(node->type))->identifier->name; 
   	}
   
    variable_info.type =  compound_type;
    variable_info.offset = currentParameterOffset; 
    currentParameterOffset = currentParameterOffset + 4;
    variable_info.size = 4; 
    currentVariableTable->insert (std::pair<std::string, VariableInfo>(node->identifier->name, variable_info));
}

void Symbol::visitDeclarationNode(DeclarationNode* node) {
    // WRITEME: Replace with code if necessary
    for(std::list<IdentifierNode*>::iterator iter = node->identifier_list->begin();
        iter != node->identifier_list->end(); iter++) { 
    	node->visit_children(this);
    
    	VariableInfo variable_info;
    	CompoundType compound_type;
   		 compound_type.baseType = node->basetype;
  		  if(compound_type.baseType == bt_object) {
    
   				compound_type.objectClassName = ((ObjectTypeNode *)(node->type))->identifier->name; 
   			}
   
    	variable_info.type =  compound_type;
    
   		 if (currentMemberOffset == 0){
    		variable_info.offset = currentLocalOffset;
    		currentLocalOffset = currentLocalOffset -4;
    		}
    	else {
    		variable_info.offset = currentMemberOffset;
    		currentMemberOffset = currentMemberOffset + 4;
    		}
    	
    	variable_info.size = 4; 
    	currentVariableTable->insert (std::pair<std::string, VariableInfo>((*iter)->name, variable_info)); 
    	}
    
    
}

void Symbol::visitReturnStatementNode(ReturnStatementNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitAssignmentNode(AssignmentNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIfElseNode(IfElseNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitPlusNode(PlusNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMinusNode(MinusNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitTimesNode(TimesNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitDivideNode(DivideNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitLessNode(LessNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitLessEqualNode(LessEqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitAndNode(AndNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitOrNode(OrNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNotNode(NotNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNegationNode(NegationNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMethodCallNode(MethodCallNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMemberAccessNode(MemberAccessNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitVariableNode(VariableNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNewNode(NewNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_integer;
}

void Symbol::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_boolean;
}

void Symbol::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_object;
    
}

void Symbol::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_none;
}

void Symbol::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
}
