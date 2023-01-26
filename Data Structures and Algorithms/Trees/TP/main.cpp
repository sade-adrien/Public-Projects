#include "inttree.h"

using namespace std;

int main()
{
    //Exercice 1.2:

    IntTree* root = new IntTree(12);
    root->addAsLastSon(new IntTree(8));
    root->getSon(0)->addAsLastSon(new IntTree(4));
    root->getSon(0)->addAsLastSon(new IntTree(9));
    root->addAsLastSon(new IntTree(23));
    root->getSon(1)->addAsLastSon(new IntTree(17));
    root->getSon(1)->getSon(0)->addAsLastSon(new IntTree(15));


    //Exercice 2.2
    root->display();
    //Exercice 2.3
    cout << "\n";
    root->display2("*");


    //Exercice 3.7: tests d'erreurs
    IntTree* root2 = new IntTree(100);
    const IntTree* root3 = new IntTree(1000);

    try {
        root->setSon(root->nbSons(),root2);
    }
    catch(std::out_of_range &exn) {
        std::cerr << "error, out_of_range" << std::endl;
    }
    try {
        root->getSon(root->nbSons());
    }
    catch(std::out_of_range &exn) {
        std::cerr << "error, out_of_range" << std::endl;
    }
    try {
        root3->getSon(root3->nbSons());
    }
    catch(std::out_of_range &exn) {
        std::cerr << "error, out_of_range" << std::endl;
    }





    return 0;


}
