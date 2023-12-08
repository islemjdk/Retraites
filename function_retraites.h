#include "stdlib.h"
#include "stdio.h"

typedef struct dossier *liste;
typedef struct dossier
{
    char nom[35];
    char prenom[20];
    char sexe;
    char adresse[30];
    int age;
    int kids;
    int date_naissance;
    int taux;
    float spmm;
    char majoration;
    char* banque;
    char* compt;
    char peymen;
    int ans_activite;
    float montant_mensuel;
    liste dossier_suiv;
} dossier;
int legal_retraite(int date_naissance, char sexe , int age);
liste nouveau_dossier(int numero_dossier, char nom[35], char prenom[20], char sexe, char adresse[30], char *nmr_compte[15], char *banque_saisie[30], int date_naissance, int taux, float spmm, char peym, char majoration, int kid, int nbr_ans_activite, float salaire, float montant_mensuel);
float duree_taux(int nbr_ans_activite);
float SPMM(float salaire);
char majoration_conjoint(char majoration);
char PEYMEN(char paym);
char* nom_banque(char banque_saisie[30]);
char* compte(char nmr_compte[15]);
int kids(int kid);
char* nom_banque(char banque_saisie[30]);
float montant_pension(float spmm, int nmb_ans_activite);
liste modifier(liste tete);
void affichge(liste tete);
liste ajoute_dossier(liste tete);