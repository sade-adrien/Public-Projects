#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;
#include <unistd.h>
#include <iostream>
#include <cmath>
using namespace std;

const int NombreCouleurs=10;
const int NombreCouleursPalette=8;


void ConversionHexa(int deci[3], int Hexa);
void ordonnerTableau(int tableau[], int tableaumiroir1[], int tailleTableau);
void ChargerImage(string name, byte* &r, byte* &g, byte* &b, int& w, int& h);
void DetruireTableau(byte* &t);
void AfficherImage(byte* r, byte* g, byte* b, int w, int h);
void PaletteDiscretiseedeCouleurs(int Palette[NombreCouleursPalette*NombreCouleursPalette*NombreCouleursPalette], byte* r, byte* g, byte* b, int w,int h);
void DetermineCouleursPrincipales(int Palette[NombreCouleursPalette*NombreCouleursPalette*NombreCouleursPalette], int CouleursPrincipales[NombreCouleurs+1]);
void ConversionTableauCouleursRGB(int CouleursPrincipales[NombreCouleurs+1], int CouleursPrincipalesRGB[NombreCouleurs+1]);
void DeterminePourcentagesCouleursPrincipales(int PourcentagesCouleurs[NombreCouleurs+1], int CouleursPrincipales[NombreCouleurs+1], int Palette[NombreCouleursPalette*NombreCouleursPalette*NombreCouleursPalette]);
void RepartitionpourColoriage(int TableauDebutColoriage[NombreCouleurs+1], int PourcentagesCouleurs[NombreCouleurs+1]);
void RemplirTableauxFinaux(byte* &r, byte* &g, byte* &b, int compteur, int TableauDebutColoriage[NombreCouleurs+1], int CouleursPrincipales[NombreCouleurs+1], int w, int h);
void ConversionTableauCouleursGRIS(int CouleursPrincipales[NombreCouleurs+1], int CouleursPrincipalesRGB[NombreCouleurs+1]);
