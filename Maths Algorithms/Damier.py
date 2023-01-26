# -*- coding: utf-8 -*-
"""
Created on Thu Oct 05 13:10:50 2017

@author: charlie.pauvre

Title : "Damier"
"""

from Tkinter import *

#########################################################################

def TracerUnCarre(n):
    global x,y,c
    if n%2==0:
        couleur='black'
    else:
        couleur='white'
    Can1.create_rectangle(x,y,x+c,y+c,fill=couleur,outline=couleur)
    
#creation de l'environnement graphique

fen1=Tk()
Can1=Canvas(fen1,bg='yellow',height=120,width=120)
Can1.pack(side=LEFT)

# On crée des carrés

x,y,c=10,10,10

for k in range (10):
    
    for i in range (10):
        
        TracerUnCarre(k+i)
        x+=10
            
    x=10
    y+=10
 

#On affiche la figure

fen1.mainloop()















