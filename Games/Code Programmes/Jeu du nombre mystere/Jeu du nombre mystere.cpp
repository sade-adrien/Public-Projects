#include <cstdlib>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int recommencer = 0;
    while(recommencer != 2)
    {
int niveau = 0;
    long MAX = 0;
    long MIN = 0;


    printf("Choisissez un niveau: 1.2.3.!\nOu bien 4.Je souhaite moi-meme choisir les limites de mon nombre mystere!\n");
    scanf("%d",&niveau);

switch(niveau)
{
              default:
                                         printf("Vous n'avez pas respecte les niveaux, par consequent, pas de jeu pour vous!\n");
                                         system("PAUSE");
                                         return 0;
                                         break;
                  case 1:
                       MAX+=100;
                       printf("Vous avez choisis le niveau 1, alors la valeur maximum, de votre nombre mystere sera,  100 et minimum 0!\n\n");
                       break;
                       case 2:
                            MAX+=1000;
                            printf("Vous avez choisis le niveau 2, alors la valeur maximum, de votre nombre mystere sera,  1 000 et minimum 0!\n\n");
                            break;
                            case 3:
                                 MAX+=10000;
                                 printf("Vous avez choisis le niveau 3, alors la valeur maximum, de votre nombre mystere sera,  10 000 et minimum 0!\n\n");
                                 break;
                                 case 4:
                                      printf("Choisissez le minimum de votre nombre mystere (pas moins de -1 000 000!):");
                                      scanf("%ld", &MIN);
                                      if(MIN < -1000000)
                                      {
                                             printf("Vous ne devez pas descendre en dessous de -1 000 000!!! Pas de jeu pour vous!");
                                             system("PAUSE");
                                             return 0;
                                             }
                                             printf("Et maintenant le maximum (pas plus de 1 000 000!):");
                                             scanf("%ld", &MAX);
                                             if(MAX > 1000000)
                                      {
                                             printf("Vous ne devez pas monter au dessus de 1 000 000!!! Pas de jeu pour vous!");
                                             system("PAUSE");
                                             return 0;
                                             }
                                             printf("\nDonc, votre nombre mystere sera choisit au hasard entre %ld et %ld.", MIN, MAX);
                                             break;




}
int nombrevies = 0;

printf("Choisissez votre nombre de vies de departs : 1.4V,2.7V,3.11V,4.14V,5.20V,\n6.Je souhaite choisir mon nombre de vies, 7.Je souhaite jouer sans vies!\n");
scanf("%d",&nombrevies);
switch(nombrevies)
{
                  default:

                                         printf("Vous n'en faites qu'a votre tete!! Pas de jeu pour vous!!");
                                         system("PAUSE");
                                         return 0;
                                         break;
                  case 1:
                       nombrevies+=3;
                       printf("Vous avez donc %d vies!Et votre nombre Mystere est entre %ld et %ld\n", nombrevies, MIN, MAX);
                       break;
                       case 2:
                            nombrevies+=5;
                            printf("Vous avez donc %d vies!Et votre nombre Mystere est entre %ld et %ld\n", nombrevies, MIN, MAX);
                            break;
                            case 3:
                                 nombrevies+=8;
                                 printf("Vous avez donc %d vies!Et votre nombre Mystere est entre %ld et %ld\n", nombrevies, MIN, MAX);
                                 break;
                                 case 4:
                                 nombrevies+=10;
                                 printf("Vous avez donc %d vies!Et votre nombre Mystere est entre %ld et %ld\n", nombrevies, MIN, MAX);
                                 break;
                                 case 5:
                                 nombrevies+=15;
                                 printf("Vous avez donc %d vies!Et votre nombre Mystere est entre %ld et %ld\n", nombrevies, MIN, MAX);
                                 break;
                                 case 6:
                                      printf("Vous n'avez plus qu'a choisir votre nombre de vies (pas plus de 250!):");
                                      scanf("%d", &nombrevies);
                                      if(nombrevies > 250 && nombrevies <= 0)
                                      {
                                                    printf("PAS PLUS DE 250!!!!!! Pas de jeu pour vous");
                                                    system("PAUSE");
                                                    return 0;
                                                    }
                                                    printf("Vous obtenez donc, %d vie(s), et votre nombre Mystere est entre %ld et %ld\n", nombrevies, MIN, MAX);
                                                    break;
                                 case 7:
                                      printf("Vous voulez donc jouer sans vie.");
                                      printf("\nChercher le nombre mystere!Entre %ld et 0\n", MAX);
                                           long nombreMystere = 0, nombreEntre = 0, compteurcoup = 0;
                                                 srand(time(NULL));
    nombreMystere = (rand() % (MAX  - MIN + 1)) + MIN;

while (nombreEntre != nombreMystere)
{
      compteurcoup+=1;
       scanf("\n%ld", &nombreEntre);
       if(nombreEntre < 0 || nombreEntre > 10000)
       {
                      printf("Vous devez entrer un nombre entre 0 et 10 000, PAS PLUS!!!!, vous n'avez plus  qu'a recomencer!");
                      system("PAUSE");
                      return 0;
                      }


       if (nombreEntre < nombreMystere)
       {
                       printf("\nLe nombre est plus grand!");
                        if(compteurcoup > 1)
                             {
      printf("\nVous en etes a votre %ld coup(s)", compteurcoup);
      }
               printf("\nChercher,encore,le nombre Mystere!");


                       }

                       else if (nombreEntre > nombreMystere)
                       {
                       printf("\nLe nombre est plus petit!");
                        if(compteurcoup > 1)
                       printf("\nChercher le nombre Mystere!");
                       {
      printf("\nVous en etes a votre %ld coup(s)!", compteurcoup);
      }
                       }

                            else if(nombreEntre = nombreMystere)
                             printf("\n\nBRAVO a vous!!!Le nombre etait bien %ld!!\n\n", nombreMystere);

                                }
                                system("PAUSE");
                                return 0;
                                 break;





                       }
                       printf("\nChercher le nombre Mystere!");

     long nombreMystere = 0, nombreEntre = 0, compteurcoup = 0;
                                                 srand(time(NULL));
    nombreMystere = (rand() % (MAX  - MIN + 1)) + MIN;

while (nombreEntre != nombreMystere && nombrevies != 0)
{
      compteurcoup+=1;
       scanf("%ld", &nombreEntre);
              if(nombreEntre < -1000000  || nombreEntre > 1000000)
       {
                      printf("Vous devez entrer un nombre entre -1 000 000 et 1 000 000, PAS PLUS, PAS MOINS!!!!, vous n'avez plus   qu'a recomencer!");
                      system("PAUSE");
                      return 0;
                      }
       nombrevies-=1;

       if (nombreEntre < nombreMystere)
       {
                       printf("\nLe nombre est plus grand!");
                       printf("\nChercher le nombre Mystere!");
                        if(compteurcoup > 1)

               {
      printf("\nVous en etes a votre %ld coup(s) et vous n'avez plus que %d de vies!!\n", compteurcoup, nombrevies);
      }

                       }

                       else if (nombreEntre > nombreMystere)
                       {
                       printf("\nLe nombre est plus petit!");
                        if(compteurcoup > 1)
                       printf("\nChercher le nombre Mystere!");
                       {
      printf("\nVous en etes a votre %ld coup(s) et vous n'avez plus que %d de vies!!", compteurcoup, nombrevies);
      }
                       }


                            else if(nombreEntre = nombreMystere)
                            {
                             printf("\n\nBRAVO a vous!!!Le nombre etait bien %ld!!(et il vous restait %d de vies)!\n\n", nombreMystere, nombrevies);

                                while(recommencer != 1 && recommencer != 2)
                                {
                                 recommencer = 0;
                                printf("Si vous souhaitez recommencer, entrez 1., sinon entrez 2.:");
                                scanf("%d", &recommencer);
                                if(recommencer = 2)
                                printf("Au revoir!", recommencer);
                                else if(recommencer = 1)
                                printf("Bon jeu!");
                                else
                                printf("Non correct, reentre 1 ou 2:!");
                                }
                                }
                                }

                                         if(nombrevies = 0)
      printf("\n\nDesole pour vous, vous avez perdu, car vos vies sont descendues a %d!", nombrevies);

   system("PAUSE");
    return 0;
}
}
