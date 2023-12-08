
#include "function_retraites.h"

#define min(A, B) (((A) < (B)) ? (A) : (B))

liste nouveau_dossier(int numero_dossier, char nom[35], char prenom[20], char sexe, char adresse[30], char *nmr_compte[15], char *banque_saisie[30], int date_naissance, int taux, float spmm, char peym, char majoration, int kid, int nbr_ans_activite, float salaire, float montant_mensuel)
{

    liste temp = malloc(sizeof(dossier));
    temp->sexe = sexe;
    temp->kids = KIDS(kid);
    temp->date_naissance = date_naissance;
    if (legal_retraite(date_naissance, sexe, kid) == 0)
    {
        free(temp);
        return NULL;
    }
    temp->ans_activite = ANS_ACTIVITE(nbr_ans_activite);
    if (nbr_ans_activite < 15)
    {
        free(temp);
        return NULL;
    }
    strncpy(temp->adresse, adresse, 30);
    strncpy(temp->nom, nom, 35);
    strncpy(temp->prenom, prenom, 20);
    temp->taux = duree_taux(nbr_ans_activite);
    temp->spmm = SPMM(salaire);
    temp->majoration = majoration_conjoint(majoration);
    temp->peymen = PEYMEN(peym);
    temp->banque = nom_banque(banque_saisie[30]);
    temp->compt = compte(nmr_compte[15]);
    temp->age = lage(date_naissance);
    temp->montant_mensuel = montant_pension(spmm, nbr_ans_activite);
    temp->dossier_suiv = NULL;
}
char majoration_conjoint(char majoration)
{
    do
    {
        printf("Majoration pour conjoint a charge (O/N):");
        scanf("%s", &majoration);
    } while (majoration = 'O' || 'N');
    if (majoration == 'N')
    {
        printf("Il na pas de majoration!");
    }
    else
    {
        printf("Il y a une majoration de 2500DA");
    }
    return majoration;
}
char PEYMEN(char paym)
{
    char payement;
    do
    {
        printf("entrez le mode de payement(mandat/CCP/banque)(M/C/B):");
        scanf("%s", &payement);
    } while (payement = 'M' || 'C' || 'B');
    return payement;
}
char *nom_banque(char banque_saisie[30])
{
    printf("entrez le nom de banque:");
    fgets(banque_saisie, 30, stdin);
    return banque_saisie;
}
char *compte(char nmr_compte[15])
{

    do
    {
        printf("entrez le numero de compte: ");
        fgets(nmr_compte, 15, stdin);
    } while (nmr_compte > 0);
    return nmr_compte;
}
int ANS_ACTIVITE(nbr_ans_activite)
{
    printf("Entrez le nbr dannee dactivite : ");
    scanf("%d", &nbr_ans_activite);
    return nbr_ans_activite;
}
int lage(int date_naissance)
{
    int age = 2023 - date_naissance;
    return age;
}
int KIDS(int kid)
{
    int kds;
    do
    {
        printf("entrez le nombre des enfaint :");
        scanf("%d", &kds);
    } while (kds >= 0);
    return kds;
}
float montant_pension(float spmm, int nbr_ans_activite)
{
    float AS, IRG, avantage_principal, montant_mensuel;
    char majoration;
    int maj, SNMG = 20000;
    AS = (2 * avantage_principal) / 100;
    if (avantage_principal < 20000)
    {
        IRG = 0;
    }
    else
    {
        if (avantage_principal >= 20000 && avantage_principal <= 30000)
        {
            IRG = (10 * avantage_principal) / 100;
        }
        else
        {
            IRG = (10 * avantage_principal) / 100;
        }
    }
    if (majoration_conjoint(majoration) == 'N')
    {
        maj = 0;
    }
    else
    {
        maj = 2500;
    }
    avantage_principal = spmm * nbr_ans_activite * 2.5;
    montant_mensuel = avantage_principal - (AS + IRG) + maj;
    if (montant_mensuel < 15000)
    {
        montant_mensuel = 15000;
    }
    else
    {
        if (montant_mensuel > SNMG * 15)
        {
            montant_mensuel = 300000;
        }
    }
    return montant_mensuel * 0.02; // Le montant de la retenue sécurité sociale est de 2% du salaire brut.
}
float duree_taux(int nbr_ans_activite)
{

    float taux;
    if (nbr_ans_activite < 5)
    {
        printf("Nous vous prions de nous excuser. Vous navez pas le droit de recevoir de prestations de retraite.");
        printf("\nla duree de cotisation est insuffisant");
    }
    else // nbr_ans_activite >= 5
    {
        if (nbr_ans_activite <= 15)
        {
            printf("Accepte! une allocation de retraite.");
            taux = nbr_ans_activite * 2.5;
            if (taux > 80)
            {
                taux = 80;
            }
            printf("\nLe taux de l'allocation est :%f %", taux);
        }
        else
        {
            printf("Accepte! une pension de retraite.");
            taux = nbr_ans_activite * 2.5;
            if (taux > 80)
            {
                taux = 80;
            }
            printf("\nLe taux de la pension est :%f %", taux);
        }
    }
    return taux / 100;
}
int legal_retraite(int date_naissance, char sexe, int kid)
{
    // 1 <=> true
    // 0 <=> false

    if (sexe == ('H' || 'h'))
    {
        if ((2023 - date_naissance) < 60)
        {
            printf("Nous vous prions de nous excuser. Vous navez pas le droit de recevoir de prestations de retraite.");
            printf("Moins de 60 ans !");
            return 0;
        }
        else
        {
            printf("Vous avez droit à une pension.");
            return 1;
        }
    }
    else
    {

        if (sexe == ('F' || 'f'))
        /*lazem nogredlha ytrigl l3mor m3a 3adad ta lowlad*/
        {

            int age_retraite = 55 - min(kid, 3);
            if ((2023 - date_naissance) < age_retraite)

            {
                printf("Nous vous prions de nous excuser. Vous navez pas le droit de recevoir de prestations de retraite.");
                printf("Moins de 60 ans !");
                return 0;
            }
            else
            {

                printf("Vous avez droit à une pension.");
                return 1;
            }
        }
    }
}
float SPMM(float salaire)
{

    float T = 0;
    for (int i = 1; i <= 5; i++)
    {
        do
        {
            printf("entrez la moyenne des 12 mois de salaire annee %d", i);
            scanf("%f", &salaire);
        } while (salaire > 20000);
        T = T + salaire;
    }
    float spmm = T / 5;
    printf("le salaire de poste mensuel moyen (SPMM) est: %f", spmm);
    return spmm;
}
liste ajoute_dossier(liste tete)
{
    liste temp;
    char nom[35], adresse[30], prenom[20], nmr_compte[15], banque_saisie[30];
    int date_naissance, kid, nbr_ans_activite;
    float taux, spmm, salaire, montant_mensuel;
    char sexe, numero_dossier, peym, majoration;

    printf("\n entrer le nom de retraite: ");
    scanf("%s", nom);
    getchar();
    printf("\n entrer le prenom de retraite: ");
    scanf("%s", prenom);
    getchar();
    printf("entrez le sexe de retraite: ");
    scanf("%c", &sexe);
    printf("\n entrer ladresse de retraite: ");
    scanf("%s", adresse);
    getchar();
    if (tete == NULL)
    {
        tete = nouveau_dossier(numero_dossier, nom, prenom, sexe, adresse, &nmr_compte, &banque_saisie, date_naissance, taux, spmm, peym, majoration, kid, nbr_ans_activite, salaire, montant_mensuel);
        temp = tete;
    }
    else
    {
        temp->dossier_suiv = nouveau_dossier(numero_dossier, nom, prenom, sexe, adresse, &nmr_compte, &banque_saisie, date_naissance, taux, spmm, peym, majoration, kid, nbr_ans_activite, salaire, montant_mensuel);
        temp = temp->dossier_suiv;
    }
    printf("\n \t ****OERATION EFFECTUEE****");
    return tete;
}
liste modifier(liste tete)
{
    char nmr_compte[15];
    float salaire;
    if (tete == NULL)
    {
        printf("il nexiste aucunne dossier !!!");
        return tete;
    }
    liste temp = tete;
    while (temp != NULL)
    {
        if (temp->compt == nmr_compte)
        {
            temp->spmm = SPMM(salaire);
            printf("la modification est terminer avec succer !");
            return tete;
        }
        temp = temp->dossier_suiv;
    }
    printf("se dossier nexiste pas !!");
    return tete;
}
void affichage(liste tete)
{
    liste temp = tete;
    while (temp != NULL)
    {
        printf("\nle nom de retraite : %s", temp->nom);
        printf("\nle prenom de retraite : %s", temp->prenom);
        printf("\nle prenom de retraite : %s", temp->prenom);
        printf("\nle nmr de compte de retraite : %s", temp->compt);
        printf("\nle salaire de retraite : %s", temp->spmm);
        printf("\n\t-----****-----");
        temp = temp->dossier_suiv;
    }
}
liste recherche(liste tete)
{
    liste temp = tete;
    char compt[15];
    printf("\n Entrez le nmr de compte : ");
    scanf("%s", &compt);
    getchar();
    if (temp != NULL)
    {
        while (temp != NULL)
        {
            if (strcmp(temp->compt, compt) == 0)
            {
                printf("le nom de retraite : %s", temp->nom);
                printf("\nle prenom de retraite : %s", temp->prenom);
                printf("\nle nbr dannee dactivite de retraite : %d", temp->ans_activite);
                printf("\nl age de retraite : %d", temp->age);
                printf("\nle majoration conjoint de retraite : %c", temp->majoration);
                if (temp->majoration == 'O')
                {
                    printf("\nle mode de payement : %c", temp->peymen);
                    printf("\nle nom de la banque : %s", temp->banque);
                }
                if (temp->sexe == ('F' || 'f'))
                {
                    printf("\nle nbr des enfant : %d", temp->kids);
                }
                printf("\nle salaire de poste mensuel moyen (SPMM) :%.3f", temp->spmm);
                printf("\nle duree taux de retraite : %.3f", temp->taux);
                printf("\nle montant mensuel de retraite : %.3f", temp->montant_mensuel);
            }
        }
    }
}