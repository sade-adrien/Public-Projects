# -*- coding: utf-8 -*-
"""
Created on Thu Nov 09 13:39:56 2017

@author: charlie.pauvre

Nombres Premiers
"""

from math import sqrt

def NombresPremiers(k):
    ListeNP=[]
    Premier=False
    
    for n in range (k):
        m=sqrt(n)
        for i in range (2,int(m)):
            while n%i!=0:
                
        ListeNP.append(n)
    print(ListeNP)
    
NombresPremiers(100)