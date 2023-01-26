//L'affichage des modifs élémentaires est seulement programmé pour la méthode itérative: on modifie la chaine 1.
//Remarque: en l'état, pour la distance de damerau, on ne peut faire de distinction entre la substitution et
//la transposition lors de la recherche de la suite des modifs élémentaires. Cependant, il suffirait de modifier
//le poids de la transposition en la choisissant entre 0 et 1 strictement (ex:0.5), et on pourrait alors les distinguer.

#include <iostream>
#include "outils.h"
#include "vector"
#include <time.h>

using namespace std;

vector<vector <int>> memo;

int distance_levenshtein_recursive(string s1, string s2, bool memoisation, bool damerau){
    int length_s1 = s1.size();
    int length_s2 = s2.size();
    int cout;

    if(length_s1==0 || length_s2==0)
        return max(length_s1,length_s2);

    if(s1.at(0)==s2.at(0))
        cout = 0;
    else
        cout=1;


    if(!memoisation){
        int d_L1 = 1+distance_levenshtein_recursive(s1.substr(1,length_s1-1),s2,memoisation,damerau);
        int d_L2 = 1+distance_levenshtein_recursive(s1,s2.substr(1,length_s2-1),memoisation,damerau);
        int d_L3 = cout+distance_levenshtein_recursive(s1.substr(1,length_s1-1),s2.substr(1,length_s2-1),memoisation,damerau);

        int temp = min(min(d_L1,d_L2),d_L3);

        if(damerau)
        {
            if(length_s1>1 && length_s2>1 && s1.at(1)==s2.at(0) && s1.at(0)==s2.at(1))
            {
                int d_L4 = cout+distance_levenshtein_recursive(s1.substr(2,length_s1-2),s2.substr(2,length_s2-2),memoisation,damerau);

                temp = min(temp,d_L4);
            }
        }

        return temp;
    }



    for(int i=0;i<memo.size();i++){
        if((length_s1==memo.at(i).at(0) && length_s2==memo.at(i).at(1)) || (length_s1==memo.at(i).at(1) && length_s2==memo.at(i).at(0)))
            return memo.at(i).at(2);
    }

    if(length_s1==0)
    {
        vector<int> v;
        v.push_back(length_s1);
        v.push_back(length_s2);
        v.push_back(length_s2);
        memo.push_back(v);
        return length_s2;
    }

    if(length_s2==0)
    {
        vector<int> v;
        v.push_back(length_s1);
        v.push_back(length_s2);
        v.push_back(length_s1);
        memo.push_back(v);
        return length_s1;
    }

    if(s1.at(length_s1-1)==s2.at(length_s2-1))
    {
        vector<int> v;
        v.push_back(length_s1);
        v.push_back(length_s2);
        int temp=distance_levenshtein_recursive(s1.substr(0,length_s1-1),s2.substr(0,length_s2-1),memoisation,damerau);
        v.push_back(temp);
        memo.push_back(v);
        return temp;
    }

    vector<int> v;
    v.push_back(length_s1);
    v.push_back(length_s2);

    int d_L1 = 1+distance_levenshtein_recursive(s1.substr(1,length_s1-1),s2,memoisation,damerau);
    int d_L2 = 1+distance_levenshtein_recursive(s1,s2.substr(1,length_s2-1),memoisation,damerau);
    int d_L3 = cout+distance_levenshtein_recursive(s1.substr(1,length_s1-1),s2.substr(1,length_s2-1),memoisation,damerau);

    int temp = min(min(d_L1,d_L2),d_L3);

    if(damerau)
    {
        if(length_s1>1 && length_s2>1 && s1.at(1)==s2.at(0) && s1.at(0)==s2.at(1))
        {
            int d_L4 = cout+distance_levenshtein_recursive(s1.substr(2,length_s1-2),s2.substr(2,length_s2-2),memoisation,damerau);

            temp = min(temp,d_L4);
        }
    }


    v.push_back(temp);
    memo.push_back(v);

    return temp;

}

