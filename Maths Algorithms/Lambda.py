# -*- coding: utf-8 -*-
"""
Created on Thu Nov 30 13:09:59 2017

@author: charlie.pauvre
"""

import matplotlib.pyplot as plt
import numpy as np
import math as m

#################################################################

def fonction(x,a):
        y=np.exp(x)*(1+a*(x-1))
        return y


def f(x):
    y=(np.exp(x))/x
    return y

def g(x):
    y=(2/(x+1))*np.exp(x)
    return y
    
#################################################################

plt.figure("Graphes")

u=np.linspace(-4,0,1000)
v=np.linspace(0,4,1000)
w=np.linspace(-4,-1.25,1000)
z=np.linspace(-.75,4,1000)
t=np.linspace(-3,1.25,1000)

Yu=f(u)
Yv=f(v)
Yw=g(w)
Yz=g(z)

for a in range (-6,6):
    Yt=fonction(t,a/2.)
    plt.plot(t,Yt,"blue")

plt.plot(u,Yu,"red")
plt.plot(v,Yv,"red")
plt.plot(w,Yw,"green")
plt.plot(z,Yz,"green")

plt.plot([0,0],[-5,5],"black")
plt.plot([-5,5],[0,0],"black")

plt.axis([-5,5,-5,5])
plt.grid()
plt.xlabel("x")
plt.ylabel("y")
plt.title("Courbes")
