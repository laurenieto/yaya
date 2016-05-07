#include "memoire.h"

int memory [TAILLEMAX];
int op_tab [TAILLEMAX][4];
int i_inst = 0, i_op = 0;

void addition(int add, int a, int b){
	memory[add] = memory[a] + memory[b];
}

void multiplication(int add, int a, int b){
	memory[add] = memory[a] * memory[b];
}

void soustraction(int add, int a, int b){
	memory[add] = memory[a] - memory[b];
}

void division(int add, int a, int b){
	memory[add] = memory[a] / memory[b];
}

void inferieur(int add, int a, int b){
	if(memory[a]<memory[b]){
		memory[add] = 1;
	}
	else{
		memory[add] = 0;
	}
}

void superieur(int add, int a, int b){
	if(memory[a] > memory[b]){
		memory[add] = 1;
	}
	else{
		memory[add] = 0;
	}
}

void et(int add, int a, int b){
	if(memory[a] && memory[b]){
		memory[add] = 1;
	}
	else{
		memory[add] = 0;
	}
}

void ou(int add, int a, int b){
	if(memory[a]||memory[b]){
		memory[add] = 1;
	}
	else{
		memory[add] = 0;
	}
}

void egal(int add, int a, int b){
	if(memory[a]==memory[b]){
		memory[add] = 1;
	}
	else{
		memory[add] = 0;
	}
}

void affectation(int add, int a){
	memory[add] = a;
}

void copie(int a, int b){
	memory[a] = memory[b];
}

void jmf(int a, int b){
	if(memory[a]!=1){
		i_inst = b-1;
	}
}

void jump(int a){
	i_inst = a-1;
}

void add(op operateur, int adresse, int val1, int val2){
	op_tab[i_op][0] = operateur;
	op_tab[i_op][1] = adresse;
	op_tab[i_op][2] = val1;
	op_tab[i_op][3] = val2;
	i_op++;
}


void operation(){
	//numéro de l'instruction qui contient le main pour qu'on puisse commencer par la
	int inst_main = 0;
	for(i_inst = inst_main; i_inst<i_op; i_inst++){
		printf("\n%d -> %d, %d, %d, %d\n", i_inst, op_tab[i_inst][0], op_tab[i_inst][1], op_tab[i_inst][2], op_tab[i_inst][3]);
		switch (op_tab[i_inst][0]) {
		case ADD :
			printf("ADD\n");
			addition(op_tab[i_inst][1], op_tab[i_inst][2], op_tab[i_inst][3]);
		break;
		case MUL : 
			printf("MUL\n");
			multiplication(op_tab[i_inst][1], op_tab[i_inst][2], op_tab[i_inst][3]);
		break;
		case SOU : 
			printf("SOU\n");
			soustraction(op_tab[i_inst][1], op_tab[i_inst][2], op_tab[i_inst][3]);
		break; 
		case DIV :
			printf("DIV\n");
			division(op_tab[i_inst][1], op_tab[i_inst][2], op_tab[i_inst][3]);
		break;
		case INF : 
			printf("INF\n");
			inferieur(op_tab[i_inst][1], op_tab[i_inst][2], op_tab[i_inst][3]);
		break;
		case SUP :  
			printf("SUP\n");
			superieur(op_tab[i_inst][1], op_tab[i_inst][2], op_tab[i_inst][3]);
		break;
		case AND :
			printf("AND\n");
			et(op_tab[i_inst][1], op_tab[i_inst][2], op_tab[i_inst][3]);
		break;
		case OR :
			printf("OR\n");
			ou(op_tab[i_inst][1], op_tab[i_inst][2], op_tab[i_inst][3]);
		break;
		case EQU :
			printf("EQU\n");
			egal(op_tab[i_inst][1], op_tab[i_inst][2], op_tab[i_inst][3]);
		break;
		case AFC :
			printf("AFC\n");
			affectation(op_tab[i_inst][1], op_tab[i_inst][2]);
		break;
		case COP :
			printf("COP\n");
			copie(op_tab[i_inst][1], op_tab[i_inst][2]);
		break;
		case JMF :
			printf("JMF\n");
			jmf(op_tab[i_inst][1], op_tab[i_inst][2]);
		break;
		case JMP :
			printf("JMP\n");
			jump(op_tab[i_inst][1]);
		break;
		default :
			printf("pas add \n");
		}
		affiche_memo();
	}
}

void affiche_tab(){
	int i;

	printf("instr\n");
	for(i=0; i<15; i++){
		printf("%d -> %d, %d, %d, %d\n", i, op_tab[i][0], op_tab[i][1], op_tab[i][2], op_tab[i][3]);
	 }
}
void affiche_memo(){
	int i;
	printf("memoire : \n");
	for(i=0; i<10; i++){
		printf("%d -> %d\n",i, memory[i]);
	}
	
	printf("memoire temp : \n");
	for(i=1000; i<1010; i++){
		printf("%d -> %d\n",i, memory[i]);
	}
}
/*
int main (){
	return 0;	
}*/













