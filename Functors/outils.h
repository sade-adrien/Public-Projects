#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

class Eleve{
public:
    std::string name;
    int grade;
    Eleve(std::string chaine, int entier);
    void Print();

};

class CompareGrade {
public:
    int* ptr;
    bool operator()(Eleve i, Eleve j){++*ptr; return i.grade<j.grade;}
};

class CompareName {
public:
    int* ptr;
    bool operator()(Eleve i, Eleve j){
        ++*ptr;
        return i.name<j.name;
    }
};


std::string name_generator();
