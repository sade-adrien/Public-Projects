#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "main.h"
#define TAILLEMAX 100


int main()
{
    int choix = 0;
    int membreactuel = 0;
    int membreactuel2 = 1;
    float *pointeur = NULL;
    float resultat = 0;
    char chaine[TAILLEMAX] = {0};
    char chaineoui[4] = {'o', 'u', 'i', '\0'};
    char chainenon[4] = {'n', 'o', 'n', '\0'};
    float tableaunombre[TAILLEMAX] = {1};

    printf("Bienvenue dans la Calculatrice!\nQuelle operation souhaitez-vous effectuer?\n1:Addition\n2:Soustraction\n3:Multiplication\n4:Division\n");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        printf("\nTres bien, entrez les nombres a additioner:\n(Entrez 0 lorsque vous avez fini)\n");
        break;
    case 2:
        printf("\nTres bien, entrez les nombres a soustraire:\n(Entrez 0 lorsque vous avez fini)\n");
        break;
    case 3:
        printf("\nTres bien, entrez les nombres a multiplier:\n(Entrez 0 lorsque vous avez fini)\n");
        break;
    case 4:
        printf("\nTres bien, entrez les nombres a diviser:\n(Entrez 0 lorsque vous avez fini)\n");
        break;
    default:
        printf("Je n'ai pas compris, recommencez SVP!");
        Sleep(2000);
        system("cls");
        main();
        break;
    }
    while (tableaunombre[membreactuel] != 0)
        {
                membreactuel++;
                scanf("%f", &tableaunombre[membreactuel]);
        }

tableaunombre[0] = 0;
membreactuel--;
printf("\n\nDonc ");

while (membreactuel2 <= membreactuel)
{
    if (choix == 1)
    {
        printf("%f ", tableaunombre[membreactuel2]);
               if (membreactuel2 < membreactuel)
               {
                   printf("+ ");
               }
    }
    else if (choix == 2)
    {
        printf("%f ", tableaunombre[membreactuel2]);
               if (membreactuel2 < membreactuel)
               {
                   printf("- ");
               }
    }
    else if (choix == 3)
    {
        printf("%f ", tableaunombre[membreactuel2]);
               if (membreactuel2 < membreactuel)
               {
                   printf("* ");
               }
    }
    else if (choix == 4)
    {
        printf("%f ", tableaunombre[membreactuel2]);
               if (membreactuel2 < membreactuel)
               {
                   printf("/ ");
               }
    }

membreactuel2++;
}
printf("= \n");
pointeur = tableaunombre;
    switch (choix)
    {
    case 1 :
        resultat = addition(pointeur);
        printf("%f .\n", resultat);
        break;
    case 2:
        resultat = soustraction(pointeur);
        printf("%f .\n", resultat);
        break;
    case 3:
        resultat = multiplication(pointeur);
        printf("%f .\n", resultat);
        break;
    case 4:
        resultat = division(pointeur);
        printf("%f .\n", resultat);
        break;
    }
    printf("\nVoulez-vous effectuer une nouvelle operation?\noui\nnon\n.....");
    scanf("%s", chaine);
    if(strcmp(chaine, chaineoui) == 0)
    {
        printf("\nTres bien recommencons:\n\n");
        printf("=========================================================\n\n");
        main();
    }
    else if (strcmp(chaine, chainenon) == 0)
    {
        printf("\nTres bien, j'arrete le programme!");
        Sleep(2000);
        return 0;
    }
    else
    {
        printf("\nJe n'ai pas compris, desole.\nJ'arrete le programme.");
        Sleep(2500);
        return 0;
    }
    return 0;
}


float addition(float *pointeur)
{
  float resultat = 0;
  int i = 1;

  while (*(pointeur + i) != 0)
  {
  resultat =  resultat + *(pointeur + i);
  i++;
  }
  return resultat;
}


float soustraction(float *pointeur)
{
    float resultat = 0;
    int i = 1;

    while (*(pointeur + i) != 0)
    {
        if ( i == 1)
        {
            resultat = *(pointeur + i) - resultat;
        }
        else
        {
        resultat = resultat - *(pointeur + i);
        }
        i++;
    }
    return resultat;
}


float multiplication(float *pointeur)
{
    float resultat = 1;
    int i = 1;

    while(*(pointeur + i) != 0)
    {
        resultat = resultat * *(pointeur + i);
        i++;
    }
    return resultat;
}


float division(float *pointeur)
{
    float resultat = 1;
    int i = 1;

    while (*(pointeur + i) != 0)
    {
        if (i == 1)
        {
            resultat = *(pointeur + i) / resultat;
        }
        else
        {
            resultat = resultat / *(pointeur + i);
        }
        i++;
    }
    return resultat;
}
