#include "outils.h"


Matrice::Matrice(int nbr_lignes_colonnes) {
    nbr_lignes=nbr_lignes_colonnes;
    nbr_colonnes=nbr_lignes_colonnes;
    tab = new double [nbr_lignes_colonnes*nbr_lignes_colonnes];
    compteur = new int (1);
    std::cout << "La matrice carrée est créée: compteur = 1" << std::endl;
}

Matrice::Matrice(int nbr_lignes_fct, int nbr_colonnes_fct) {
    nbr_lignes=nbr_lignes_fct;
    nbr_colonnes=nbr_colonnes_fct;
    tab = new double [nbr_lignes*nbr_colonnes];
    compteur = new int (1);
    std::cout << "La matrice est créée: compteur = 1" << std::endl;
}

Matrice::Matrice (const Matrice& M){
    nbr_lignes=M.nbr_lignes;
    nbr_colonnes=M.nbr_colonnes;
    tab=new double [nbr_lignes*nbr_colonnes];

    double *src=M.tab, *dst=tab;
    for(int i=0; i<nbr_lignes*nbr_colonnes; i++)
        *dst++ = *src++;
    compteur = M.compteur;
    *compteur += 1;

    std::cout << "La matrice est copiée: compteur = " << *compteur << std::endl;

}

Matrice::~Matrice() {
    *compteur -= 1;
    std::cout << "La matrice est détruite: compteur = " << *compteur << std::endl;
    delete [] tab;
}

void Matrice::Afficher_Matrice(){
    for(int i=0; i<nbr_lignes; i++)
    {
        for(int j=0; j<nbr_colonnes; j++)
        {
            std::cout << tab[j*nbr_lignes+i] << " ";
        }

        std::cout << "\n";
    }
}

void Matrice::Init_Matrice(){
    for(int i=0; i<nbr_lignes; i++)
        for(int j=0; j<nbr_colonnes; j++)
            tab[j*nbr_lignes+i]=0;
}

void Matrice::Afficher_Element(int ligne_element, int colonne_element){
    std::cout << tab[(colonne_element-1)*nbr_lignes+ligne_element-1];
}

void Matrice::Modifier_Element(double valeur, int ligne_element, int colonne_element){
    tab[(colonne_element-1)*nbr_lignes+ligne_element-1]=valeur;
}

Matrice Matrice::Produit_Matriciel(Matrice M){
    if(nbr_colonnes != M.nbr_lignes)
    {
        std::cout << "Produit matriciel impossible, matrices incompatibles" << std::endl;
        return 0;
    }

    Matrice M_Resultat(nbr_lignes, M.nbr_colonnes);
    M_Resultat.Init_Matrice();

    for(int i=0; i<M_Resultat.nbr_lignes; i++)
    {
        for(int j=0; j<M_Resultat.nbr_colonnes; j++)
        {
           double S = 0;

           for(int k=0; k<nbr_colonnes; k++)
               S += tab[k*nbr_lignes+i] * M.tab[j*M.nbr_lignes+k];

           M_Resultat.tab[j*M_Resultat.nbr_lignes + i] = S;

        }

    }

    return M_Resultat;
}

void Matrice::deepCopy() {
    if(*compteur>1)
    {
        *compteur -= 1;
        double * tab2 = new double [nbr_lignes*nbr_colonnes];

        for(int i=0; i<nbr_lignes*nbr_colonnes; i++)
            tab2[i] = tab[i];
        tab = tab2;
    }
}
