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
plt.figure(figsize=(9,4.5))
fig = plt.figure(1)
x0=0.075
plotwidth=0.5-x0-0.025


delp_gluon=[-2,-1,1,2,1,-1]
delq_gluon=[1,2,-2,-1,1,-1]
delp_quark=[1,0,-1]
delq_quark=[0,-1,1]
delp_antiquark=[-1,0,1]
delq_antiquark=[0,1,-1]

####################################
p0=6
q0=3
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

ax = fig.add_axes([x0,0.14,plotwidth,0.8])

xx=[0,50]
yy=[0,50]
plt.plot(xx,yy,linestyle='--',lw=1,color='k')

plt.plot(pgluon,qgluon,linestyle='None',marker='o',color='k',label='gluon-like')
plt.plot(pquark,qquark,linestyle='None',marker=(3,0,180),color='r',label='quark-like')
plt.plot(pantiquark,qantiquark,linestyle='None',marker=(3,0,0),color='g',label='antiquark-like')

ax.tick_params(axis='both', which='major', labelsize=14)
ax.set_xticks(np.arange(0,50,3), minor=False)
ax.set_xticklabels(np.arange(0,50,3), minor=False, family='serif')
ax.set_xticks(np.arange(00,50,1), minor=True)
ax.xaxis.set_major_formatter(ticker.FormatStrFormatter('%d'))
plt.xlim(-0.1,9.1)

ax.set_yticks(np.arange(0,50,3), minor=False)
ax.set_yticklabels(np.arange(0,50,3), minor=False, family='serif')
ax.set_yticks(np.arange(00,50,1), minor=True)
ax.yaxis.set_major_formatter(ticker.FormatStrFormatter('%0d'))
plt.ylim(-0.1,9.1)

plt.xlabel('$p$', fontsize=18, weight='normal')
plt.ylabel('$q$',fontsize=18)

for i in range(0,3):
  #plt.arrow(p0,q0,delp_quark[i],delq_quark[i], color='r',head_width=0.25, head_length=0.4, length_includes_head=True)
  
  #arrowstyle="Simple, tail_width=0.25,head_width=0.25, head_length=0.25"
  
  p2=patches.FancyArrowPatch((p0,q0), (p0+delp_quark[i],q0+delq_quark[i]), arrowstyle='-|>', ls='--', mutation_scale=10, lw=2, color='r')
  ax.add_patch(p2)
  #plt.arrow(p0,q0,delp_antiquark[i],delq_antiquark[i], color='g',head_width=0.25, head_length=0.4, length_includes_head=True)
  
  p2=patches.FancyArrowPatch((p0,q0), (p0+delp_antiquark[i],q0+delq_antiquark[i]), arrowstyle='-|>', mutation_scale=10, lw=2,color='g')
  ax.add_patch(p2)

for i in range(0,6):
  #plt.arrow(p0,q0,delp_gluon[i],delq_gluon[i], color='k',head_width=0.25, head_length=0.4, length_includes_head=True)
  p2=patches.FancyArrowPatch((p0,q0), (p0+delp_gluon[i],q0+delq_gluon[i]), arrowstyle='-|>', mutation_scale=20, lw=3, color='k')
  ax.add_patch(p2)
  #p2=patches.FancyArrowPatch((p0,q0), (p0+delp_gluon[i],q0+delq_gluon[i]), arrowstyle=arrowstyle, ls='--', lw=2, color='k')
  ax.add_patch(p2)
  
ax.legend(framealpha=100, loc="upper left")

#############################################

ax = fig.add_axes([x0+0.5,0.14,plotwidth,0.8])
plt.plot(Q3gluon,Q2gluon,linestyle='None',marker='o',color='k',label='pure glue')
plt.plot(Q3quark,Q2quark,linestyle='None',marker=(3,0,180),color='r',label='quark-like')
plt.plot(Q3antiquark,Q2antiquark,linestyle='None',marker=(3,0,0),color='g',label='antiquark-like')

