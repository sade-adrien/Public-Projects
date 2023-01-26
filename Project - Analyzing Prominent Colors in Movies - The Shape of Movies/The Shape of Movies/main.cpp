#include "outils.h"



int main()
{
    int w=1920;
    int h=1040;
    int w2=6000;
    int h2=1800;

    openWindow(w,h);

    byte* Rsortie = new byte[w2*h2];
    byte* Gsortie = new byte[w2*h2];
    byte* Bsortie = new byte[w2*h2];

for(int p=1;p<6001;p+=1){

    int Palette[NombreCouleursPalette*NombreCouleursPalette*NombreCouleursPalette]={0};
    int CouleursPrincipales[NombreCouleurs+1]={0};       //+1 car on garde un 0 en premier terme
    int CouleursPrincipalesRGB[NombreCouleurs+1]={0};
    int PourcentagesCouleurs[NombreCouleurs+1]={0};
    int TableauDebutColoriage[NombreCouleurs+1]={0};

    byte* r = new byte[w*h];
    byte* g = new byte[w*h];
    byte* b = new byte[w*h];

    string name = "//Titanic//00";
    string image= to_string(p);
    string extension = ".jpg";

    if(p<10)
        name = name + "000";
    else if(p>=10 && p<100)
        name = name + "00";
    else if(p>=100 && p<1000)
        name=name + "0";

    ChargerImage(name+image+extension,r,g,b,w,h);

    cout << name+image+extension << endl;

    AfficherImage(r,g,b,w,h);

    PaletteDiscretiseedeCouleurs(Palette,r,g,b,w,h);

    DetermineCouleursPrincipales(Palette,CouleursPrincipales);


/* **********Gestion du rangement des couleurs par clarté********** */

    ConversionTableauCouleursRGB(CouleursPrincipales,CouleursPrincipalesRGB);
//    ConversionTableauCouleursGRIS(CouleursPrincipales,CouleursPrincipalesRGB);

/* ************************************************************* */


    ordonnerTableau(CouleursPrincipalesRGB,CouleursPrincipales, NombreCouleurs+1);

    DeterminePourcentagesCouleursPrincipales(PourcentagesCouleurs,CouleursPrincipales,Palette);

    RepartitionpourColoriage(TableauDebutColoriage,PourcentagesCouleurs);

    RemplirTableauxFinaux(Rsortie,Gsortie,Bsortie,p,TableauDebutColoriage,CouleursPrincipales,w2,h2);


    DetruireTableau(r);
    DetruireTableau(g);
    DetruireTableau(b);

}

//    AfficherImage(Rsortie,Gsortie,Bsortie,w,h);
    saveColorImage("Spirited Away.png",Rsortie,Gsortie,Bsortie,w2,h2);

    endGraphics();

    DetruireTableau(Rsortie);
    DetruireTableau(Gsortie);
    DetruireTableau(Bsortie);

    return 0;

}
