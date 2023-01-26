# -*- coding: utf-8 -*-
"""
Created on Thu Oct 05 13:10:50 2017

@author: charlie.pauvre

Title : "Damier"
"""
"""
a=0
b=0

def multiplication(a,b):

    x = input ("Entrez deux nombres que vous voulez multiplier : "))
    
    a = x[0]
    b = x[1]
    
    return a*b

print (multiplication(a,b))

"""
"""
def equation(a,b,c): # on résout l'équation ax²+bx+c
    delta = b**2 -4*a*c
    
    if delta ==0:
        return [-b/2/a]
    elif delta > 0:
        return [(-b-sqrt(delta))/2/a,(-b+sqrt(delta))/2/a]
    else:
        return []

print (equation(1,2,1))
print (equation(1,3,2))
print (equation(1,1,1))


"""
from Tkinter import *

#########################################################################

def TracerUnCarre(couleur):
    global x,y,c
    Can1.create_rectangle(x,y,x+c,y+c,fill=couleur,outline='black')
    
#creation de l'environnement graphique

fen1=Tk()
Can1=Canvas(fen1,bg='yellow',height=200,width=200)
Can1.pack(side=LEFT)

# On crée des carrés

x,y,c=0,0,10

TracerUnCarre('red')
x+=10
y+=10
TracerUnCarre('blue')

#On affiche la figure

fen1.mainloop()






















