%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include "ast.hpp"
    
    #define YYDEBUG 1
    int yylex(void);
    void yyerror(const char *);
    
    extern ASTNode* astRoot;
%}

%error-verbose

/* WRITEME: Copy your token and precedence specifiers from Project 3 here */
%left T_OR
%left T_AND
%left T_LESS T_LESS_EQUAL T_EQUIVALENT
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE
%right T_NOT 
%token T_CLOSED_PAR
%token T_OPEN_PAR
%token T_INTEGER
%token T_TRUE
%token T_FALSE
%token T_SEMICOLON
%token T_PRINT
%token T_RETURN
%token T_IF
%token T_ELSE
%token T_FOR
%token T_NEW
%token T_INT
%token T_BOOL
%token T_NONE
%token T_OPEN_BRACE
%token T_CLOSE_BRACE
%token T_COLON
%token T_EQUAL
%token T_NAME
%token T_PERIOD
%token T_COMMA


/* WRITEME: Specify types for all nonterminals and necessary terminals here */
%type <declaration_list_ptr> Members Declarations 
%type <declaration_ptr> Declaration 
%type <identifier_list_ptr> Declaration_2
%type <class_list_ptr> Start RealStart
%type <class_ptr> Class
%type <method_list_ptr> Methods
%type <parameter_list_ptr> Arguments Arguments_2
%type <methodbody_ptr> Body
%type <statement_list_ptr> Statements Statements_2 
%type <assignment_ptr> Assignment
%type <methodcall_ptr> MethodCall
%type <ifelse_ptr> IfElse
%type <for_ptr> ForLoop
%type <print_ptr> Print
%type <expression_ptr> Expression
%type <expression_list_ptr> Parameters Parameters_2
%type <type_ptr> Type
%type <returnstatement_ptr> Return
%type <base_char_ptr> T_NAME
%type <base_int> T_INTEGER

%%

/* WRITEME: This rule is a placeholder. Replace it with your grammar
            rules from Project 3 */

RealStart : Start {astRoot = new ProgramNode ($1);}
	       ;     

Start : Class Start {$$ = $2; $$->push_front($1);}
	  | Class { $$ = new std::list<ClassNode*>(); $$->push_front($1); }
	  ;
	 
Class	: T_NAME T_COLON T_NAME T_OPEN_BRACE Members Methods T_CLOSE_BRACE { $$ = new ClassNode(new IdentifierNode($1), new IdentifierNode($3), $5, $6);}
		| T_NAME T_OPEN_BRACE Members Methods T_CLOSE_BRACE { $$ = new ClassNode(new IdentifierNode($1), NULL, $3, $4);}
		;

Members : Members Type T_NAME  {$$ = $1; std::list<IdentifierNode*>* list = new std::list<IdentifierNode*>(); list->push_back(new IdentifierNode($3)); $$->push_back(new DeclarationNode($2, list)); } 
		|  {$$ = new std::list<DeclarationNode*>(); } 
		;

Methods : T_NAME T_OPEN_PAR Arguments T_CLOSED_PAR T_COLON Type T_OPEN_BRACE Body T_CLOSE_BRACE Methods { $$ = $10; $$->push_front(new MethodNode(new IdentifierNode($1), $3, $6, $8));}
		| {$$ = new std::list<MethodNode*>();} 
		;
		
Arguments : Type T_NAME T_COMMA Arguments_2 {$$ = $4; $$->push_front(new ParameterNode($1, new IdentifierNode($2))); } 
		  | Type T_NAME {$$ = new std::list<ParameterNode*>(); $$->push_front(new ParameterNode($1, new IdentifierNode($2)));} 
		  |{$$ = new std::list<ParameterNode*>();}
		  ;
		  
Arguments_2 : Type T_NAME T_COMMA Arguments_2 {$$ = $4; $$->push_front(new ParameterNode($1, new IdentifierNode($2)));}
		  | Type T_NAME {$$ = new std::list<ParameterNode*>(); $$->push_front(new ParameterNode($1, new IdentifierNode($2)));}
		  ;
		  
Body : Declarations Statements Return {$$ = new MethodBodyNode($1, $2, $3);}
	 ;
	 
Declarations : Declarations Declaration {$$ = $1; $$->push_back($2);}
			 | {$$ = new std::list<DeclarationNode*>();}
			 ;
			 
Declaration : Type T_NAME Declaration_2 { $3->push_front(new IdentifierNode($2)); $$ = new DeclarationNode($1, $3);} 
			 ;
			 
Declaration_2 : T_COMMA T_NAME Declaration_2 {$$ = $3; $$->push_front(new IdentifierNode($2));}
			  | {$$ = new std::list<IdentifierNode*>(); }
			  ;
			 
Return : T_RETURN Expression {$$ = new ReturnStatementNode($2);}
		| {$$ = NULL;}
		;
		
