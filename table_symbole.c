#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "table_symbole.h"


/** TODO 
	compiler
**/

/* fprintf stderr pour changer la sortie ex: faire un warning */

/* MODIFICATION YACC : 
 
BlocAff : tID tEG Expr tPV {addr = cherAdd($1); 
							printf("AFC %d ",addr);
							huiuu;
							gyg
							}; 
-> entre parenthèse on peut mettre tout le code C qu'on veut qui permet de générer l'assembleur en dur
-> $1 correspond à la valeur de tID ... 

Expr : 	Expr tPLUS Expr	{$$ = 4}
-> $$ = 4 permet de retourner 4 quand on appelle 

*/

#define TAILLEMAX 1000
//enum type {INT, CONST};

Liste *liste_var = NULL;
Liste *liste_var_temp = NULL;

void initialisation(Liste *liste)
{
	liste = malloc(sizeof(Liste));
	memset(liste, 0, sizeof(Liste));
	liste->premier = NULL;
}

void insertion(Variable nvVar, int var_temp) //si on insere une variable temporaire -> var_temp = 1 sinon var_temp = 0
{
	int deb_adresse = 0;
	Liste *liste = liste_var;
	if(var_temp == 1){
		int deb_adresse = TAILLEMAX;
		liste = liste_var_temp;
	}
	/* Création du nouvel élément */
	Element *nouveau = malloc(sizeof(*nouveau));
	if (liste == NULL)
	{
	    initialisation(liste);
	}
	nouveau->var = nvVar;

	/* Insertion de l'élément au début de la liste */
	Element *aux = liste->premier;
	if(aux==NULL){
		liste->premier = nouveau;
		liste->dernier = nouveau;
		nouveau->var.adr_memoire = deb_adresse;
		liste->nb_element = 1;
	}
	else{

		/* Verification que la variable n'est pas deja declarée */
		Element *temp = liste->premier;
		while(temp != NULL){ 
			if(strcmp(temp->var.nom,nvVar.nom)==0 && temp->var.portee == nvVar.portee){
				fprintf(stderr, "ERROR : Variable deja dans la table\n");
			    exit(-1);
			}
			temp = temp->suivant;
		}		

		if(liste->dernier->var.adr_memoire = TAILLEMAX+1){
			fprintf(stderr, "ERROR : plus de place en memoire\n");
		    exit(-1);
		}
		liste->dernier->suivant = nouveau;
		liste->dernier = nouveau;
		nouveau->var.adr_memoire = liste->nb_element;
		liste->nb_element++;
	}
	nouveau->suivant = NULL;	
}

void insertion_v(char *id, int profondeur, int constant){
	int portee = profondeur; //transformer la profondeur en portee 
	Variable var;
	var.nom = id;
	var.init = 0;
	var.portee = portee;
	var.constant = constant;
	insertion(var, 0);
}

int insertion_v_tmp(){
	Variable var;
	var.nom = "tmp";
	var.init = 1;
	var.portee = -1;
	var.constant = 0;
	insertion(var,1);
	return liste_var_temp->dernier->var.adr_memoire;
}

int get_address(char *nom, int profondeur){
	int portee = profondeur; //transformer la profondeur en portee 
	Element *temp = liste_var->premier;
	while(temp != NULL){ 
		if(strcmp(temp->var.nom,nom)==0 && temp->var.portee == portee){
			return temp->var.adr_memoire;
		}
		temp = temp->suivant;
	}		
	fprintf(stderr, "ERROR : variable n'est pas dans la table\n");
    exit(-1);
}
 
void suppr_tmp_var(){
	Element *aux = liste_var_temp->premier;
	while(aux->suivant != liste_var_temp->dernier && aux != NULL){
		aux = aux->suivant;
	}
	if(aux == NULL){
		fprintf(stderr, "ERROR : pas de variable temporaire\n");
		exit(-1);
	}
	aux->suivant = NULL;
	//free ! 
}

void suppression(Liste *liste, int supPortee){
	Element *aux = liste->premier;
	if(liste->premier->var.portee == supPortee){
		liste->premier = NULL;
		liste->dernier = NULL;
	}
	else{
		while(aux->suivant!=NULL && aux->suivant->var.portee < supPortee){
			aux = aux->suivant;
		}
		aux->suivant = NULL;
		liste->dernier = aux;
		liste->nb_element = aux->var.adr_memoire+1;
		//free(aux);
	}
}

int est_constante(char *nom, int profondeur){
	int portee = profondeur; //transformer la profondeur en portee 
	// 1 constante 0 non 
	Element *temp = liste_var->premier;
	while(temp != NULL){ 
		if(strcmp(temp->var.nom,nom)==0 && temp->var.portee == portee){
			return temp->var.constant;
		}
		temp = temp->suivant;
	}		
	fprintf(stderr, "ERROR : variable n'est pas dans la table\n");
    exit(-1);
}
void affichage(Liste *liste){
	Element *aux = liste->premier;
	while(aux != NULL){
		printf("nom : %s, portee : %d, addr : %d\n",aux->var.nom, aux->var.portee, aux->var.adr_memoire);
		aux = aux->suivant;
	}
}

