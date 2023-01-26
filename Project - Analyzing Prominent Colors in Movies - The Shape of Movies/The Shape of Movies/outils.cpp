#include "outils.h"

void ConversionHexa(int deci[3], int Hexa)
{
    for(int i=0;i<NombreCouleursPalette;i++)
    {
        for(int j=0;j<NombreCouleursPalette;j++)
        {
            for(int k=0;k<NombreCouleursPalette;k++)
            {
                if(i+NombreCouleursPalette*j+NombreCouleursPalette*NombreCouleursPalette*k==Hexa)
                {
                    deci[0]=k;
                    continue;
                }
            }
            if(i+NombreCouleursPalette*j+NombreCouleursPalette*NombreCouleursPalette*deci[0]==Hexa)
            {
                deci[1]=j;
                continue;
            }
        }
        if(i+NombreCouleursPalette*deci[1]+NombreCouleursPalette*NombreCouleursPalette*deci[0]==Hexa)
        {
            deci[2]=i;
            continue;
        }
    }
}

void ordonnerTableau(int tableau[], int tableaumiroir1[], int tailleTableau)
{
    int i = 0; // Variable Index de boucle lecture tableau
    int d = 0 ; // Variable de décalage Index de boucle lecture tableau
    int tampon = 0;
    int tampon1 = 0;

    for(d=1; d < tailleTableau; d++)
        for(i=d; i < tailleTableau; i++)

            if (tableau [i]>= tableau [d])
            {
            tampon = tableau [d];
            tableau [d]= tableau [i];
            tableau [i] = tampon;

            tampon1 = tableaumiroir1[d];
            tableaumiroir1[d] = tableaumiroir1[i];
            tableaumiroir1[i] = tampon1;
            }
}

void ChargerImage(string name, byte* &r, byte* &g, byte* &b, int& w, int& h)
{
    loadColorImage(stringSrcPath(name),r,g,b,w,h);
}

void DetruireTableau(byte* &t)
{
    delete [] t;
}

void AfficherImage(byte* r, byte* g, byte* b, int w, int h)
{
    putColorImage(0,0,r,g,b,w,h);
}

void PaletteDiscretiseedeCouleurs(int Palette[NombreCouleursPalette*NombreCouleursPalette*NombreCouleursPalette], byte* r, byte* g, byte* b, int w,int h)
{
    int testr;
    int testg;
    int testb;

    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            testr=int(float(r[i+h*j])/(float(256)/float(NombreCouleursPalette)));
            testg=int(float(g[i+h*j])/(float(256)/float(NombreCouleursPalette)));
            testb=int(float(b[i+h*j])/(float(256)/float(NombreCouleursPalette)));

            Palette[testr + NombreCouleursPalette*testg + NombreCouleursPalette*NombreCouleursPalette*testb]++;
        }
    }
}

void DetermineCouleursPrincipales(int Palette[NombreCouleursPalette*NombreCouleursPalette*NombreCouleursPalette], int CouleursPrincipales[NombreCouleurs+1])
{
    int PaletteOrdonee[NombreCouleursPalette*NombreCouleursPalette*NombreCouleursPalette];
    int Miroir[NombreCouleursPalette*NombreCouleursPalette*NombreCouleursPalette];
    for(int k=0;k<NombreCouleursPalette*NombreCouleursPalette*NombreCouleursPalette;k++)
    {
        PaletteOrdonee[k]=Palette[k];
        Miroir[k]=k;
    }
    ordonnerTableau(PaletteOrdonee,Miroir,NombreCouleursPalette*NombreCouleursPalette*NombreCouleursPalette);
    for(int k=1;k<NombreCouleurs+1;k++)
    {
        CouleursPrincipales[k]=Miroir[k];
    }
}

