#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include "main.h"
#define FICHIER "MOTMYSTERE2.txt"
#define TAILLE_MAX 100


int main()
{
    int erreursPossibles = 10;
    int verification = 0;
    int taillemotmystere = 0;
    int nombreMystere = 0;
    int MIN = 1;
    int MAX = 0;
    int resopblm = 1;
    int i = 0;
    char eppuisement = 0;
    int nbrmots = 0;
    char lettre = 0;
    int reponse = 1;
    char *pointeurDifficulte = NULL;
    char *pointeurMotMystere = NULL;
    char *pointeurcopieMotMystere = NULL;
    char *pointeurmotTrouve = NULL;
    char motTrouve[TAILLE_MAX] = "";
    char motMystere[TAILLE_MAX] = "";
    char copiemotMystere[TAILLE_MAX] = "";
    char tableauTest[TAILLE_MAX] = "";
    char *motetoile = NULL;
    char chaineDifficulte[TAILLE_MAX] = {0};
    char chaineRejouer[TAILLE_MAX] = {0};
    char chaineOui[4] = {'O', 'U', 'I', '\0'};
    char chaineNon[4] = {'N', 'O', 'N', '\0'};
    FILE *pointeur = NULL;


    printf("\n********************************************************************************\n********************************   LE PENDU   **********************************\n********************************************************************************\n\n\n\n");
    printf("Bienvenue dans le jeu du pendu!\nLe but de ce jeu est de trouver le mot mystere.\nMais attention, vous n'avez le droit qu'a 10 erreurs avant d'etre pendu(e)!\n\n");
    Sleep(1000);
    printf("\n   //Avant de commencer souhaitez-vous changer le nombre d'erreurs possibles,\n   //pour adapter la difficulte?(oui ou non)...");

while (verification == 0)
    {
    scanf("%s", chaineDifficulte); printf("   //");
    pointeurDifficulte = chaineDifficulte;
    majuscules(pointeurDifficulte);


    if (strcmp(chaineDifficulte, chaineOui) == 0)                                      //Changement de difficulté
    {
        printf("\n   //Tres bien, entrez un nombre d'erreurs possibles:.....");

        while (verification == 0)
        {
         scanf("%d", &erreursPossibles);
         if (erreursPossibles > 0)
           {
              printf("\n\n---Vous aurez donc %d erreurs possibles.---\n", erreursPossibles);
              verification++;
           }
         else if (erreursPossibles <= 0)
           {
               printf("\n   //Le nombre entre n'est pas valide, entrez un nombre strictement positif:.....");

           }
        }

        verification = 1;

    }
    else if (strcmp(chaineDifficulte, chaineNon) == 0)
    {

        printf("\n\n\n---Tres bien, vous aurez donc %d erreurs possibles!---\n", erreursPossibles);
        verification = 1;
    }
    else
    {
        printf("\n   //Je n'ai pas compris veuillez reessayer SVP....");
    }

    }
    scanf("%c", &eppuisement);


    printf("\n\nBien, nous pouvons commencer!\n\n       Vous devrez donc trouvez le mot mystere remplace par des ***.\n       En essayant des lettres une a une ;) !\n\n\n");


    pointeur = fopen(FICHIER, "r+");                                                      //FICHIER en #define
    nbrmots = comptemot(pointeur);
    MAX = nbrmots;

    nombreMystere = nombreMystereCrea(MAX, MIN);                                         //!!! À changer si changement du fichier TXT !!!


    pointeurMotMystere = motMystere;
    Sleep(1800);

    determineMot(pointeur, nombreMystere, pointeurMotMystere);



    taillemotmystere = taillemot(pointeurMotMystere);

    pointeurcopieMotMystere = copiemotMystere;
    etoiles(pointeurcopieMotMystere, taillemotmystere, pointeurMotMystere);



while (erreursPossibles > 0 && resopblm != 0)
{
    printf("Quel est le mot mystere : %s ?\n", copiemotMystere);
    printf("Entrez une lettre:");
    lettre = lettreentree();

    if(strchr(pointeurMotMystere, lettre) != 0)
       {
           printf("\nBonne lettre!\n\n");
           reponse = 1;
           remplacement(pointeurMotMystere, pointeurcopieMotMystere, lettre);
           resopblm = 0;
           i = 0;

           while (*(pointeurcopieMotMystere + i) != 0)
           {
               if (*(pointeurcopieMotMystere + i) == '*')
               {
                 resopblm++;
               }
               i++;
           }

       }
    else
       {
           char smiley = 1;
           erreursPossibles--;
           if (erreursPossibles == 9)
           {
               printf("\n\n       ____\n");
           }
           else if (erreursPossibles == 8)
           {
               printf("\n\n        |\n        |\n        |\n        |\n        |\n       ____\n");
           }
           else if (erreursPossibles == 7)
           {
               printf("\n\n          ___\n        |\n        |\n        |\n        |\n        |\n       ____\n");
           }
           else if (erreursPossibles == 6)
           {
               printf("\n\n          ___\n        |    |\n        |\n        |\n        |\n        |\n       ____\n");
           }
           else if (erreursPossibles == 5)
           {
               printf("\n\n          ___\n        |    |\n        |    %c\n        |\n        |\n        |\n       ____\n", smiley);
           }
           else if (erreursPossibles == 4)
           {
               printf("\n\n          ___\n        |    |\n        |    %c\n        |    |\n        |    |\n        |\n       ____\n", smiley);
           }
           else if (erreursPossibles == 3)
           {
               printf("\n\n          ___\n        |    |\n        |    %c\n        |  --|\n        |    |\n        |\n       ____\n", smiley);
           }
           else if (erreursPossibles == 2)
           {
               printf("\n\n          ___\n        |    |\n        |    %c\n        |  --|--\n        |    |\n        |\n       ____\n", smiley);
           }
           else if (erreursPossibles == 1)
           {
               printf("\n\n          ___\n        |    |\n        |    %c\n        |  --|--\n        |    |\n        |   /\n       ____\n", smiley);
           }
           else if (erreursPossibles == 0)
           {
               printf("\n\n          ___\n        |    |\n        |    %c\n        |  --|--       PENDU\n        |    |\n        |   / \\\n       ____\n", smiley);
           }
           printf("\nMauvaise lettre! Plus que %d erreurs possibles\n\n", erreursPossibles);
           reponse = 1;
       }

}

if (resopblm == 0)
{
    printf("\nBRAVO, vous avez trouvez le mot mystere,\nqui etait : %s", motMystere);
}
else if (erreursPossibles == 0)
{
    printf("\nVous avez ete PENDU(E)!!\nLe mot mystere etait : %s", motMystere);
}
else
  {
      printf("BUG FIN ELSE IF");
  }

verification = 0;
fclose(pointeur);

while (verification == 0)
{

printf("\n\nVoules-vous recommencer?(oui ou non)...");
scanf("%s", chaineRejouer);
majuscules(chaineRejouer);

if (strcmp (chaineRejouer, chaineOui) == 0)
{
    printf("\nTres bien, je redemarre le jeu...");
    scanf("%c", &eppuisement);
    Sleep(1250);
    printf("\n\n================================================================================\n\n");
    main();
}
else if(strcmp(chaineRejouer, chaineNon) == 0)
{
    printf("\nA bientot!\n");
    Sleep(1000);
    exit (0);
}
else
{
   printf("\nJe n'ai pas compris, reessayez!\n");
   scanf("%c", &eppuisement);
}
}

    return 0;
}








