%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "memoire.h"

	int yyeror();

	int val_main = 0;

%}
%union {int nb;}

%token  <nb> tNB
        tADD tMUL tSOU tDIV
        tAFC tCOP tCOPB tCOPA
        tEQU tSUP tINF tAND tOR
        tJMF tJMP tERROR tPRI tMAIN


%start Input

%%
Input : Main Instruction;

Instruction : 	Add Instruction | Mul Instruction | Sou Instruction | Div Instruction |
				Inf Instruction | Sup Instruction | And Instruction | Or Instruction |
		    	Equ Instruction | Afc Instruction | Copa Instruction | Copb Instruction | Cop Instruction | Jmf Instruction |
			    Jmp Instruction | Pri Instruction |;

Add : tADD tNB tNB tNB {op operateur = ADD; add(operateur,$2,$3,$4);};

Mul : tMUL tNB tNB tNB {op operateur = MUL; add(operateur,$2,$3,$4);};

Sou : tSOU tNB tNB tNB {op operateur = SOU; add(operateur,$2,$3,$4);};

Div : tDIV tNB tNB tNB {op operateur = DIV; add(operateur,$2,$3,$4);};

Inf : tINF tNB tNB tNB {op operateur = INF; add(operateur,$2,$3,$4);};

Sup : tSUP tNB tNB tNB {op operateur = SUP; add(operateur,$2,$3,$4);};

And : tAND tNB tNB tNB {op operateur = AND; add(operateur,$2,$3,$4);};

Or : tOR tNB tNB tNB {op operateur = OR; add(operateur,$2,$3,$4);};

Equ : tEQU tNB tNB tNB {op operateur = EQU; add(operateur,$2,$3,$4);};

Afc : tAFC tNB tNB {op operateur = AFC; add(operateur,$2,$3,0);};

Copa: tCOPA tNB tNB {op operateur = COPA; add(operateur, $2, $3, 0);};

Copb: tCOPB tNB tNB {op operateur = COPB; add(operateur, $2, $3, 0);};

Cop : tCOP tNB tNB {op operateur = COP; add(operateur,$2,$3,0);};

Jmf : tJMF tNB tNB {op operateur = JMF; add(operateur,$2,$3,0);};

Jmp : tJMP tNB {op operateur = JMP; add(operateur,$2,0,0);};

Pri : tPRI tNB {printf("d \n",$2);};

Main : tMAIN tNB {val_main = $2;};

%%

int yyerror(char *s) {
  printf("erreur yacc interpreteur : %s\n",s);
	return 1;
}

int main(void){
	yyparse();
	operation(val_main);
	affiche_tab();
	return 0;
}