ax.tick_params(axis='both', which='major', labelsize=14)
ax.set_xticks(np.arange(-2000,2000,50), minor=False)
ax.set_xticklabels(np.arange(-2000,2000,50), minor=False, family='serif')
ax.set_xticks(np.arange(-2000,2000,25), minor=True)
ax.xaxis.set_major_formatter(ticker.FormatStrFormatter('%0d'))
plt.xlim(-103,103)

ax.set_yticks(np.arange(0,1000,25), minor=False)
ax.set_yticklabels(np.arange(0,1000,25), minor=False, family='serif')
ax.set_yticks(np.arange(00,1000,5), minor=True)
ax.yaxis.set_major_formatter(ticker.FormatStrFormatter('%0d'))
plt.ylim(-1,60.0001)
#ax.set_yticks(0.1:1.0:10.0:100.0, minor=True)
#ax.yaxis.set_major_formatter(ticker.FormatStrFormatter('%.1e'))
ax.yaxis.set_major_formatter(sformatter)

plt.xlabel('$\langle Q^{(3)}\\rangle$', fontsize=18, weight='normal')
plt.ylabel('$\langle Q^{(2)}\\rangle$',fontsize=18)

Q20=(p0*p0+q0*q0+3.0*p0+3.0*q0+p0*q0)/3.0;
Q30=(p0-q0)*(3.0+p0+2.0*q0)*(3.0+q0+2.0*p0)/18.0;
for i in range(0,3):
  pf=p0+delp_quark[i]
  qf=q0+delq_quark[i]
  Q2f=(pf*pf+qf*qf+3.0*pf+3.0*qf+pf*qf)/3.0;
  Q3f=(pf-qf)*(3.0+pf+2.0*qf)*(3.0+qf+2.0*pf)/18.0;
  delQ2=Q2f-Q20
  delQ3=Q3f-Q30
  #plt.arrow(Q30,Q20,delQ3,delQ2, color='r',head_width=0.25, head_length=0.4, length_includes_head=True)
  p2=patches.FancyArrowPatch((Q30,Q20), (Q3f,Q2f), arrowstyle='-|>', mutation_scale=15, lw=2, ls='--', color='r')
  ax.add_patch(p2)
  
  
  pf=p0+delp_antiquark[i]
  qf=q0+delq_antiquark[i]
  Q2f=(pf*pf+qf*qf+3.0*pf+3.0*qf+pf*qf)/3.0;
  Q3f=(pf-qf)*(3.0+pf+2.0*qf)*(3.0+qf+2.0*pf)/18.0;
  delQ2=Q2f-Q20
  delQ3=Q3f-Q30
  #plt.arrow(Q30,Q20,delQ3,delQ2, color='g',head_width=0.25, head_length=0.4, length_includes_head=True)
  p2=patches.FancyArrowPatch((Q30,Q20), (Q3f,Q2f), arrowstyle='-|>', mutation_scale=20, lw=2, color='g')
  ax.add_patch(p2)

for i in range(0,6):
  pf=p0+delp_gluon[i]
  qf=q0+delq_gluon[i]
  Q2f=(pf*pf+qf*qf+3.0*pf+3.0*qf+pf*qf)/3.0;
  Q3f=(pf-qf)*(3.0+pf+2.0*qf)*(3.0+qf+2.0*pf)/18.0;
  delQ2=Q2f-Q20
  delQ3=Q3f-Q30
  #plt.arrow(Q30,Q20,delQ3,delQ2, color='k',head_width=5, head_length=6.0, length_includes_head=True)
  #p2=patches.FancyArrowPatch((Q30,Q20), (Q3f,Q2f), arrowstyle='-|>', mutation_scale=20, color='k')
  #ax.add_patch(p2)

#############################################

plt.savefig('pq3.pdf',format='pdf')
os.system('open -a Preview pq3.pdf')
