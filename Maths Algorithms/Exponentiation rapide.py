# -*- coding: utf-8 -*-
"""omega
Created on Thu Dec  7 16:21:19 2017

@author: charlie.pauvre
"""
import matplotlib.pyplot as plt
import numpy as np
import math as m

###################################################################
#calcul de x^n modulo N

def expo (x,n,N):
    
    if n==0:
        return 1
        
    A,B,C=n,x,1
    
    while A>1:
        if A%2==1:
            C=B*C%N
        
        B=B*B%N
        A=A//2
    
    return B*C%N
    
##################################################################

for n in range (15):
    print(n,expo(2,n,10**10))