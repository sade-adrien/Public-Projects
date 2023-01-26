#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main ()
{
    int recommencer = 1;

    while (recommencer == 1)
    {
    recommencer = 0;
    int nombreMystere = 0;
    int LVL = 0;
    int confirmation1 = 0;
    int confirmation2 = 0;
    int confirmationrecommencer = 0;
    int MAX = 0;
    int MIN = 0;
    int essaie = 0;
    signed int coups = 0;

    printf("Bienvenue dans le jeu du nombre mystere! \nLe but de ce jeu est de trouver le nombre prealablement determine par l'IA.\n");
    Sleep(1000);
    printf("Cela etant dit, nous pouvons commencer!\nTout d'abord selectionnez un niveau\n(il determinera le nombre de coups autorises et le maximum et minimum de votre\nnombre).\n");
    Sleep(1000);
    printf("1:LVL1\n2:LVL2\n3:LVL3\n4:Ou bien determinez vos propres conditions avec le LVL4\n\n");


while (confirmation1 != 1)
{
    scanf("%d", &LVL);

    switch (LVL)
    {
    case 1:
        printf("Tres bien, niveau debutant, vous avez donc 15 coups possibles, \net votre nombre mystere se trouve entre 0 et 500.\n");
        confirmation1++;
        MIN = 0;
        MAX = 500;
        coups = 15;
        break;
    case 2:
        printf("Le niveau intermediaire determine donc, 15 coups possibles, \net votre nombre mystere sera compris entre -1.000 et 1.000;\n");
        confirmation1++;
        MIN = -1000;
        MAX = 1000;
        coups = 15;
        break;
    case 3:
        printf("Niveau expert? Bravo! Vous aurez donc 15 coups, \net le nombre mystere sera compris entre -10.000 et 10.000.\n");
        confirmation1++;
        MIN = -10000;
        MAX = 10000;
        coups = 15;
        break;
    case 4:
        printf("Tres bien, choisissez vos conditions de jeu.\n");
        printf("Choisissez votre nombre de coups (ATTENTION POSITIF):");
        scanf("%d", &coups);
        if (coups <= 0)
        {
            printf("Vous n'avez pas respectez les consignes,\nvous avez entre en nombre negatif (ou 0).\nPas de jeu pour vous!\n");
            return 0;
        }
while (confirmation2 != 1)
        {
        printf("\nChoisissez le maximum possible du nombre mystere:");
        scanf("%d", &MAX);
        printf("\nChoisissez le minimum possible du nombre mystere:");
        scanf("%d", &MIN);
        if (MAX <= MIN)
        {
            printf("Attention, votre maximum est inferieur ou egal a votre minimum.\n Veuillez recommencez.");
            MAX = 0;
            MIN = 0;
        }
        else
        {
            confirmation2++;
        }
        }
        printf("Vous avez donc %d coups, et votre nombre mystere et compris entre %d et %d", coups, MIN, MAX);
        confirmation1++;
        break;
    default:
        printf("Le niveau selectionne n'est pas valide, merci de recommencer.");
        LVL = 0;
        break;

    }
}

srand(time(NULL));
nombreMystere = (rand() % (MAX - MIN + 1)) + MIN;

printf("\nLe jeu commence!\n");

while (essaie != nombreMystere && coups > 0)
       {
            printf("Entrez un nombre:");
            scanf("%d", &essaie);
            coups--;
            if (essaie > nombreMystere)
                {
                  if (essaie < MAX)
                  {
                      printf ("\nLe nombre mystere est plus petit!\nIl vous reste %d coups.\nReessayez.", coups);
                  }
                  else if (essaie > MAX)
                  {
                      coups++;
                      printf ("\nLe nombre mystere est plus petit!\nRappelez-vous, le nombre mystere n'est pas superieur a %d.\nCe coup n'est pas pris en compte.\nIl vous reste %d coups.\nReessayez.", MAX, coups);
                  }
                }
            else if (essaie < nombreMystere)
                {
                    if (essaie > MIN)
                    {
                        printf("\nLe nombre mystere est plus grand!\nIl vous reste %d coups.\nReessayez.", coups);
                    }
                    else if (essaie < MIN)
                    {
                        coups++;
                        printf("\nLe nombre mystere est plus grand!\nRappelez-vous, le nombre mystere n'est pas inferieur a %d.\nCe coups n'est pas pris en compte.\nIl vous reste %d coups.Reessayez.", MIN, coups);
                    }
                }
       }

       if (essaie == nombreMystere && coups != 0)
       {
           printf("\n\n\nBravo, vous avez gagne!!!\Le nombre mystere etait bien %d.\nEt il vous restait %d coups.", nombreMystere, coups);
       }
       else if (coups == 0 && essaie != nombreMystere)
       {
           printf("\n\n\nDesole vous avez perdu.\nVous n'avez plus de coups possibles.\nLe nombre mystere etait %d.", nombreMystere);
       }
       else
       {
           printf("\n\n\nBravo vous avez gagne,\nmais c'etait juste puisque c'etait votre dernier coup!\nLe nombre mystere etait bien %d.", nombreMystere);
       }

    printf("Le jeu est termine souhaitez-vous recommencer?\n1:OUI\n2:NON\n");

    while (confirmationrecommencer != 1)
    {
        confirmationrecommencer = 0;
    scanf("%d", &recommencer);
    switch (recommencer)
    {
    case 1:
        printf("Tres bien, je redemarre le jeu!\n");
        printf("\n======================================================================\n\n");
        Sleep(2000);
        confirmationrecommencer++;
        break;
    case 2:
        printf("\nDommage, a bientot!\n");
        confirmationrecommencer++;
        recommencer = 0;
        return 0;
        break;
    default:
        printf("La reponse n'est pas correct veuillez reessayez.\n");
        break;
    }
    }
}
return 0;
}

