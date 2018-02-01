import numpy as np
import matplotlib.pyplot as plt

alph=0
with open('C:\\Users\\nosov\\Documents\\Visual Studio 2015\\Projects\\Diag_up_git\\Diag_up\\alpha\\alpha_10x100_2.txt') as inf:
    alph_10x100=np.loadtxt(inf)

with open('C:\\Users\\nosov\\Documents\\Visual Studio 2015\\Projects\\Diag_up_git\\Diag_up\\alpha_100x20_1.txt') as inf:
    alph_100x20=np.loadtxt(inf)



plt.figure()
plt.plot(alph_10x100[:,0],alph_10x100[:,1],alph_100x20[:,0],alph_100x20[:,1])
plt.title('Синий 10x100 \n Оранжевый 100x20')
plt.show()
