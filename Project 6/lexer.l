%option yylineno
%pointer

%{
    #include <stdlib.h>
    #include <errno.h>
    #include <limits.h>
    #include "ast.hpp"
    #include "parser.hpp"
    void yyerror(const char *);
%}

/* WRITEME: Copy any definitions and start conditions from Project 3 here */
%x comment

%%
"/*" {BEGIN(comment);}
<comment>. ;
<comment>\n ;
<comment><<EOF>> {yyerror("dangling comment");}
<comment>"*/" {BEGIN(INITIAL);}


  /* WRITEME: Copy your Flex rules from Project 3 here */

[ \t\n]						; /* skip whitespace */ 
(?-i:or)		  			{return T_OR;}
(?-i:and)		 		    {return T_AND;}
"<"				  			{return T_LESS;}  
"<="				 		{return T_LESS_EQUAL;}
"=="				 		{return T_EQUIVALENT;}
"+"				  			{return T_PLUS;}
"-"				  			{return T_MINUS;}
"*"						    {return T_MULTIPLY;}
"/"				  			{return T_DIVIDE;}
"not"				    	{return T_NOT;} 
")"						    {return T_CLOSED_PAR;}
"("					        {return T_OPEN_PAR;}
[0-9]+                      {yylval.base_int= atoi(yytext); return T_INTEGER;}
(?-i:true)				    {return T_TRUE;}
(?-i:false)				    {return T_FALSE;}
";"						    {return T_SEMICOLON;}
"."							{return T_PERIOD;}
","							{return T_COMMA;}
(?-i:print)					{return T_PRINT;}
(?-i:return)				{return T_RETURN;}
(?-i:if)				    {return T_IF;}
(?-i:else)					{return T_ELSE;}
(?-i:for)				    {return T_FOR;}
(?-i:int)				    {return T_INT;}
(?-i:bool)					{return T_BOOL;}
(?-i:none)					{return T_NONE;}
(?-i:new)				    {return T_NEW;}
"{"						    {return T_OPEN_BRACE;}
"}"						    {return T_CLOSE_BRACE;}
":"						    {return T_COLON;}
"="					        {return T_EQUAL;}
[a-zA-Z][a-zA-Z0-9]*		{yylval.base_char_ptr = strdup(yytext); return T_NAME;}
.               		    { yyerror("invalid character"); }   


%%

int yywrap(void) {
  return 1;
}
