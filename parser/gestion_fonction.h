#ifndef GESTION_FONCTION
#define GESTION_FONCTION

typedef struct Variable_fun Variable_fun;
struct Variable_fun
{
	char *nom;
	int adr_instr;
	int adr_retour;
};

typedef struct Element_fun Element_fun;
struct Element_fun
{
	Variable_fun var;
	Element_fun *suivant;
};

typedef struct Liste_fun Liste_fun;
struct Liste_fun
{
	Element_fun *premier;
	Element_fun *dernier;
	int nb_element;
};

void init_liste_fun();
void insertion_fun(char *id, int addr);
int get_addr_fun(char *nom);
int get_addr_return(char *nom);
void set_addr_return(char *nom, int adr);

void affichage_liste_fun();

#endif
