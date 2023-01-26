#include "outils.h"

Eleve::Eleve(std::string chaine, int entier) {
    name=chaine;
    grade=entier;
}

void Eleve::Print(){
    std::cout << name << " received a " << grade << std::endl;
}

std::string name_generator(){

    char first_letter = (char) (rand() % 26 + 65);
    std::string name(1,first_letter);

    int name_length = rand() % 10 + 1;

    for(int i=0; i<name_length; i++)
        name += (char) (rand() % 26 + 97);

    return name;
}

