# -*- coding: utf-8 -*-
"""
Created on Thu Oct 12 16:07:46 2017

@author: charlie.pauvre
"""


from Tkinter import *

#########################################################################

def TracerUnCarre(n):
    global x,y,c
    if n in PetitsNombresPremiers:
        couleur='black'
    elif n==1:
        couleur='red'
    else:
        couleur='yellow'
    Can1.create_rectangle(x,y,x+c,y+c,fill=couleur,outline=couleur)
    
PetitsNombresPremiers=[2,3,5,7,11,13,17,19]

def EstPremier(n):
    #convient si 2<=n<=100
    if n in PetitsNombresPremiers:
        return True
    for x in PetitsNombresPremiers:
        if n%x==0:
            return False
    return True

 
PetitsNombresPremiers = [n for n in range (2,400) if EstPremier(n)==True]

#################################################
    


        
########################################################################
#creation de l'environnement graphique

fen1=Tk()
Can1=Canvas(fen1,bg='white',height=2000,width=2000)
Can1.pack(side=LEFT)

#######################################################################

#creation
x=100
y=100
c=10
n=1


for k in range (1,100):

    for j in range (2*k-1):  #Droite
        TracerUnCarre(n)
        n=n+1
        x+=c
    for j in range (2*k-1): #haut
        TracerUnCarre(n)
        n=n+1
        y+=-c
    for l in range (2*k):   #gauche
        TracerUnCarre(n)
        n=n+1
        x+=-c
    for m in range (2*k):  #bas
        TracerUnCarre(n)
        n=n+1
        y+=c

#######################################################################
 
#On affiche la figure

fen1.mainloop()





