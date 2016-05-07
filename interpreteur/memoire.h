#include <stdlib.h>
#include <stdio.h>

#define TAILLEMAX 10000

typedef enum {
	ADD, MUL, SOU, DIV, COP, AFC, JMP, JMF, INF, SUP, EQU, PRI, AND, OR
}op;

void add(op operateur, int adresse, int val1, int val2);
void affiche_tab();
void operation();
void affiche_memo();

void addition(int add, int a, int b);
void multiplication(int add, int a, int b);
void soustraction(int add, int a, int b);
void division(int add, int a, int b);
void inferieur(int add, int a, int b);
void superieur(int add, int a, int b);
void et(int add, int a, int b);
void ou(int add, int a, int b);
void egal(int add, int a, int b);
void affectation(int add, int a);
void copie(int a, int b);
void jmf(int a, int b);
void jump(int a);
