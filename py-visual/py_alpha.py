import numpy as np
import matplotlib.pyplot as plt

alph=0
with open('C:\\Users\\nosov\\Documents\\Visual Studio 2015\\Projects\\Diag_up_git\\Diag_up\\alpha_10x100_2.txt') as inf:
    alph=np.loadtxt(inf)


plt.figure()
plt.plot(alph[:,0],alph[:,1])
plt.show()