void majuscules(char *pointeur)                                                       //Mettre en majuscule un tableau avec un pointeur
{
    int i = 0;

    while (*(pointeur + i) != 0)
    {
        *(pointeur + i) = toupper(*(pointeur + i));
        i++;
    }
}


void etoiles(char *pointeur, int taille, char *pointeurExemplaire)                                              //Transformer une chaîne de caractères en *
{
    int i = 0;

    while ((i < taille))
    {
        if (*(pointeurExemplaire + i) != '-')
        {
        *(pointeur + i) = '*';
        }
        else
        {
            *(pointeur + i) = '-';
        }

        i++;

    }
}


int taillemot(char *pointeur)                                                         //Déterminer la taille d'un mot
{
    int i = 0;

    while (*(pointeur + i) != 0)
    {
       i++;
    }
    i--;
    return i;
}


char lettreentree()                                                                   //Entrer un carcatère
{
    char lettre = 0;
    lettre = 0;
    lettre = getchar();
    lettre = toupper(lettre);

    while(getchar() != '\n');

    return lettre;

}


void remplacement(char *pointeur, char *pointeuramodifier, char lettre)               //Remplacer étoiles par lettre correct
{
    int i = 0;
    i = 0;

    while (*(pointeur + i) != 0)
    {
        if (*(pointeur + i) == lettre)
        {
            *(pointeuramodifier + i) = lettre;
        }
       i++;

    }
}


int comptemot(FILE *pointeur)                                                         //Compter les lignes d'un fichier txt (-1)
{
    char caractereActuel[TAILLE_MAX] = {1};
    char chaineNULL[TAILLE_MAX] = {0};
    int i = 0;
    int j = 0;

    fseek(pointeur, 0, SEEK_SET);

    while(strcmp(caractereActuel, chaineNULL) != 0)
    {
        fgets(caractereActuel, TAILLE_MAX, pointeur);
        if (caractereActuel[0] == ' ')
        {
            while (j != TAILLE_MAX)
            {
            caractereActuel[0 + j] = 0;
            j++;
            }
        }
        i++;
    }
    i--;
    return i;
}


void determineMot(FILE *pointeur, int nombreHasard, char *pointeurmotmystere)         //Prend un mot avec le nombre au hasard
{


    char tableau[TAILLE_MAX] = "";
    int i = 0;

    fseek(pointeur, 0, SEEK_SET);

    while (nombreHasard > 0)
    {
        fgets(tableau, TAILLE_MAX, pointeur);
        nombreHasard--;
    }

    while (i < TAILLE_MAX)
    {
        *(pointeurmotmystere + i) = tableau[i];
        i++;
    }
}


int nombreMystereCrea(int MAX, int MIN)                                                   //Création d'un nombre (+ ou -) aléatoire (MOTMYSTERE2)
{
    int aleatoire = 0;
    int random = 0;
    int nombreMystere = 0;

srand(time(NULL));
nombreMystere = ((rand() % (MAX - MIN + 1)) + MIN);

return nombreMystere;
}


int nombreMystereCreaComplique(int MAX, int MIN)                                          //Création d'un nombre (+ ou -) aléatoire pour nombre grand (MOTMYSTERE)
{
    int aleatoire = 0;
    int random = 0;
    int nombreMystere = 0;

srand(time(NULL));
nombreMystere = ((rand() % (MAX - MIN + 1)) + MIN);
nombreMystere = nombreMystere * 6 / 4 + MAX - MAX / 3;
nombreMystere = ((rand() % nombreMystere));
aleatoire = ((rand() % 10));
nombreMystere = nombreMystere * aleatoire;
random = ((rand() % 200000));
nombreMystere = nombreMystere + random;

return nombreMystere;
}



