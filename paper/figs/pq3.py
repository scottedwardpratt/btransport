import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import numpy as np
import os
from pylab import *
from matplotlib import ticker
from matplotlib.ticker import ScalarFormatter
sformatter=ScalarFormatter(useOffset=True,useMathText=True)
sformatter.set_scientific(True)
sformatter.set_powerlimits((-2,3))

#plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))

font = {'family' : 'serif',
        'weight' : 'normal',
        'size'   : 14}
plt.rc('font', **font)
plt.rc('text', usetex=False)
plt.figure(figsize=(6,5))
fig = plt.figure(1)
ax = fig.add_axes([0.15,0.12,0.8,0.8])

gluondata = np.loadtxt('pq3_gluon.txt',skiprows=0,unpack=True)
pgluon=gluondata[0]
qgluon=gluondata[1]

quarkdata = np.loadtxt('pq3_quark.txt',skiprows=0,unpack=True)
pquark=quarkdata[0]
qquark=quarkdata[1]

antiquarkdata = np.loadtxt('pq3_antiquark.txt',skiprows=0,unpack=True)
pantiquark=antiquarkdata[0]
qantiquark=antiquarkdata[1]

plt.plot(pgluon,qgluon,linestyle='None',marker='o',color='r',label='pure glue')
plt.plot(pquark,qquark,linestyle='None',marker=(3,0,0),color='g',label='quark-like')
plt.plot(pantiquark,qantiquark,linestyle='None',marker=(3,0,180),color='b',label='antiquark-like')


ax.tick_params(axis='both', which='major', labelsize=14)

ax.set_xticks(np.arange(0,50,2), minor=False)
ax.set_xticklabels(np.arange(0,50,2), minor=False, family='serif')
ax.set_xticks(np.arange(00,50,1), minor=True)
ax.xaxis.set_major_formatter(ticker.FormatStrFormatter('%0.1f'))
plt.xlim(0,20)

ax.set_yticks(np.arange(0,50,2), minor=False)
ax.set_yticklabels(np.arange(0,50,2), minor=False, family='serif')
ax.set_yticks(np.arange(00,50,1), minor=True)
ax.yaxis.set_major_formatter(ticker.FormatStrFormatter('%0.1f'))
plt.ylim(0,20)
#ax.set_yticks(0.1:1.0:10.0:100.0, minor=True)
#ax.yaxis.set_major_formatter(ticker.FormatStrFormatter('%.1e'))
ax.yaxis.set_major_formatter(sformatter)

ax.legend()

plt.xlabel('$p$', fontsize=18, weight='normal')
plt.ylabel('$q$',fontsize=18)

plt.savefig('pq3.pdf',format='pdf')
os.system('open -a Preview pq3.pdf')
