# -*- coding: utf-8 -*-
"""
Created on Thu Dec  7 16:29:19 2017

@author: charlie.pauvre
"""

import matplotlib.pyplot as plt
import numpy as np
import math as m

###################################################
#Algo d'Euclide

def euclide(a,b):
    delta,r=abs(a),abs(b)
    
    while r!=0:
        delta,r=r,delta%r
    
    return delta

#Calcul de (2^2^n)+1
def Fermat (n):
    x=2
    for k in range (n):
        x=x*x
    
    return x+1
    
#####################################################

for n in range (10):
    
    print (n,Fermat(n))


for n in range (10):
    
    print(euclide(Fermat(n),Fermat(n+1))