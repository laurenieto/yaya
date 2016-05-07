#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gestion_fonction.h"

Liste_fun *liste_fun = NULL;

void init_liste_fun(){
	liste_fun = malloc(sizeof(Liste_fun));
	memset(liste_fun, 0, sizeof(Liste_fun));
	liste_fun->premier = NULL;
}

void insertion_fun(char *id, int addr){
	Variable_fun var;
	var.nom = id;
	var.adr_instr = addr;

	/* Création du nouvel élément */
	Element_fun *nouveau = malloc(sizeof(*nouveau));
	nouveau->var = var;

	/* Insertion de l'élément*/
	Element_fun *aux = liste_fun->premier;
	if(aux==NULL){
		liste_fun->premier = nouveau;
		liste_fun->dernier = nouveau;
		nouveau->var.adr_instr = addr;
		liste_fun->nb_element = 1;
	}
	else{
		/* Verification que la fonction n'est pas deja declarée */
		Element_fun *temp = liste_fun->premier;
		while(temp != NULL){
			if(strcmp(temp->var.nom,var.nom)==0){
				fprintf(stderr, "ERROR : insertion_fun, fonction deja déclaré\n");
			    exit(-1);
			}
			temp = temp->suivant;
		}
		liste_fun->dernier->suivant = nouveau;
		liste_fun->dernier = nouveau;
		nouveau->var.adr_instr = addr;
		liste_fun->nb_element++;
	}
	nouveau->suivant = NULL;
}



int get_addr_fun(char *nom){
	Element_fun *temp = liste_fun->premier;
	int flag = 1;
	int addr;
	while(temp != NULL && flag){
		if(strcmp(temp->var.nom,nom)==0){
			addr = temp->var.adr_instr;
			flag = 0;
		}
		temp = temp->suivant;
	}
	if(flag){
		fprintf(stderr, "ERROR : get_addr_fun, fonction n'existe pas\n");
	    exit(-1);	
	}

	return addr;
}

int get_addr_return(char *nom){
	Element_fun *temp = liste_fun->premier;
	int flag = 1;
	int addr;
	while(temp != NULL && flag){
		if(strcmp(temp->var.nom,nom)==0){
			addr = temp->var.adr_retour;
			flag = 0;
		}
		temp = temp->suivant;
	}
	if(flag){
		fprintf(stderr, "ERROR : get_addr_fun, la fonction n'existe pas\n");
	    exit(-1);	
	}

	return addr;
}

void set_addr_return(char *nom, int adr){
	Element_fun *temp = liste_fun->premier;
	int flag = 1;
	int addr;
	while(temp != NULL && flag){
		if(strcmp(temp->var.nom,nom)==0){
			temp->var.adr_retour = adr;
			flag = 0;
		}
		temp = temp->suivant;
	}
	if(flag){
		fprintf(stderr, "ERROR : get_addr_fun, fonction n'existe pas\n");
	    exit(-1);	
	}
}

void affichage_liste_fun(){
	Element_fun *aux = liste_fun->premier;
	while(aux != NULL){
		printf("nom : %s, addr : %d\n",aux->var.nom, aux->var.adr_instr);
		aux = aux->suivant;
	}
}
/*
int main(){
 return 0;
}//*/
