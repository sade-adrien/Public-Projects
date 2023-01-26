# -*- coding: utf-8 -*-
"""
Created on Thu Oct 05 14:30:29 2017

@author: charlie.pauvre

Title : "Triangle de Pascal"
"""

from Tkinter import *

#########################################################################

def TracerUnCarre(n):
    global x,y,c
    if n%2==0:
        couleur='black'
    else:
        couleur='#e6c475'
    Can1.create_rectangle(x,y,x+c,y+c,fill=couleur,outline=couleur)
    
def Fact(n):
    P=1
    for k in range (n):
        P=P*(k+1)
    return P


def CoefficientBinomial (k,n): 
    
    if k>n:
        return 0
    
    else:
        return Fact(n)//Fact(k)//Fact(n-k)
    
for n in range (20):
    print ([CoefficientBinomial(k,n) for k in range (n+1)])
    
########################################################################

#creation de l'environnement graphique

fen1=Tk()
Can1=Canvas(fen1,bg='white',height=2000,width=2000)
Can1.pack(side=LEFT)

#######################################################################

# On crée le triangle de pascal

x,y,c=10,10,2

for n in range (256):
    for k in range (n+1):
        CoefficientBinomial(k,n) 
        TracerUnCarre(CoefficientBinomial(k,n))
        x+=2
    x=10
    y+=2

 
#######################################################################
 
#On affiche la figure

fen1.mainloop()














