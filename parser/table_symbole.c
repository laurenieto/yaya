#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "table_symbole.h"


#define TAILLEMAX 1000
//enum type {INT, CONST};
Liste *liste_var = NULL;
Liste *liste_var_temp = NULL;

void init_liste_var_temp(){
	liste_var_temp = malloc(sizeof(Liste));
	memset(liste_var_temp, 0, sizeof(Liste));
	liste_var_temp->premier = NULL;
}

void init_liste_var(){
	liste_var = malloc(sizeof(Liste));
	memset(liste_var, 0, sizeof(Liste));
	liste_var->premier = NULL;
}

int insertion_v_tmp(){
	Variable var;
	var.nom = "tmp";
	var.init = 1;
	var.portee = -1;
	var.constant = 0;

	/* Création du nouvel élément */
	Element *nouveau = malloc(sizeof(*nouveau));
	nouveau->var = var;

	/* Insertion de l'élément */
	Element *aux = liste_var_temp->premier;
	if(aux==NULL){
		liste_var_temp->premier = nouveau;
		liste_var_temp->dernier = nouveau;
		nouveau->var.adr_memoire = TAILLEMAX;
		liste_var_temp->nb_element = 1;
	}
	else{
		int last_addr;
		last_addr = liste_var_temp->dernier->var.adr_memoire;
		liste_var_temp->dernier->suivant = nouveau;
		liste_var_temp->dernier = nouveau;
		nouveau->var.adr_memoire = (last_addr + 1);
		liste_var_temp->nb_element++;
	}
	nouveau->suivant = NULL;	
	return liste_var_temp->dernier->var.adr_memoire;
}

void insertion_v(char *id, int portee, int constant){ 
	Variable var;
	var.nom = id;
	var.init = 0;
	var.portee = portee;
	var.constant = constant;
	
	/* Création du nouvel élément */
	Element *nouveau = malloc(sizeof(*nouveau));
	nouveau->var = var;

	/* Insertion de l'élément*/
	Element *aux = liste_var->premier;
	if(aux==NULL){
		liste_var->premier = nouveau;
		liste_var->dernier = nouveau;
		nouveau->var.adr_memoire = 0;
		liste_var->nb_element = 1;
	}
	else{
		/* Verification que la variable n'est pas deja declarée */
		Element *temp = liste_var->premier;
		while(temp != NULL){ 
			if(strcmp(temp->var.nom,var.nom)==0 && temp->var.portee == var.portee){
				fprintf(stderr, "ERROR : insertion_v, variable deja dans la table\n");
			    exit(-1);
			}
			temp = temp->suivant;
		}		
		/* Verification qu'il reste de la place en memoire */
		if(liste_var->dernier->var.adr_memoire == TAILLEMAX+1){
			fprintf(stderr, "ERROR : insertion_v, plus de place en memoire\n");
		    exit(-1);
		}
		liste_var->dernier->suivant = nouveau;
		liste_var->dernier = nouveau;
		nouveau->var.adr_memoire = liste_var->nb_element;
		liste_var->nb_element++;
	}
	nouveau->suivant = NULL;	
}

/*
void suppression_tmp_var(){
	Element *aux = liste_var_temp->premier;
	while(aux != liste_var_temp->dernier && aux != NULL){
		aux = aux->suivant;
	}
	if(aux == NULL){
		fprintf(stderr, "ERROR : suppr_tmp_var, pas de variable temporaire\n");
		exit(-1);
	}
	aux->suivant = NULL;
}
*/

void suppression_var(int portee){
	Element *aux = liste_var->premier;
	if(liste_var->premier->var.portee == portee){
		liste_var->premier = NULL;
		liste_var->dernier = NULL;
	}
	else{
		while(aux->suivant!=NULL && aux->suivant->var.portee < portee){
			aux = aux->suivant;
		}
		aux->suivant = NULL;
		liste_var->dernier = aux;
		liste_var->nb_element = aux->var.adr_memoire+1;
	}
}

int get_address(char *nom, int portee){
	Element *temp = liste_var->premier;
	int flag = 0;
	int addr; 
	while(temp != NULL){ 
		if(strcmp(temp->var.nom,nom)==0 && temp->var.portee <= portee){
			addr = temp->var.adr_memoire;
			flag = 1;
		}
		temp = temp->suivant;
	}
	if(flag){
		return addr;
	}
	fprintf(stderr, "ERROR : get_addresse, variable n'est pas dans la table\n");
    exit(-1);
}

void init_var(char *nom, int portee){
	Element *temp = liste_var->premier;
	int count = 0;
	while(temp != NULL){ 
		if(strcmp(temp->var.nom,nom)==0 && temp->var.portee <= portee){
			count++;
		}
		temp = temp->suivant;
	}		
	if(count == 0){
		fprintf(stderr, "ERROR : init_var, variable n'est pas dans la table\n");
	    exit(-1);
	}
	else{
		//on parcours 2 fois la liste car on veut initialiser la derniere variable
		while(temp != NULL && count!=0){ 
			if(strcmp(temp->var.nom,nom)==0 && temp->var.portee <= portee){
				count--;
				if(count == 0){			
					temp->var.init = 1;	
				}
			}
			temp = temp->suivant;
		}
	}
}

int est_constante(char *nom, int portee){
	// 1 constante 0 non 
	Element *temp = liste_var->premier;
	int flag = 0;
	int cons;
	while(temp != NULL){ 
		if(strcmp(temp->var.nom,nom)==0 && temp->var.portee <= portee){
			cons = temp->var.constant;
			flag = 1;
		}
		temp = temp->suivant;
	}	
	if(flag){
		return cons;
	}	
	fprintf(stderr, "ERROR : est_constante, variable n'est pas dans la table\n");
    exit(-1);
}

int est_init(char *nom, int portee){
	// 1 init 0 non 
	Element *temp = liste_var->premier;
	int init;
	int flag = 0;
	while(temp != NULL){ 
		if(strcmp(temp->var.nom,nom)==0 && temp->var.portee <= portee){
			init = temp->var.init;
			flag = 1;
		}
		temp = temp->suivant;
	}		
	if(flag){
		return init;
	}
	fprintf(stderr, "ERROR : est_init, variable n'est pas declaree\n");
    exit(-1);
}

/*
void affichage_liste_var(){
	Element *aux = liste_var->premier;
	while(aux != NULL){
		printf("nom : %s, init : %d, portee : %d, addr : %d, constant : %d\n",
				aux->var.nom, aux->var.init, aux->var.portee, aux->var.adr_memoire, aux->var.constant);
		aux = aux->suivant;
	}
}

void affichage_liste_var_temp(){
	Element *aux = liste_var_temp->premier;
	while(aux != NULL){
		printf("addr : %d\n",aux->var.adr_memoire);
		aux = aux->suivant;
	}
}


int main(){
	
	init_var_temp();
	init_var(); 
	printf("main \n");
	Liste * liste;
	printf("insertion_variable\n");
	insertion_v("a", 0, 0);
	insertion_v("b", 0, 0);
	insertion_v("c", 1, 0);
	insertion_v("d", 1, 0);
	insertion_v("a", 2, 0);
	insertion_v("e", 3, 0);
	affichage_liste_var();
	printf("insertion_variable_temp\n");
	insertion_v_tmp();
	//affichage(liste_var_temp);
	printf("suppression\n");
	suppression_var(2);
	affichage_liste_var();
	printf("suppression var temp\n");
	suppr_tmp_var();
	printf("done\n");
	return 0;
}//*/