Statements : Assignment Statements {$$ = $2; $$->push_front($1);}
		   | MethodCall Statements {$$ = $2; $$->push_front(new CallNode($1));}
		   | IfElse Statements {$$ = $2; $$->push_front($1);}
		   | ForLoop Statements {$$ = $2; $$->push_front($1);}
		   | Print Statements {$$ = $2; $$->push_front($1);}
		   | {$$ = new std::list<StatementNode*> ();}
		   ;
		   
Statements_2 : Assignment Statements {$$ = $2; $$->push_front($1);}
		   | MethodCall Statements {$$ = $2; $$->push_front(new CallNode($1));}
		   | IfElse Statements {$$ = $2; $$->push_front($1);}
		   | ForLoop Statements {$$ = $2; $$->push_front($1);}
		   | Print Statements {$$ = $2; $$->push_front($1);}
		   ;
		   
Assignment : T_NAME T_EQUAL Expression {$$ = new AssignmentNode(new IdentifierNode($1), $3);}
			;
			
MethodCall : T_NAME T_OPEN_PAR Parameters T_CLOSED_PAR { $$ = new MethodCallNode((new IdentifierNode($1)), NULL, $3); }
			| T_NAME T_PERIOD T_NAME T_OPEN_PAR Parameters T_CLOSED_PAR { $$ = new MethodCallNode(new IdentifierNode($1), new IdentifierNode($3), $5); }
			;
			
IfElse : T_IF Expression T_OPEN_BRACE Statements_2 T_CLOSE_BRACE { $$ = new IfElseNode($2, $4, NULL); } 
       | T_IF Expression T_OPEN_BRACE Statements_2 T_CLOSE_BRACE T_ELSE T_OPEN_BRACE Statements_2 T_CLOSE_BRACE { $$ = new IfElseNode($2, $4, $8); }
       ;
       
ForLoop : T_FOR Assignment T_SEMICOLON Expression T_SEMICOLON Assignment T_OPEN_BRACE Statements T_CLOSE_BRACE {$$ = new ForNode($2, $4, $6, $8); }
		;
		
Print : T_PRINT Expression { $$ = new PrintNode($2); }
	  ;
	  
Expression : Expression T_PLUS Expression { $$ = new PlusNode($1, $3); }
			|	Expression T_MINUS Expression { $$ = new MinusNode($1, $3); }
			|	Expression T_MULTIPLY Expression { $$ = new TimesNode($1, $3); }
			|	Expression T_DIVIDE Expression { $$ = new DivideNode($1, $3); }
			|	Expression T_LESS Expression { $$ = new LessNode($1, $3); }
			|	Expression T_LESS_EQUAL Expression { $$ = new LessEqualNode($1, $3); }
			|	Expression T_EQUIVALENT Expression { $$ = new EqualNode($1, $3); }
			|	Expression T_AND Expression { $$ = new AndNode($1, $3); }
			|	Expression T_OR Expression { $$ = new OrNode($1, $3); }
			|	T_NOT Expression { $$ = new NotNode($2); }
			|	T_MINUS Expression %prec T_NOT { $$ = new NegationNode($2); }
			|	T_NAME { $$ = new VariableNode(new IdentifierNode($1)); }
			|	T_NAME T_PERIOD T_NAME { $$ = new MemberAccessNode(new IdentifierNode($1), new IdentifierNode($3)); }
			|	MethodCall { $$ = $1; }
			|	T_OPEN_PAR Expression T_CLOSED_PAR { $$ = $2; }
			|	T_INTEGER  { $$ = new IntegerLiteralNode(new IntegerNode($1)); }
			|	T_TRUE { $$ = new BooleanLiteralNode(new IntegerNode(1)); }
			|	T_FALSE { $$ = new BooleanLiteralNode(new IntegerNode(0)); }
			|	T_NEW T_NAME { $$ = new NewNode(new IdentifierNode($2), new std::list<ExpressionNode*>()); }
			|	T_NEW T_NAME T_OPEN_PAR Parameters T_CLOSED_PAR { $$ = new NewNode(new IdentifierNode($2), $4); } 
			;	
			
Parameters : Parameters_2 {$$ = $1;}
			|  { $$ = new std::list<ExpressionNode*> (); }
			;
			
Parameters_2 : Parameters_2 T_COMMA Expression { $$ = $1; $$->push_back($3); }
			| Expression { $$ = new std::list<ExpressionNode*> ();
			               $$->push_back($1); }
			;
			
Type : T_INT { $$ = new IntegerTypeNode();  }
	 | T_BOOL { $$ = new BooleanTypeNode(); }
	 | T_NAME { $$ = new ObjectTypeNode(new IdentifierNode($1)); }
	 | T_NONE { $$ = new NoneNode(); } 
	 ;			


%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(0);
}
