import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import numpy as np
import os
from pylab import *
from matplotlib import ticker
from matplotlib.ticker import ScalarFormatter
import matplotlib.patches as patches
sformatter=ScalarFormatter(useOffset=True,useMathText=True)
sformatter.set_scientific(True)
sformatter.set_powerlimits((-2,3))

#plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))

font = {'family' : 'serif',
        'weight' : 'normal',
        'size'   : 14}
plt.rc('font', **font)
plt.rc('text', usetex=False)
plt.figure(figsize=(5,5))
fig = plt.figure(1)
x0=0.11
plotwidth=1.0-x0-0.025


delp_gluon=[-2,-1,1,2,1,-1]
delq_gluon=[1,2,-2,-1,1,-1]
delp_quark=[1,0,-1]
delq_quark=[0,-1,1]
delp_antiquark=[-1,0,1]
delq_antiquark=[0,1,-1]

####################################

gluondata = np.loadtxt('pq3_gluon.txt',skiprows=0,unpack=True)
pgluon=gluondata[0]
qgluon=gluondata[1]
Q2gluon=gluondata[2]
Q3gluon=gluondata[3]

quarkdata = np.loadtxt('pq3_quark.txt',skiprows=0,unpack=True)
pquark=quarkdata[0]
qquark=quarkdata[1]
Q2quark=quarkdata[2]
Q3quark=quarkdata[3]

antiquarkdata = np.loadtxt('pq3_antiquark.txt',skiprows=0,unpack=True)
pantiquark=antiquarkdata[0]
qantiquark=antiquarkdata[1]
Q2antiquark=antiquarkdata[2]
Q3antiquark=antiquarkdata[3]

#############################################

ax = fig.add_axes([x0,x0,plotwidth,plotwidth])

xx=[0,50]
yy=[0,50]
plt.plot(xx,yy,linestyle='--',lw=1,color='k')

plt.plot(pgluon,qgluon,linestyle='None',marker='o',markersize=10,color='k',label='gluon-like')
plt.plot(pquark,qquark,linestyle='None',marker=(3,0,180),markersize=12,color='r',label='quark-like')
plt.plot(pantiquark,qantiquark,linestyle='None',marker=(3,0,0),markersize=12,color='g',label='antiquark-like')

ax.tick_params(axis='both', which='major', labelsize=14)
ax.set_xticks(np.arange(0,50,1), minor=False)
ax.set_xticklabels(np.arange(0,50,1), minor=False, family='serif')
ax.set_xticks(np.arange(0,50,1), minor=True)
ax.xaxis.set_major_formatter(ticker.FormatStrFormatter('%d'))
plt.xlim(-0.1,3.1)

ax.set_yticks(np.arange(0,50,1), minor=False)
ax.set_yticklabels(np.arange(0,50,1), minor=False, family='serif')
ax.set_yticks(np.arange(00,50,1), minor=True)
ax.yaxis.set_major_formatter(ticker.FormatStrFormatter('%0d'))
plt.ylim(-0.1,3.1)

plt.xlabel('$p$', fontsize=20, weight='normal',labelpad=-2)
plt.ylabel('$q$',fontsize=20,labelpad=-2)

p0=3
q0=0
p2=patches.FancyArrowPatch((p0,q0), (p0-2,q0+1), arrowstyle='-|>', mutation_scale=20, lw=3, color='k')
ax.add_patch(p2)
p0=1
q0=1
p2=patches.FancyArrowPatch((p0,q0), (p0-1,q0-1), arrowstyle='-|>', mutation_scale=20, lw=3, color='k')
ax.add_patch(p2)

p0=3
q0=0
p2=patches.FancyArrowPatch((p0,q0), (p0-1,q0), arrowstyle='-|>', mutation_scale=20, lw=3, color='g')
ax.add_patch(p2)
p0=2
q0=0
p2=patches.FancyArrowPatch((p0,q0), (p0-1,q0), arrowstyle='-|>', mutation_scale=20, lw=3, color='g')
ax.add_patch(p2)
p0=1
q0=0
p2=patches.FancyArrowPatch((p0,q0), (p0-1,q0), arrowstyle='-|>', mutation_scale=20, lw=3, color='g')
ax.add_patch(p2)

text(0.4,0.09,'b) decay via 3 quarks',fontsize=18,family='sans', color='g')
text(1.15,0.116,'a) decay via 2 gluons',fontsize=18,family='sans', color='k',rotation=-26.565)

plt.savefig('pq3_2gluon.pdf',format='pdf')
os.system('open -a Preview pq3_2gluon.pdf')
