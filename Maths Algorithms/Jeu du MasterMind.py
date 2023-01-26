# -*- coding: utf-8 -*-
"""
Created on Thu Sep 14 13:54:56 2017

@author: adrien.sade

Jeu du MasterMind
"""

import random

###################################################################
#################### Création d'une configuration cachée ##########
###################################################################
Rejouer = True

while Rejouer == True:
    
    a = random.randint(1,8)
    b = random.randint(1,8)
    while b == a:
        b = random.randint(1,8)
        
    c = random.randint(1,8)
    while c == a or c ==b:
        c = random.randint(1,8)
                
    d = random.randint(1,8)
    while d == a or d == b or d == c:
        d = random.randint(1,8)
                
    ConfigurationCachee = [a,b,c,d]      #ConfigurationCachee est une liste

#####################################################################
##########################Initialisation#############################
#####################################################################

    NombreDeCoups = 0
    PartieGagnee = False         #PartieGagnee est un booléen
    PartieFinie = False          #PartieFinie est un booléen

#####################################################################
#########################Deroulement du Jeu##########################
#####################################################################

    while PartieFinie == False and PartieGagnee == False:
        NombreDeCoups +=1
        x = input("Propose un nombre de 4 chiffres distincts entre 1 et 8: ")
        ConfigurationProposee = [int(x[0]), int(x[1]), int(x[2]), int(x[3])]                #la fonction int permet de transformer le type str en integer
        NbBienPlaces, NbMalPlaces = 0,0
    
        for k in range (4):             #k variant de 0 à 3
            if ConfigurationCachee[k] == ConfigurationProposee[k]:
                NbBienPlaces +=1
            if ConfigurationProposee[k] in ConfigurationCachee:
                NbMalPlaces +=1
                    
        NbMalPlaces = NbMalPlaces - NbBienPlaces
                    
        print("Nombres bien places:", NbBienPlaces)
        print("Nombres mal places:", NbMalPlaces)
                    
        if NbBienPlaces == 4:
            PartieGagnee = True
            print("Bravo, tu as gagne, en", NombreDeCoups, "coups!")
                            
        elif NombreDeCoups >= 15:
            PartieFinie = True
            print("Tu as perdu, tu as joue", NombreDeCoups, "coups!")
            print("La solution etait:", ConfigurationCachee)
            
    y = input("Voulez-vous rejouer? 0 non, 1 oui:  ")

    if int(y[0]) == 0:
        Rejouer = False

    elif int(y[0]) == 1:
        print("Bonne partie!")
        
        


    

    
    
    
    
    