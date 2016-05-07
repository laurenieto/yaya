%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "interpreteur.h"
%}

BLANCS [ \t]+
NB [0-9]+

%% 

{BLANCS} {/*on ignore*/}
(-?){NB} { yylval.nb=atoi(yytext); 
	   return tNB;
	 }
"ADD" {return tADD;}
"MUL" {return tMUL;}
"SOU" {return tSOU;}
"DIV" {return tDIV;}
"INF" {return tINF;}
"SUP" {return tSUP;}
"AND" {return tAND;}
"OR" {return tOR;}
"EQU" {return tEQU;}
"AFC" {return tAFC;}
"COP" {return tCOP;}
"JMF" {return tJMF;}
"JMP" {return tJMP;}
"PRI" {return tPRI;}
"main" {return tMAIN;}

.  {printf("tERROR token non reconnu\n");
   return tERROR; }

