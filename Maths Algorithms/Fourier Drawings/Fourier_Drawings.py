#!/usr/bin/env python
# coding: utf-8

# In[2]:
import os
os.chdir('C:\\Users\\sade-\\Desktop\\Fourier Drawings')


import numpy as np
import matplotlib.pyplot as plt
import cv2


# In[ ]:


original_image = cv2.imread('elephant.jpg')
cv2.imshow('original image', original_image)



# In[223]:


gray_image = cv2.cvtColor(original_image, cv2.COLOR_BGR2GRAY)
(thresh, blackandwhite_image) = cv2.threshold(gray_image, 240, 255, cv2.THRESH_BINARY)

cv2.imshow('black and white image', blackandwhite_image)


# In[224]:


contours, hierarchy = cv2.findContours(blackandwhite_image,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
numbers_points = [len(cnt) for cnt in contours]

final_contour = contours[np.argmax(numbers_points)]

X = np.array(final_contour)[:,:,0]
Y = -np.array(final_contour)[:,:,1]

'''
X, Y = [], []
for c in contours:
    X = np.append(X, c[:,:,0][:,0])
    Y = np.append(Y, c[:,:,1][:,0])
Y = -Y
X = X[Y<-10]
Y = Y[Y<-10]
X = X[Y>-275]
Y = Y[Y>-275]
'''

plt.plot(X, Y, color='black', marker='x', linestyle='')
plt.axes().set_aspect('equal')


# In[226]:


time = np.linspace(0,10, len(X))

fig, axs = plt.subplots(2)
fig.suptitle('Points coordinates regarding to time drawing')
axs[0].plot(time, X, color='blue')
axs[1].plot(time, Y, color='red')


# In[227]:


complex_coordinates = [complex(x, y) for (x, y) in zip(X, Y)]

def fourier_fct(k):
  return [complex_coordinates[i]*np.exp(-2*np.pi*k*t*1j/time[-1]) for (i, t) in enumerate(time)]


# In[257]:


from scipy.integrate import trapz

n = 50    #number of circles
rank_coeff = np.array([0] + [(k//2+1)*int(k%2==0) + (-k//2)*int(k%2==1) for k in range(0,n)])
coeff_fourier = np.array([[1/time[-1] * trapz(fourier_fct(k), time), k] for k in rank_coeff])

spectrum = np.absolute(coeff_fourier[:,0])
plt.figure()
plt.vlines(rank_coeff, [0], spectrum, color='r')
plt.xlabel('frequencies')
plt.ylabel('amplitude')


# In[1]:


from matplotlib import animation

fig = plt.figure()
fig.set_dpi(100)
fig.set_size_inches(15,15)
ax = plt.axes(xlim=(100, 500), ylim=(-400, 0))
ax.set_aspect('equal')

patchs = [plt.Circle((5, 5), radius=np.abs(coeff_fourier[p][0]), color='black', fill=False, alpha=0.5, linewidth=1/np.log(p+1)) for p in range(1,n+1)]     #moving circles
patchs2 = [plt.Circle((5, 5), radius=1, color='green', fill=True, alpha=0.5, linewidth=1/np.log(p+1)) for p in range(0,n)] + [plt.Circle((5, 5), radius=2, color='red', fill=True)]   #moving points
arrows = [ax.plot([],[], color='green', linestyle='--', alpha=0.5, linewidth=1/np.log(p+1))[0] for p in range(1,n+1)]    #drawing moving radius
curve, = ax.plot([],[], color='blue')     #drawing curve

def init():
    for patch in patchs:
        patch.center = (5, 5)
        ax.add_patch(patch)
    for patch in patchs2:
        patch.center = (5, 5)
        ax.add_patch(patch)
        
    return patchs + patchs2


x3, y3 = [], []
def animate(t):
    t = t/9999*100
    
    x, y = [], []
    x2, y2 = [], []
    x4, y4 =[], []
    
    
    for k in range(n+1):
        if k==0:
            x.append(np.real(coeff_fourier[k][0]*np.exp(2*np.pi*coeff_fourier[k][1]*1j*t/time[-1])))
            y.append(np.imag(coeff_fourier[k][0]*np.exp(2*np.pi*coeff_fourier[k][1]*1j*t/time[-1])))
            
            x2.append(np.real(coeff_fourier[k][0]*np.exp(2*np.pi*coeff_fourier[k][1]*1j*t/time[-1])))
            y2.append(np.imag(coeff_fourier[k][0]*np.exp(2*np.pi*coeff_fourier[k][1]*1j*t/time[-1])))
        else:
            x.append(x[-1] + np.real(coeff_fourier[k][0]*np.exp(2*np.pi*coeff_fourier[k][1]*1j*t/time[-1])))
            y.append(y[-1] + np.imag(coeff_fourier[k][0]*np.exp(2*np.pi*coeff_fourier[k][1]*1j*t/time[-1])))
            
            x2.append(x2[-1] + np.real(coeff_fourier[k][0]*np.exp(2*np.pi*coeff_fourier[k][1]*1j*t/time[-1])))
            y2.append(y2[-1] + np.imag(coeff_fourier[k][0]*np.exp(2*np.pi*coeff_fourier[k][1]*1j*t/time[-1])))

    x3.append(x2[-1])
    y3.append(y2[-1])
    
    for k in range(len(x)-1):
        x4.append(np.linspace(x[k], x[k+1], 100))
        y4.append(np.linspace(y[k], y[k+1], 100))

    for (i, patch) in enumerate(patchs):
         patch.center = (x[i], y[i])
    for (i, patch) in enumerate(patchs2):
         patch.center = (x2[i], y2[i])
    curve.set_data(x3, y3)
    for (i, arrow) in enumerate(arrows):
         arrow.set_data(x4[i], y4[i])
    
         
    return patchs + patchs2 + [curve] + arrows


anim = animation.FuncAnimation(fig, animate, 
                               init_func=init, 
                               frames=10000, 
                               interval=10,
                               blit=True)

plt.show()









