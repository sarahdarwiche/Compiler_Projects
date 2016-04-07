%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #define YYDEBUG 1

    int yylex(void);
    void yyerror(const char *);
%}

%error-verbose

/* WRITEME: List all your tokens here */
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

/* WRITEME: Specify precedence here */
%%

/* WRITEME: This rule is a placeholder, since Bison requires
            at least one rule to run successfully. Replace
            this with your appropriate start rules. */
Start : Class Start
	  | Class
	  ;
	   	

		  

/* WRITME: Write your Bison grammar specification here */


Class	: T_NAME T_COLON T_NAME T_OPEN_BRACE Members Methods T_CLOSE_BRACE
		| T_NAME T_OPEN_BRACE Members Methods T_CLOSE_BRACE
		;

Members : Members Type T_NAME 
		| 
		;

Methods : T_NAME T_OPEN_PAR Arguments T_CLOSED_PAR T_COLON Type T_OPEN_BRACE Body T_CLOSE_BRACE Methods
		|
		;
		
Arguments : Type T_NAME T_COMMA Arguments_2
		  | Type T_NAME
		  |
		  ;
		  
Arguments_2 : Type T_NAME T_COMMA Arguments_2
		  | Type T_NAME
		  ;
		  
Body : Declarations Statements Return
	 ;
	 
Declarations : Declarations Declaration
			 |
			 ;
			 
Declaration : Type T_NAME Declaration_2
			 ;
			 
Declaration_2 : T_COMMA T_NAME Declaration_2
			  |
			  ;
			 
Return : T_RETURN Expression
		|
		;
		
Statements : Assignment Statements
		   | MethodCall Statements
		   | IfElse Statements
		   | ForLoop Statements
		   | Print Statements
		   |
		   ;
		   
Statements_2 : Assignment Statements
		   | MethodCall Statements
		   | IfElse Statements
		   | ForLoop Statements
		   | Print Statements
		   ;
		   
Assignment : T_NAME T_EQUAL Expression
			;
			
MethodCall : T_NAME T_OPEN_PAR Parameters T_CLOSED_PAR
			| T_NAME T_PERIOD T_NAME T_OPEN_PAR Parameters T_CLOSED_PAR
			;
			
IfElse : T_IF Expression T_OPEN_BRACE Statements_2 T_CLOSE_BRACE
       | T_IF Expression T_OPEN_BRACE Statements_2 T_CLOSE_BRACE T_ELSE T_OPEN_BRACE Statements_2 T_CLOSE_BRACE
       ;
       
ForLoop : T_FOR Assignment T_SEMICOLON Expression T_SEMICOLON Assignment T_OPEN_BRACE Statements T_CLOSE_BRACE
		;
		
Print : T_PRINT Expression
	  ;
	  
Expression : Expression T_PLUS Expression
			|	Expression T_MINUS Expression
			|	Expression T_MULTIPLY Expression
			|	Expression T_DIVIDE Expression
			|	Expression T_LESS Expression
			|	Expression T_LESS_EQUAL Expression
			|	Expression T_EQUIVALENT Expression
			|	Expression T_AND Expression
			|	Expression T_OR Expression
			|	T_NOT Expression
			|	T_MINUS Expression %prec T_NOT
			|	T_NAME
			|	T_NAME T_PERIOD T_NAME
			|	MethodCall
			|	T_OPEN_PAR Expression T_CLOSED_PAR
			|	T_INTEGER
			|	T_TRUE
			|	T_FALSE
			|	T_NEW T_NAME
			|	T_NEW T_NAME T_OPEN_PAR Parameters T_CLOSED_PAR
			;	
			
Parameters : Parameters_2
			| 
			;
			
Parameters_2 : Parameters_2 T_COMMA Expression
			| Expression
			;
			
Type : T_INT
	 | T_BOOL
	 | T_NAME
	 | T_NONE
	 ;			

%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(0);
}