int distance_levenshtein_iterative(string s1, string s2,bool damerau){
    int length_s1 = s1.size();
    int length_s2 = s2.size();

    if(length_s1==0 || length_s2==0)
        return max(length_s1,length_s2);

    int *tableau = new int [(length_s1+1)*(length_s2+1)];

    for(int i=0;i<length_s1+1;i++)
    {
        for(int j=0;j<length_s2+1;j++)
        {
            if(i==0)
                tableau[i+j*(length_s1+1)]=j;
            else if(j==0)
                tableau[i+j*(length_s1+1)]=i;
            else{
                tableau[i+j*(length_s1+1)]=0;
                if(s1.at(i-1)!=s2.at(j-1))
                    tableau[i+j*(length_s1+1)]=1;
            }
        }
    }

    for(int i=1;i<length_s1+1;i++)
    {
        for(int j=1;j<length_s2+1;j++)
        {
            int cout=1;
            if(s1.at(i-1)==s2.at(j-1)) {cout=0;}
            tableau[i+j*(length_s1+1)] = min(min(tableau[i-1+j*(length_s1+1)]+1,tableau[i+(j-1)*(length_s1+1)]+1),tableau[i-1+(j-1)*(length_s1+1)]+cout);

            if(damerau)
            {
                if(i>1 && j>1 && s1.at(i-1)==s2.at(j-2) && s1.at(i-2)==s2.at(j-1))
                {
                    tableau[i+j*(length_s1+1)] = min(tableau[i+j*(length_s1+1)],cout+tableau[i-2+(j-2)*(length_s1+1)]);

                }
            }
        }
    }




    int d_L = tableau[(length_s1+1)*(length_s2+1)-1];


    //Affichage de la suite de modifs élémentaires
    if(!damerau)
        cout << "Modifications élémentaires pour distance de Levenshtein:" << endl;
    else
        cout << "Modifications élémentaires pour distance de Damerau-Levenshtein:" << endl;
    int *suite_i = new int [(length_s1+1)*(length_s2+1)];
    int *suite_j = new int [(length_s1+1)*(length_s2+1)];
    suite_i[0]=length_s1;
    suite_j[0]=length_s2;
    int k = 1;
    int i = length_s1;
    int j = length_s2;
    while(i!=0 || j!=0)
    {
        if(i==0 || tableau[i+(j-1)*(length_s1+1)]==tableau[i+j*(length_s1+1)]-1){
            j--;

        }
        else if(j==0 || tableau[i-1+j*(length_s1+1)]==tableau[i+j*(length_s1+1)]-1)
            i--;
        else{
            i--;
            j--;
        }
        suite_i[k]=i;
        suite_j[k]=j;

        k++;
    }

    for(int l=k-1;l>=0;l--){
        if(suite_i[l-1]==suite_i[l]+1 && suite_j[l-1]==suite_j[l]+1)
        {
            if(damerau && tableau[suite_i[l-1]+suite_j[l-1]*(length_s1+1)]==tableau[suite_i[l]+suite_j[l]*(length_s1+1)]+1)
                cout << "on substitue ou transpose (?) " << s1.at(suite_i[l-1]-1) << " avec " << s2.at(suite_j[l-1]-1) << endl;

            else if(tableau[suite_i[l-1]+suite_j[l-1]*(length_s1+1)]==tableau[suite_i[l]+suite_j[l]*(length_s1+1)]+1)
                cout << "on substitue " << s1.at(suite_i[l-1]-1) << " avec " << s2.at(suite_j[l-1]-1) << endl;
        }

        else if(suite_i[l-1]==suite_i[l]+1 && suite_j[l-1]==suite_j[l])
            cout << "on supprime " << s1.at(suite_i[l-1]-1) << endl;

        else if(suite_i[l-1]==suite_i[l] && suite_j[l-1]==suite_j[l]+1)
            cout << "on ajoute " << s2.at(suite_j[l-1]-1) << endl;
    }

    cout << "-------------------------------------------" << endl;

    delete [] tableau;
    delete [] suite_i;
    delete [] suite_j;

    return d_L;


}

int main()
{
    string s1="daccord";
    string s2="accrod";

    clock_t tdlr_debut = clock();
    int dlr=distance_levenshtein_recursive(s1,s2,false,false);
    clock_t tdlr_fin = clock();

    clock_t tdlrm_debut = clock();
    int dlrm=distance_levenshtein_recursive(s1,s2,true,false);
    clock_t tdlrm_fin = clock();

    clock_t tdli_debut = clock();
    int dli=distance_levenshtein_iterative(s1,s2,false);
    clock_t tdli_fin = clock();

    memo.clear();

    clock_t tddlr_debut = clock();
    int ddlr=distance_levenshtein_recursive(s1,s2,false,true);
    clock_t tddlr_fin = clock();

    clock_t tddlrm_debut = clock();
    int ddlrm=distance_levenshtein_recursive(s1,s2,true,true);
    clock_t tddlrm_fin = clock();

    clock_t tddli_debut = clock();
    int ddli=distance_levenshtein_iterative(s1,s2,true);
    clock_t tddli_fin = clock();



    cout << "distance_levenshtein_recursive=" << dlr << " time=" << (tdlr_fin-tdlr_debut)/float(CLOCKS_PER_SEC) << endl;
    cout << "distance_levenshtein_recursive_memoization=" << dlrm << " time=" << (tdlrm_fin-tdlrm_debut)/float(CLOCKS_PER_SEC) << endl;
    cout << "distance_levenshtein_iterative=" << dli << " time=" << (tdli_fin-tdli_debut)/float(CLOCKS_PER_SEC) << endl;
    cout << "distance_damerau_levenshtein_recursive=" << ddlr << " time=" << (tddlr_fin-tddlr_debut)/float(CLOCKS_PER_SEC) << endl;
    cout << "distance_damerau_levenshtein_recursive_memoization=" << ddlrm << " time=" << (tddlrm_fin-tddlrm_debut)/float(CLOCKS_PER_SEC) << endl;
    cout << "distance_damerau_levenshtein_iterative=" << ddli << " time=" << (tddli_fin-tddli_debut)/float(CLOCKS_PER_SEC) << endl;




    return 0;
}
