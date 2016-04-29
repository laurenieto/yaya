%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "table_symbole.h"

	int yerror();

	int ins[255][4];
	int ins_id = 0;

	int profondeur;

/*ce tableau permet de réaliser la table des labels,
	- c : code de l'instruction assembleur
	- p1,p2,p3 : paramètres de l'instruction
	- on se sert des $x comme des variables temporaires afin de récupérer des valeurs
	- cela permet de mettre à jour les paramètres et de n'afficher les instructions qu'une fois que nous avons ttes les @ */

	void add_ins(int c, int p1, int p2, int p3) {
		ins[ins_id][0] = c;
		ins[ins_id][1] = p1;
		ins[ins_id][2] = p2;
		ins[ins_id][3] = p3;
		ins_id++;
	}
%}

%union {int nb; char * str;}

%type <nb> Expr
%type <nb> Affectation
%type <nb> Condition
%type <nb> suiteDecl

%token tPRINTF tMAIN tCST tINT tRET <str> tID <nb> tNB tPV tV tPO tPF tAO tAF tTEXT tG
%token tOU tET
%token tEG tPLUSPLUS tMOINSMOINS
%token <nb> tWHILE <nb> tIF tELSIF tELSE
%token tERROR

%left  tNOT tAND tOR tINFEG tSUPEG tINF tSUP tEGEG tNOTEG
%left  tPLUS tMOINS
%left  tFOIS tDIV

%start Input

%%
Input : Fonction Input
		|;

Fonction: tINT tID tPO {profondeur ++;} Params tPF Body
		|tINT  tMAIN tPO {profondeur ++;} Params tPF Body;

Appel_fn : tID tPO Params tPF tPV;

Params : 	tINT tID SuiteParams {insertion_v($2,profondeur,0);}
			|;

SuiteParams : 	tV tINT tID SuiteParams {insertion_v($3,profondeur,0);}
				|;

Body : tAO Instrs tAF {	suppression_var(profondeur);
						profondeur --;};

Instrs : 	BlocAff Instrs
			|BlocDecl  Instrs
			|BlocPrintf Instrs
			|BlocIf Instrs
			|BlocWhile Instrs
			|Appel_fn Instrs
			|tRET Expr tPV
			|;

/*une constante ne peux être affectée que lors de sa déclaration*/
//affectation retourne l'adresse de la variable , on ne peut pas affecter plsuieurs valeurs à la fois
BlocAff : tID Affectation tPV {
								if(est_constante($1,profondeur)){
									fprintf(stderr, "ERROR : On ne peux pas affecter une constante\n");
									exit(-1);
								}
								int m = get_address($1,profondeur);
								add_ins(0x5, m, $2, -1);
								init_var($1, profondeur);							
							};


Affectation : tEG Expr { $$ = $2;};

// 1 -> cste , 0 non
BlocDecl : 	tINT tID suiteDecl tPV { 	insertion_v($2,profondeur,0);
										if($3!=-1){
											int m = get_address($2,profondeur);
											add_ins(0x5, m, $3, -1);
											init_var($2, profondeur);
										}
									}
			|tCST tINT tID suiteDecl tPV { insertion_v($3,profondeur,1); };

suiteDecl :	Affectation{$$=$1;}
			|tV tID suiteDecl { insertion_v($2,profondeur,0); $$=-1;}
			|{$$=-1;};


Condition : Condition tAND Condition
			| Condition tOR Condition {add_ins(0xD,$1,$1,$3); $$=$1;}
			| Condition tINF Condition {add_ins(0x9,$1,$1,$3); $$=$1;}
			| Condition tSUP Condition {add_ins(0xA,$1,$1,$3); $$=$1;}
			| Condition tINFEG Condition {	int n = insertion_v_tmp(); add_ins(0x9,n,$1,$3);
											int m = insertion_v_tmp(); add_ins(0xB,m,$1,$3);
											add_ins(0xD,$1,n,m); $$=$1;}
			| Condition tSUPEG Condition {	int n = insertion_v_tmp(); add_ins(0xA,n,$1,$3);
											int m = insertion_v_tmp(); add_ins(0xB,m,$1,$3);
											add_ins(0xD,$1,n,m); $$=$1;}
			| Condition tEGEG Condition {add_ins(0xB,$1,$1,$3); $$=$1;}
			| Condition tNOTEG Condition {add_ins(0xB,$1,$1,$3); $$=$1;}
