#include <stdio.h>
#include <stdlib.h>
#include "function_retraites.h"

int main()
{
    liste tete;
    int x;
   
   do
   {
    printf("\nsi vous voullez ajoute un nouveau dossier clic:1");
    printf("\nsi vous voullez afichez tout les dossier des retraite clic:2");
     printf("\nsi vous voullez modifier le salaire de tes annees clic:3");
     printf("\nsi vous veullez rechercher a un dossier clic:4");
     scanf("%d" , &x);
      switch (x)
    {
        case 1:
        tete = ajoute_dossier(tete);
        break;
    case 2:
        printf("voici la liste des dossiers:\n");
        tete = affichage(tete);
        break;
    case 3:
        tete = modifier(tete);
        break;
    case 4:
        tete = recherche(tete);
        break;
    default:
        printf("se choix nexiste pas dans le menu !!!");
        break;
    }
   } while (x > 4);
   
}