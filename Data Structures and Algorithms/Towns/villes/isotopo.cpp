#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>
#include <set>
#include <math.h>

#include "town.h"

using namespace std;

#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
const string townFile = srcPath "/villes.txt";



string histogramme_graphisme(int* pointeur_tbl, int N, int k)
{
    int total = 0;
    string histo;
    for(int i=0; i<=N; i++)
        total += *(pointeur_tbl+i);
    for(int j=0; j<round(*(pointeur_tbl+k)*100/total); j++)
    {
        histo += "|";
    }

    return histo;
}



// Study French isotoponyms
int main() {
    vector<Town> towns;
    // Read file
    cout << "Reading town file: " << townFile << endl;
    clock_t time1 = clock();
    int nb_towns = Town::read_file(townFile, towns);
    clock_t time2 = clock();
    // Sanity check
    if (nb_towns < 0) {
        cout << "Error while reading file" << endl;
        return 2;
    }
    if (nb_towns == 0) {
        cout << "No town found" << endl;
        return 1;
    }

    srand(time(NULL));
    // Say how many towns have been read
    cout << "File read in: "
         << ((float)(time2-time1)/CLOCKS_PER_SEC) << " s" << endl;
    cout << "Number of towns in file: "
         << towns.size() /* same as nb_towns */ << endl;
    cout << "A random town, using format \"name[lat,lon](x,y)\": "
         << towns[rand() % towns.size()] << endl;

    // That's all folks



    //******************************** Q1 **************************************//


//    map<std::string, int> tbl_asso;
//    int* hist = new int [towns.size()];

//    for(auto it=towns.begin(); it!=towns.end(); ++it)
//    {
//        tbl_asso.insert(std::pair<std::string, int>(it->name(),towns_with_name(towns,it->name()).size()));
//    }

//    for(int i=0; i<towns.size(); i++)
//        hist[i]=0;

//    int max=0;

//    for(auto it=tbl_asso.begin(); it!=tbl_asso.end(); ++it)
//    {
//        hist[it->second] ++;
//        if(it->second>max)
//            max=it->second;
//    }

//    cout << "Histogramme Q1:" << endl;

//    for(int i=1; i<=max; i++)
//        cout << i << " villes exactement: " << histogramme_graphisme(hist,max,i) << hist[i] << " noms de villes" << endl;


//    delete [] hist;




    //******************************** Q2 **************************************//
    //Remarque: pour gagner du temps lors de l'execution il faudrait regrouper les 2 codes et boucles
    //Ici on garde ce schéma pour bien distinguer les 2 questions

//    map<Point2D, int> tbl_asso2;
//    int* hist2 = new int [towns.size()];

//    for(auto it=towns.begin(); it!=towns.end(); ++it)
//    {
//        Point2D coord(it->lat(), it->lon());
//        tbl_asso2.insert(std::pair<Point2D, int>(coord,towns_with_lat_lon(towns,coord.x,coord.y).size()));
//    }

//    for(int i=0; i<towns.size(); i++)
//        hist2[i]=0;

//    int max2=0;

//    for(auto it=tbl_asso2.begin(); it!=tbl_asso2.end(); ++it)
//    {
//        hist2[it->second] ++;
//        if(it->second>max2)
//            max2=it->second;
//    }

//    cout << "Histogramme Q2:" << endl;

//    for(int i=1; i<=max2; i++)
//        cout << i << " villes exactement: " << histogramme_graphisme(hist2,max2,i) << hist2[i] << " coordonnées similaires" << endl;


//    delete [] hist2;




    //******************************** Q3 **************************************//

    set<Town> N;
    set<Town> C;

    for(auto it=towns.begin(); it<towns.end(); ++it)
    {
        vector<Town> same_name = towns_with_name(towns,it->name());
        if(same_name.size()>1)
        {
            for(auto sous_it=same_name.begin(); sous_it<same_name.end(); ++sous_it)
            {
                N.insert(*sous_it);
            }
        }

        Point2D coord(it->lat(), it->lon());
        vector<Town> same_coord = towns_with_lat_lon(towns,coord.x,coord.y);
        if(same_coord.size()>1)
        {
            for(auto sous_it=same_coord.begin(); sous_it<same_coord.end(); ++sous_it)
            {
                C.insert(*sous_it);
            }
        }
    }

    vector<Town> NinterC(min(N.size(),C.size()));
    vector<Town>::iterator end = set_intersection(N.begin(),N.end(),C.begin(),C.end(),NinterC.begin());
    NinterC.resize(end - NinterC.begin());

    cout << "\nLe cardinal de NinterC est = " << NinterC.size() << endl;

    cout << "Ces villes sont:" << endl;
    for(auto it=NinterC.begin(); it<NinterC.end(); ++it)
        cout << *it << endl;




    //******************************** Q4 **************************************//

    int nb_villes_erreur_possible = 0;
    int compteur_egalites = 0;
    clock_t t1 = clock();

    for(auto it=NinterC.begin(); it<NinterC.end(); ++it)
    {
        Town v1 = *it;
        vector<Town> same_coord_as_v1 = towns_with_lat_lon(NinterC,v1.lat(),v1.lon());


        for(auto it2=same_coord_as_v1.begin(); it2<same_coord_as_v1.end(); ++it2)
        {
            Town v2 = *it2;
            vector<Town> same_name_as_v1 = towns_with_name(NinterC,v1.name());


            for(auto it3=same_name_as_v1.begin(); it3<same_name_as_v1.end(); ++it3)
            {
                Town v3 = *it3;
                vector<Town> same_name_as_v2 = towns_with_name(NinterC,v2.name());
                vector<Town> same_coord_as_v3 = towns_with_lat_lon(NinterC,v3.lat(),v3.lon());

                for(auto it4=same_name_as_v2.begin(); it4<same_name_as_v2.end(); ++it4)
                {
                    Town v4 = *it4;

                    for(auto it5=same_coord_as_v3.begin(); it5<same_coord_as_v3.end(); ++it5)
                    {
                        Town v5 = *it5;

                        if((v4==v5) && !(v2==v3) && !(v2==v4) && !(v3==v4))
                        {
                            nb_villes_erreur_possible ++;
                        }
                        compteur_egalites ++;
                    }
                }
            }
        }
    }

    clock_t t2 = clock();

    cout << "\nEn France, on peut se tromper de ville si on dit 'A est toute proche de B' pour " << nb_villes_erreur_possible << " villes." << endl;




    //******************************** Q5 **************************************//
    //On reprend le cas précédent et on l'applique à la méthode naïve.

    int nb_villes_erreur_possible_naif = 0;
    int compteur_egalites_naif = 0;
    clock_t t3 = clock();

    for(auto it=towns.begin(); it<towns.end(); ++it)
    {
        Town v1 = *it;

        for(auto it2=towns.begin(); it2<towns.end(); ++it2)
        {
            Town v2 = *it2;

            if(!(v1==v2) && v1.lat()==v2.lat() && v1.lon()==v2.lon())
            {
            for(auto it3=towns.begin(); it3<towns.end(); ++it3)
            {
                Town v3 = *it3;

                if(!(v1==v3) && !(v2==v3) && v1.name()==v3.name())
                {
                for(auto it4=towns.begin(); it4<towns.end(); ++it4)
                {
                    Town v4 = *it4;


                        if(!(v1==v4) && !(v2==v4) && !(v3==v4) && v4.name()==v2.name() && v3.lat()==v4.lat() && v3.lon()==v4.lon())
                        {
                            nb_villes_erreur_possible_naif ++;
                        }

                        compteur_egalites_naif ++;

                }
                }
            }
            }
        }
    }

    clock_t t4 = clock();

    assert(nb_villes_erreur_possible==nb_villes_erreur_possible_naif);

    cout << "La méthode naïve élaguée considère " << compteur_egalites_naif << " cas en DeltaT= " << (t4-t3)/float(CLOCKS_PER_SEC) <<". Notre méthode considère " << compteur_egalites << " cas en DeltaT=" << (t2-t1)/float(CLOCKS_PER_SEC) << endl;
    cout << "Le gain de temps est d'un facteur multiplicatif = " << (t4-t3)/(t2-t1) << endl;


    return 0;
}
