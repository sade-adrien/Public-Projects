#include "inttree.h"

//Exercice 1.1
IntTree::IntTree(int d) {
    data = d;
}

IntTree::~IntTree() {
    for(int i=0; i<sons.size(); i++)
        delete [] sons[i];
}

int IntTree::getData() const {
    return data;
}

void IntTree::setData(int d) {
    data = d;
}

int IntTree::nbSons() const {
    return sons.size();
}

void IntTree::setSon(int pos, IntTree* newSon) //Throw d'erreur pour pos out_of_range de sons
{
    if(pos<0 || pos>=sons.size()) throw std::out_of_range("");
    sons.at(pos) = newSon;
}

IntTree* IntTree::getSon(int pos) //Throw d'erreur pour pos out_of_range de sons
{
    if(pos<0 || pos>=sons.size()) throw std::out_of_range("");
    return sons.at(pos);
}

const IntTree* IntTree::getSon(int pos) const //Throw d'erreur pour pos out_of_range de sons
{
    if(pos<0 || pos>=sons.size()) throw std::out_of_range("");
    return sons.at(pos);
}

void IntTree::addAsLastSon(IntTree* newSon) {
    int s = sons.size();
    sons.resize(s+1);
    setSon(s, newSon);
}

void IntTree::removeLastSon() {
    sons.pop_back();
}

//*********************************************************************

//Exercice 2.2
void IntTree::display() {
    std::cout << data << " ";
    for(int i=0; i<sons.size(); i++)
        sons.at(i)->display();
}
//Exercice 2.3
void IntTree::display2(std::string prefix, std::string indent) {
    std::cout << prefix << indent << data << "\n";
    indent += "   ";
    for(int i=0; i<sons.size(); i++)
        sons.at(i)->display2(prefix,indent);
}