void ConversionTableauCouleursRGB(int CouleursPrincipales[NombreCouleurs+1], int CouleursPrincipalesRGB[NombreCouleurs+1])
{
    for(int n=0;n<NombreCouleurs+1;n++)
    {
        int R[NombreCouleurs+1],G[NombreCouleurs+1],B[NombreCouleurs+1];
        int deci[3];

        ConversionHexa(deci,CouleursPrincipales[n]);
        R[n]=deci[2];
        G[n]=deci[1];
        B[n]=deci[0];

        CouleursPrincipalesRGB[n]=R[n]+G[n]+B[n];
    }
}

void ConversionTableauCouleursGRIS(int CouleursPrincipales[NombreCouleurs+1], int CouleursPrincipalesRGB[NombreCouleurs+1])
{
    for(int n=0;n<NombreCouleurs+1;n++)
    {
        int R[NombreCouleurs+1],G[NombreCouleurs+1],B[NombreCouleurs+1];
        int deci[3];

        ConversionHexa(deci,CouleursPrincipales[n]);
        R[n]=deci[2];
        G[n]=deci[1];
        B[n]=deci[0];

        CouleursPrincipalesRGB[n]=int(float(R[n])*0.30+float(G[n])*0.59+float(B[n])*0.11);
    }
}

void DeterminePourcentagesCouleursPrincipales(int PourcentagesCouleurs[NombreCouleurs+1], int CouleursPrincipales[NombreCouleurs+1], int Palette[NombreCouleursPalette*NombreCouleursPalette*NombreCouleursPalette])
{
    int PixelsConcernes=0;

    for(int n=1;n<NombreCouleurs+1;n++)   //Calcul du nombre de pixels concernés (pixel dont la couleur est une des principales)
    {
        PixelsConcernes=PixelsConcernes+Palette[CouleursPrincipales[n]];
    }

    for(int n=1;n<NombreCouleurs+1;n++)   //Détermine l'importance relative de chacune des c
    {
        PourcentagesCouleurs[n]=int(float(Palette[CouleursPrincipales[n]])/float(PixelsConcernes)*100);
    }


    PourcentagesCouleurs[NombreCouleurs]=100;
    for(int n=1;n<NombreCouleurs;n++)     //Gestion de la dernière couleur pour avoir un total de 100%
    {
        PourcentagesCouleurs[NombreCouleurs]=PourcentagesCouleurs[NombreCouleurs]-PourcentagesCouleurs[n];
    }
}

void RepartitionpourColoriage(int TableauDebutColoriage[NombreCouleurs+1], int PourcentagesCouleurs[NombreCouleurs+1])
{
    for(int n=1;n<NombreCouleurs+1;n++)
    {
        for(int m=1;m<=n;m++)
        {
            TableauDebutColoriage[n]=TableauDebutColoriage[n-1]+PourcentagesCouleurs[m];
        }
    }

    for(int n=0;n<NombreCouleurs+1;n++)
    {
        TableauDebutColoriage[n]=100-TableauDebutColoriage[n];
    }
}

void RemplirTableauxFinaux(byte* &r, byte* &g, byte* &b, int compteur, int TableauDebutColoriage[NombreCouleurs+1], int CouleursPrincipales[NombreCouleurs+1], int w, int h)
{
    for(int n=1;n<NombreCouleurs+1;n++)
    {
        int R[NombreCouleurs+1],G[NombreCouleurs+1],B[NombreCouleurs+1];
        int deci[3];

        ConversionHexa(deci,CouleursPrincipales[n]);
        R[n]=deci[2];
        G[n]=deci[1];
        B[n]=deci[0];

        int j = compteur-1;

        for(int i=int(h*float(TableauDebutColoriage[n-1])/100.);i>int(h*float(TableauDebutColoriage[n])/100.);i--)
        {
            r[(i-1)*w+j]=R[n]*int(float(256)/float(NombreCouleursPalette));
            g[(i-1)*w+j]=G[n]*int(float(256)/float(NombreCouleursPalette));
            b[(i-1)*w+j]=B[n]*int(float(256)/float(NombreCouleursPalette));
        }


    }
}
