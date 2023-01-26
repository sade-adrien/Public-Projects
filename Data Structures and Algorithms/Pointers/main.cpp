#include "outils.h"

using namespace std;


int Random_int_Generator(int iMin, int iMax) //only used in the testing loop to create random matrices
{
   return rand() % iMax + iMin;
}

double Random_Float_Generator(double fMin, double fMax) //only used in the testing loop to create random matrices
{
   double f = (double)rand() / RAND_MAX;
   return fMin + f * (fMax - fMin);
}


int main()
{

   while(true) //testing loop
   {

       printf("10s de pause...\n");
       std::this_thread::sleep_for(std::chrono::milliseconds(10000));

       int n=Random_int_Generator(1,10);
       int m=Random_int_Generator(1,10);
       int k=Random_int_Generator(1,10);

       Matrice M(n,m);
       M.Init_Matrice();
       cout << "M=" << endl;
       for(int i=1; i<n+1; i++)
           for(int j=1; j<m+1; j++)
               M.Modifier_Element(Random_Float_Generator(0,9),i,j);
       M.Afficher_Matrice();

       Matrice N(m,k);
       N.Init_Matrice();
       cout << "N=" << endl;
       for(int i=1; i<m+1; i++)
           for(int j=1; j<k+1; j++)
               N.Modifier_Element(Random_Float_Generator(0,9),i,j);
       N.Afficher_Matrice();

       cout << "MN=" << endl;
       M.Produit_Matriciel(N).Afficher_Matrice();

   }

   return 0;
}