//			| tNOT Condition
			| Expr {$$=$1;};

BlocIf : 	tIF tPO Condition { add_ins(0x8, $3, -1, -1); $1 = ins_id - 1;}
	 		tPF {profondeur ++;} Body { ins[$1][2] = ins_id;	} BlocElsif;


BlocElsif : tELSIF tPO Condition {add_ins(0x8, $3, -1, -1); $1 = ins_id - 1;}
	 		tPF {profondeur ++;} Body { ins[$1][2] = ins_id;	} SuiteElsif
			| BlocElse;


SuiteElsif : tELSIF tPO Condition {add_ins(0x8, $3, -1, -1); $1 = ins_id - 1;}
				 		tPF {profondeur ++;} Body { ins[$1][2] = ins_id;	} BlocElse
			|BlocElse;


BlocElse : tELSE {profondeur ++;} Body  {ins[$1][2] = ins_id;}
				|;

BlocWhile : tWHILE tPO Condition { add_ins(0x8, $3, -1 , -1); $1 = ins_id - 1; }
			tPF {profondeur ++;} Body { add_ins(0x7,$1,-1,-1); //une fois la condition réalisée on jump au debut du while
										ins[$1][2] = ins_id; // On modifie le num de l'instruction ou faire le saut si la condition est fausse
									  };



BlocPrintf : tPRINTF tPO Expr { add_ins(0xc,$3,-1,-1); } tPF tPV;


//$$ valeur retournée
Expr: 	tNB { 	int n = insertion_v_tmp();
		 		add_ins(0x6, n , $1, -1);
				$$ = n;
			 }

		| tID { int n = insertion_v_tmp(); //insertion retourne l'adresse de la v temporaire
				int m = get_address($1,profondeur);
				if(est_init($1,profondeur)){
					add_ins(0x5, n , m, -1);
		 			$$ = n;
				}
				else{
					fprintf(stderr, "ERROR : variable n'est pas declaree\n");
				    exit(-1);
				}
			  }

		| Expr tPLUS Expr {	add_ins(0x1, $1, $1, $3);
							$$ = $1;
					 	  }
		|Expr tMOINS Expr {	add_ins(0x3, $1, $1, $3);
							$$ = $1;
						  }
		|Expr tFOIS Expr {	add_ins(0x2, $1, $1, $3);
							$$ = $1;
						 }
		|Expr tDIV Expr {	add_ins(0x4, $1, $1, $3);
							$$ = $1;
						}
		|tPO Expr tPF {$$ = $2;} ;

%%

int yyerror(char *s) {
  printf("erreur yacc : %s\n",s);
}

int main(void) {
	int i;
	init_liste_var_temp();
	init_liste_var();

	yyparse();

	char * str;
	str = (char *) malloc( ins_id*512*sizeof(char) );
	char itos[15];

	for (i=0; i<ins_id; i++){
		switch(ins[i][0]){
		case 1 :
			strcat(str,"ADD ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][2]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][3]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		case 2 :
			strcat(str,"MUL ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][2]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][3]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		case 3 :
			strcat(str,"SOU ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][2]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][3]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		case 4 :
			strcat(str,"DIV ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][2]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][3]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		case 5 :
			strcat(str,"COP ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][2]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		case 6 :
			strcat(str,"AFC ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][2]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		case 7 :
			strcat(str,"JMP ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		case 8 :
			strcat(str,"JMF ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][2]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		case 9 :
			strcat(str,"INF ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][2]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][3]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		case 10 :
			strcat(str,"SUP ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][2]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][3]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		case 11 :
			strcat(str,"EQU ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][2]);
			strcat(str,itos);
			strcat(str," ");
			sprintf(itos, "%d", ins[i][3]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		case 12 :
			strcat(str,"PRI ");
			sprintf(itos, "%d", ins[i][1]);
			strcat(str,itos);
			strcat(str,"\n");
			break;
		default :
			fprintf(stderr, "ERROR : code assembleur inconnu\n");
	   		exit(-1);
		}
	}

    FILE* fichier = NULL;
    fichier = fopen("assembleur.txt", "w");

    if (fichier != NULL)
    {
        fprintf(fichier, "%s", str);
        fclose(fichier);
    }
	else{
		fprintf(stderr, "ERROR : fichier n'existe pas\n");
	    exit(-1);
	}

	return 0;
}
