#include "outils.h"
using namespace std;


bool test(Eleve i, Eleve j){
    for(int k=0; k<i.name.size(); k++)
    {
        if(int(i.name.at(k)) < int(j.name.at(k)))
            return true;
        else if(int(i.name.at(k)) > int(j.name.at(k)))
            return false;
    }
    if(i.name.size() <= j.name.size())
        return true;
    return false;
}



int main()
{
    int nbr_eleve = 30;
    std::vector<Eleve> Class;
    int compteur=0;
    int compteur2=0;
    srand((unsigned int)time(NULL));

    std::cout << "**************Unordered**************" << std::endl;
    for(int i=0; i<nbr_eleve; i++){
        Eleve new_student(name_generator(), rand() % 20 + 0);
        Class.push_back(new_student);
    }
    for(int i=0; i<nbr_eleve; i++){
        Class.at(i).Print();
    }

    std::cout << "" << std::endl;
    std::cout << "**************Ordered by grades**************" << std::endl;
    CompareGrade cmp;
    cmp.ptr=&compteur;
    std::sort(Class.begin(), Class.end(), cmp);
    for(int i=0; i<nbr_eleve; i++){
        Class.at(i).Print();
    }
    cout << "Nombre de comparaisons: " << compteur << endl;

    std::cout << "" << std::endl;
    std::cout << "**************Ordered by names**************" << std::endl;
    CompareName cmp2;
    cmp2.ptr=&compteur2;
    std::sort(Class.begin(), Class.end(), cmp2);
    for(int i=0; i<nbr_eleve; i++){
        Class.at(i).Print();
    }
    cout << "Nombre de comparaisons: " << compteur2 << endl;





    return 0;
}
