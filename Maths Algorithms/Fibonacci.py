# -*- coding: utf-8 -*-
"""
Created on Thu Dec  7 16:59:32 2017

@author: charlie.pauvre
"""

import matplotlib.pyplot as plt
import numpy as np
import math as m

def Fibonacci(n):
    if n==0:
        return 0
    if n==1:
        return 1
    F,G=0,1
    for k in range (n-1):
        F,G=G,F+G
    return G

for n in range (20):
    a=Fibonacci(n)
    b=Fibonacci(n+1)
    L=euclideetendu(a,b)
    print(n,L[0],L[3])