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
plt.figure(figsize=(5,4.5))
fig = plt.figure(1)
x0=0.145
plotwidth=1.0-x0-0.025



mydata = np.loadtxt('pminusq_vs_B.txt',skiprows=0,unpack=True)
nq=mydata[0]
B=nq/3.0
Q2=mydata[1]
pminusq=mydata[2]
Q3=mydata[3]
#############################################

ax = fig.add_axes([x0,0.14,plotwidth,0.82])

plt.plot(B,Q2,linestyle='--',lw=4,color='b',label="$\langle Q^{(2)}\\rangle$")

#plt.plot(B,4*B,linestyle='--',lw=1,color='b',label="$\langle Q^{(2)}\\rangle$")

plt.plot(B,Q3,linestyle='dotted',lw=4,color='r',label="$\langle Q^{(3)}\\rangle$")
plt.plot(B,pminusq,linestyle='-',lw=4,color='g',label="$\langle p-q\\rangle$")

ax.tick_params(axis='both', which='major', labelsize=14)
ax.set_xticks(np.arange(0,10,2), minor=False)
ax.set_xticklabels(np.arange(0,10,2), minor=False, family='serif')
ax.set_xticks(np.arange(0,10,0.333333333333), minor=True)
ax.xaxis.set_major_formatter(ticker.FormatStrFormatter('%d'))
plt.xlim(-0.1,6.1)

ax.set_yticks(np.arange(0,50,5), minor=False)
ax.set_yticklabels(np.arange(0,50,5), minor=False, family='serif')
ax.set_yticks(np.arange(0,50,1), minor=True)
ax.yaxis.set_major_formatter(ticker.FormatStrFormatter('%0d'))
plt.ylim(-0.1,20.1)

plt.xlabel('$B=N_{\\rm quarks}/3$', fontsize=18, weight='normal')
plt.ylabel('$\langle p-q\\rangle$, $\langle Q^{(2)}\\rangle$, $\langle Q^{(3)}\\rangle$',fontsize=18)


  
ax.legend(framealpha=100, loc="upper left",fontsize='18')


#############################################

plt.savefig('pminusq.pdf',format='pdf')
os.system('open -a Preview pminusq.pdf')
