%option yylineno
%pointer

%{
    #define YYSTYPE char*
    #include <stdlib.h>
    void yyerror(const char *);
    #include "parser.hpp"
    
%}

/* WRITEME: Write any definitions here. You can find information on
            definitions here:
            http://flex.sourceforge.net/manual/Definitions-Section.html */
     

/* WRITEME: If you are going to use start conditions, write them here.
            You can find more information on start conditions here:
            http://flex.sourceforge.net/manual/Start-Conditions.html
            You will probably want to use exclusive conditions rather
            than inclusive conditions (use the %x instead of the %s). */

%x comment



  /* WRITEME: Write your Flex token rules here */

%% 

"/*" {BEGIN(comment);}
<comment>. ;
<comment>\n ;
<comment><<EOF>> {yyerror("dangling comment");}
<comment>"*/" {BEGIN(INITIAL);}


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
[0-9]+                      {return T_INTEGER;}
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
[a-zA-Z][a-zA-Z0-9]*		{return T_NAME;}
.               		    { yyerror("invalid character"); } 
%%

int yywrap(void) {
  return 1;
}
