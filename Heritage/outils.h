#pragma once

#include <iostream>
#include <math.h>
#include <cmath>

//Remarque: degré du polynome nul pris égal à -1

class Fonction {
public:
    virtual float operator()(float) const = 0;
    virtual Fonction* derivee() const = 0;
    float inverse(float y) const;
    virtual Fonction* clone() const=0;
    virtual ~Fonction() {};
};

class Polynome: public Fonction {
    int deg;
    float* coef;

protected:
    Polynome(float a, float b): Fonction() {
        if(a==0 && b==0) deg=-1;
        else if(a==0) {deg=0; coef=new float[1]; coef[0]=b;}
        else {
            deg=1;
            coef=new float[2];
            coef[0]=b;
            coef[1]=a;
        }
    }
public:
    Polynome(int degre=-1): Fonction() {deg=degre;}
    Polynome(int degre, float coefficient[]): Fonction() {
        coef=new float[degre+1];

        for(int d=0;d<=degre;d++)
            coef[d]=coefficient[d];

        deg = degre;

        if(degre!=-1 && coef[degre]==0)
        {
            std::cerr << "Warning, the last coefficient of the polynomial is null, then the degrees of the polynomial is <P.deg" << std::endl;

            while(coef[degre]==0 && degre>-1)
                degre--;

            deg=degre;
        }
    }
    int degre() const {return deg;}
    virtual float operator()(float x) const {
        if(deg==-1) return 0;
        float X=coef[0];
        for(int d=1;d<=deg;d++)
            X += coef[d]*pow(x,d);
        return X;
    }
    virtual Polynome* derivee() const {
        if(deg==0 || deg==-1) return new Polynome(-1);

        float* coefficient = new float[deg];
        for(int d=1;d<=deg;d++)
            coefficient[d-1]=coef[d]*d;
        return new Polynome(deg-1,coefficient);

    }
    virtual ~Polynome() {delete [] coef;}
    virtual Fonction* clone() const {return new Polynome(*this);}
};

class Affine: public Polynome {
    float a,b;
public:
    Affine(float mult, float add): Polynome(mult,add) {a=mult;b=add;}
    float operator()(float x) const{return a*x+b;}
    Affine* derivee() const{return new Affine(0,a);}
    ~Affine() {}
    Fonction* clone() const {return new Affine(*this);}
};

class Derivee: public Fonction {
    Fonction* integrale;
public:
    Derivee(Fonction* f) {integrale=f->clone();}
    ~Derivee() {delete integrale;}
    virtual Fonction* derivee() const {return new Derivee(this->clone());}
    float operator()(float x) const {
        float epsilon=1e-2;
        return 1/(2*epsilon)*(integrale->operator()(x+epsilon)-integrale->operator()(x-epsilon));
    }
    Fonction* clone() const {return new Derivee(*this);}
};

class Trigo: public Fonction {
    std::string fct;
public:
    Trigo(std::string name): Fonction() {
        if(!name.compare("cos") || !name.compare("sin") || !name.compare("tan"))
            fct=name;
        else {
            std::cerr << "Warning, unknown Trigo function" << std::endl;
        }
    }
    float operator()(float x) const{
        if(!fct.compare("sin")) return sin(x);
        else if(!fct.compare("cos")) return cos(x);
        else if(!fct.compare("tan")) return tan(x);
        else{
            std::cerr << "Warning, unknown Trigo function" << std::endl;
            return 0;
        }
    }
    Fonction* clone() const {return new Trigo(*this);}
    Derivee* derivee() const{return new Derivee(this->clone());}
    ~Trigo() {}
};




float Fonction::inverse(float y) const{
    int iterations=0;
    float diff = 1;
    float x_1 = 1; float x_2 = 1;

    while(diff>1e-5 && iterations<100)
    {
        iterations++;

        x_1=x_2;
        x_2 = x_1 + (y-operator()(x_1))/(derivee()->operator()(x_1));
        diff=abs(x_2-x_1);
    }

    return x_2;
}

