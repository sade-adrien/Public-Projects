# -*- coding: utf-8 -*-
"""
Created on Thu Sep 14 13:15:39 2017

@author: adrien.sade

Le nombre mysterieux
"""

import random 

NombreMystere = random.randint(1,1000)
NombrePropose = 0
NombreDeCoups = 0
while NombrePropose != NombreMystere:
    NombreDeCoups += 1
    if NombreDeCoups > 1:
        if NombrePropose < NombreMystere:
            print("Trop petit tu dois rejouer")
        else:
                print("Trop grand tu dois rejouer")
    NombrePropose = int(input("Donne un nombre"))
print("Tu as trouve le nombre mystere en ", NombreDeCoups, "coups.")