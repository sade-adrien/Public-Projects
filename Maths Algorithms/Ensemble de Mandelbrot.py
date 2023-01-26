# -*- coding: utf-8 -*-
"""
Created on Thu Nov 09 13:55:01 2017

@author: charlie.pauvre

Ensemble de Mandelbrot
"""
from Tkinter import *
from math import *

##########################################################################

def TracerUnCarre(n):
    global x,y,c
    if toto(alpha)==100:
        couleur='black'
    else:
        couleur='yellow'
    Can1.create_rectangle(x,y,x+c,y+c,fill=couleur,outline=couleur)

##########################################################################

App=False

def toto(alpha):
    n=0
    z=0
    while abs(z)<2 and n<100:
        z=z*z+alpha
        n=n+1
    return n

##########################################################################

#creation de l'environnement graphique

fen1=Tk()
Can1=Canvas(fen1,bg='white',height=1000,width=1000)
Can1.pack(side=LEFT)

#######################################################################

x=0
y=0
c=1

for x in range (501):
    for y in range (501):
        
        alpha=complex(float((x-250)),float(y-250))/12
        print(alpha)
        TracerUnCarre(alpha)

#######################################################################
 
#On affiche la figure

fen1.mainloop()
