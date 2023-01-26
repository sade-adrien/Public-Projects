#pragma once

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

class Matrice {
    int nbr_lignes;
    int nbr_colonnes;
    double* tab;
    int* compteur;
    void deepCopy();

public:
    Matrice(int nbr_lignes_colonnes);
    Matrice(int nbr_lignes_fct, int nbr_colonnes_fct);
    Matrice (const Matrice& M);
    ~Matrice();
    void Init_Matrice();
    void Afficher_Matrice();
    void Afficher_Element(int ligne_element, int colonne_element);
    void Modifier_Element(double valeur, int ligne_element, int colonne_element);
    Matrice Produit_Matriciel(Matrice M);
    double operator()(int i, int j) const {return tab[i+j*nbr_lignes];}
    double& operator()(int i, int j) {deepCopy(); return tab[i+j*nbr_lignes];}
};


