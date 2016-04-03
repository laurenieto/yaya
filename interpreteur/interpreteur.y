%{
	#include <stdio.h>
	#include <stdlib.h>

	int yyeror();

%}
%union {int nb;}

%token  <nb> tNB
        tADD tMUL tSOU tDIV
        tAFC tCOP tCOPB tCOPA
        tEQU tSUP tINF tAND tOR
        tJMF tJMP tERROR

%start Instruction

%%
Instruction : Add Instruction | Mul Instruction | Sou Instruction | Div Instruction | 		      Inf Instruction | Sup Instruction | And Instruction | Or Instruction | 
	      Equ Instruction | Afc Instruction | Cop Instruction | Jmf Instruction | 
	      Jmp Instruction |;

Add : tADD tNB tNB tNB;

Mul : tMUL tNB tNB tNB;

Sou : tSOU tNB tNB tNB;

Div : tDIV tNB tNB tNB;

Inf : tINF tNB tNB tNB;

Sup : tSUP tNB tNB tNB;

And : tAND tNB tNB tNB;

Or : tOR tNB tNB tNB;

Equ : tEQU tNB tNB tNB;

Afc : tAFC tNB tNB ;

Cop : tCOP tNB tNB;

Jmf : tJMF tNB tNB;

Jmp : tJMP tNB;

%%

int yyerror(char *s) {
  printf("erreur yacc : %s\n",s);
	return 1;
}

int main(void){
	yyparse();
	return 0;
}


