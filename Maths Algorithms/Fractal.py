# -*- coding: utf-8 -*-
"""
Created on Thu Nov 30 14:20:34 2017

@author: charlie.pauvre
"""

import matplotlib.pyplot as plt
import numpy as np
import math as m

#################################################################

def cercle(a,r):
    Z=[a+r*complex(m.cos(2*k*m.pi/100),m.sin(2*k*m.pi/100)) for k in range (101)]
    
    X,Y=[z.real for z in Z],[z.imag for z in Z]

    plt.plot(X,Y)


#################################################################

plt.figure()

centres=[0]
r = 1

for n in range (10):
    #tracer les cercles dont les centres sont dans "centres"
    for x in centres:
        cercle(x,r)
        
        



    #préparer la liste "centres" suivante

    CentresProchains=[]
    
    for a in centres:
        cercle(a,r)
        CentresProchains+=[a+complex(1.5*r,0),a+complex(0,-1.5*r)]
    centres=CentresProchains
    
    #changer r
    r=r/2
    
plt.axis("scaled")


