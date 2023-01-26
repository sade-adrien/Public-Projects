#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

void majuscules(char *pointeur);
void etoiles(char *pointeur, int taille, char *pointeurExemplaire);
void remplacement(char *pointeur, char *pointeuramodifier, char lettre);
void determineMot(FILE *pointeur, int nombreHasard, char *pointeurmotmystere);
int taillemot(char *pointeur);
int nombremots(FILE *pointeur);
int strcmp ( const char * str1, const char * str2 );
int nombreMystereCrea(int MAX, int MIN);
char lettreentree();


#endif // MAIN_H_INCLUDED
