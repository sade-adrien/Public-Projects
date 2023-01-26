# -*- coding: utf-8 -*-
"""
Created on Thu Dec  7 15:18:19 2017

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

cercle(0,1)

Centres=[[complex(1.5,0),'d'],[complex(0,1.5),'h'],[complex(-1.5,0),'g'],[complex(0,-1.5),'b']]

r=0.5

for n in range (5):
    
    #préparer la liste "centres" suivante
    
    CentresProchains=[]
    for a in Centres:
        omega,origine=a[0],a[1]
        cercle(omega,r)
        
        if origine=='d':
            CentresProchains+=[[omega+complex(1.5*r,0),'d'],[omega+complex(0,1.5*r),'h'],[omega+complex(0,-1.5*r),'b']]
        if origine=='g':
            CentresProchains+=[[omega+complex(0,1.5*r),'h'],[omega+complex(-1.5*r,0),'g'],[omega+complex(0,-1.5*r),'b']]
        if origine=='h':
            CentresProchains+=[[omega+complex(1.5*r,0),'d'],[omega+complex(0,1.5*r),'h'],[omega+complex(-1.5*r,0),'g']]
        if origine=='b':
            CentresProchains+=[[omega+complex(1.5*r,0),'d'],[omega+complex(-1.5*r,0),'g'],[omega+complex(0,-1.5*r),'b']]

    Centres,r=CentresProchains,(r/2)
        
        
plt.axis("scaled")








