%{
	#include <stdio.h>
	#include <stdlib.h>

	#include "table_symbole.h"

	int profondeur;
%}

%union {int nb; char * str;}

%type <nb> Expr
%type <nb> Affectation


%token tPRINTF tMAIN tCST tINT tRET <str> tID <nb> tNB tPV tV tPO tPF tAO tAF tTEXT tG 
%token tOU tET 
%token tEG tPLUSPLUS tMOINSMOINS 
%token tWHILE tIF 

%left  tNOT tAND tOR tINFEG tSUPEG tINF tSUP tEGEG tNOTEG
%left  tPLUS tMOINS
%left  tFOIS tDIV



%start Input

%%
Input : Fonction Input 
		|;
		
Fonction: 	tINT tID tPO Params tPF Body
			|tINT tMAIN tPO Params tPF Body;

Params : 	tINT tID SuiteParams
			|;
		 
SuiteParams : 	tV tINT tID SuiteParams
				|;

Body : tAO Instrs tAF;

Instrs : 	BlocAff Instrs	
			|BlocDecl Instrs
			|BlocPrintf Instrs	
			|BlocIf Instrs
			|BlocWhile Instrs
			|tRET tNB	tPV
			|tRET tID tPV
			|;
			
/*une constante ne peux être affectée que lors de sa déclaration*/
//affectation retourne l'adresse de la variable , on ne peut pas affecter plsuieurs valeurs à la fois 
BlocAff : tID Affectation tPV { 	if(!(est_constante($1,profondeur)) ){
																		 printf("COP %d %d", atoi($1) , $2);
																		 suppr_tmp_var();
																  }
																  else {
																		printf(" WARNINGGGG on ne peux pas affecter une constante"); //sortie_erreur -> stderr
																  }
															};


Affectation : tEG Expr  { $$ = $2;}; //COP @affecté @temporaire++++++++++++

// 1 -> cste , 0 non 
BlocDecl : 	tINT tID suiteDecl tPV { insertion_v($2,profondeur,0); }
			|tCST tINT tID suiteDecl tPV { insertion_v($3,profondeur,1); };

suiteDecl : tV tID suiteDecl { insertion_v($2,profondeur,0); }
			| Affectation 
			| Affectation tV tID suiteDecl;

Condition : Condition tAND Condition
			| Condition tOR Condition
			| Condition tINF Condition
			| Condition tSUP Condition
			| Condition tINFEG Condition
			| Condition tSUPEG Condition
			| Condition tEGEG Condition
			| Condition tNOTEG Condition
			| tNOT Condition
			| Expr;

BlocIf : 	tIF tPO Condition tPF Body;

BlocWhile : tWHILE tPO Condition tPF Body;

  

BlocPrintf : tPRINTF tPO Expr tPF tPV;

//$$ valeur retournée
Expr : 	tID { int n = insertion_v_tmp(); //insertion retourne l'adresse de la v temporaire
							int m = get_address($1,profondeur);
					 		printf("COP %d %d ", n , m);
					 		$$ = m;
				 }
		|tNB { int n = insertion_v_tmp();
					 int m = $1;
					 printf("AFC %d %d ", n , $1);
					 $$ = m;
				 }

		| Expr tPLUS Expr {printf("ADD %d %d %d",  $1 , $1 , $3); 
											 suppr_tmp_var();
											 $$ = $1;
										 }
		|Expr tMOINS Expr { printf("SOU %d %d %d", $1 , $1 , $3);
											  suppr_tmp_var();
											  $$ = $1;
										 }
		|Expr tFOIS Expr	{ printf("MUL %d %d %d",  $1 , $1 , $3); 
						

						suppr_tmp_var();
											  $$ = $1;
										 }
		|Expr tDIV Expr { printf("DIV %d %d %d",  $1 , $1 , $3); 
											suppr_tmp_var();
											$$ = $1;
										 }
		|tPO Expr tPF {$$ = $2;} ;

%%

int yyerror(char *s) {
  printf("erreur yacc : %s\n",s);
}

int main(void) {
	Liste * liste;
	initialisation(liste);
  yyparse();
	return 0;
}


	

