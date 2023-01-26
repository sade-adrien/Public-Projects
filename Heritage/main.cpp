#include "outils.h"
using namespace std;

int main()
{

//Différents tests en commentaires

//    float* co = new float[5];
//    for(int i=0; i<5; i++)
//        co[i]=i+1;

//    Polynome P(3,co);

//    Polynome* Pd = P.derivee();

//    cout << Pd->degre() << " " << Pd->operator()(1) << std::endl;

//    Affine a(5,9);
//    cout << a(10) << endl;

//    Affine* a_d=a.derivee();
//    cout << a_d->operator()(10) << endl;
//    cout << a_d.degre() << " " << a_d->degre() << endl;

//    Affine* a_dd=a_d->derivee();
//    cout << a_dd->operator()(10) << endl;
//    cout << a_dd->degre() << endl;

//    cout << a.inverse(2) <<  " "  << a_d->inverse(5)  << " " << a_dd->inverse(2);

//    Affine* a2=new Affine(2,3);
//    Derivee a2_d(a);
//    Fonction* a2_dd=a2_d.derivee();

//    cout << a2_d(8) << endl;
//    cout << a2_dd->derivee()->operator()(80) << endl;


    float* coeff = new float[4];
    for(int i=0; i<3; i++)
        coeff[i]=0;
    coeff[3]=1;

    Polynome P(3,coeff);
    Trigo tan("tan");

    cout << "27^1/3 = " << P.inverse(27) << endl;

    cout << "4*atan(1) = " << 4*tan.inverse(1) << endl;

    cout << "tan'(pi/4) = " << tan.derivee()->operator()(M_PI/4) << endl;

    cout << "tan''(pi/4) = " << tan.derivee()->derivee()->operator()(M_PI/4) << endl;


    return 0;
}
