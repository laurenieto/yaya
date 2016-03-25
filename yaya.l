%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "yaya.h"
%}

/*il faut gérer les "autres" token -> . = error */


BLANCS [ \t]+
NB [0-9]+
ID [a-z][_a-z0-9]*


%%

"main" return tMAIN;
"const" return tCST;
"printf" return tPRINTF;
{BLANCS} {/*on ignore*/}
"int" return tINT;
"return" return tRET;
"while" return tWHILE;
"if" return tIF;
{ID} return tID;
(-?){NB} {yylval.nb=atoi(yytext); 
					return tNB;
				 }

";" return tPV;
"," return tV;
"(" return tPO;
")" return tPF;
"{" return tAO;
"}" return tAF;

"<=" return tINFEG;
">=" return tSUPEG;
"<" return tINF;
">" return tSUP;
"==" return tEGEG;
"!=" return tNOTEG;

"||" return tOU;
"&&" return tET;
"!" return tNOT;

"=" return tEG;
"++" return tPLUSPLUS;
"--" return tMOINSMOINS;
"+" return tPLUS;
"-" return tMOINS;
"*" return tFOIS;
"/" return tDIV;



