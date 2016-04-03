#ifndef TABLE_SYMBOLE
#define TABLE_SYMBOLES

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Variable Variable;
struct Variable {
	char * nom;
	//enum type type;
	int init; 
	int portee;
	int adr_memoire;
	int constant; //si constante = 1 c'est une constante, on ne modifie pas la valeur 
};

typedef struct Element Element;
struct Element
{
	Variable var;
	Element *suivant ;
};

typedef struct Liste Liste;
struct Liste
{
	Element *premier;
	Element *dernier;
	int nb_element;
};

void init_liste_var_temp();
void init_liste_var(); 
void insertion(Variable nvVar, int var_temp);
void insertion_v(char *id, int portee, int constant);
int insertion_v_tmp();
int get_address(char *nom, int portee);
void suppr_tmp_var();
void suppression_var(int supPortee);
int est_constante(char *nom, int portee);
int est_init(char *nom, int portee);
void affichage_liste_var();
void init_var(char *nom, int portee);
void affichage_liste_var_temp();
#endif
