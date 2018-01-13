import numpy as np
import matplotlib.pyplot as plt
x_p=np.linspace(-1,1,20)
y_p=2/np.pi*(np.arcsin(x_p)*x_p+(1-x_p**2)**0.5)
x=x_p+y_p
y=-x_p+y_p

col=0
with open('C:\\Users\\nosov\\Documents\\Visual Studio 2015\\Projects\\Diag_up_git\\Diag_up\\col_037_TEST1.txt') as inf:
    col=np.loadtxt(inf)
x1=(np.arange(col.shape[0])+1)/col.sum()**0.5
y1=np.copy(col)/col.sum()**0.5

plt.figure()
plt.plot(x,y,'r',x1,y1,'b')
plt.show()