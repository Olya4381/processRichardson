import numpy as np
import matplotlib.pyplot as plt
#предельная форма планшереля
x_p=np.linspace(-1,1,20)
y_p=2/np.pi*(np.arcsin(x_p)*x_p+(1-x_p**2)**0.5)
x=x_p+y_p
y=-x_p+y_p
#предельная форма равновероятного процесса
x=np.linspace(0.0,5,100)
y=np.log(1-np.exp(-np.pi/np.sqrt(6)*x_p))*-np.sqrt(6)/np.pi
#опстроение
#plt.figure()
#plt.plot(x_p,y_p);
#plt.show()


with open('C:\\Users\\nosov\\Documents\\Visual Studio 2015\\Projects\\Diag_up_git\\Diag_up\\col_037_simple.txt') as inf:
    col=np.loadtxt(inf)
x2=(np.arange(col.shape[0])+1)/col.sum()**0.5
y2=np.copy(col)/col.sum()**0.5

with open('C:\\Users\\nosov\\Documents\\Visual Studio 2015\\Projects\\Diag_up_git\\Diag_up\\col_037_aver_int.txt') as inf:
    col=np.loadtxt(inf)
x3=(np.arange(col.shape[0])+1)/col.sum()**0.5
y3=np.copy(col)/col.sum()**0.5

with open('C:\\Users\\nosov\\Documents\\Visual Studio 2015\\Projects\\Diag_up_git\\Diag_up\\file1\\col_037_2m.txt') as inf:
    col=np.loadtxt(inf)
x1=(np.arange(col.shape[0])+1)/col.sum()**0.5
y1=np.copy(col)/col.sum()**0.5

plt.figure()
#plt.plot(x,y,label='Line 1',x1,y1,label='Line 2')
#plt.legend()
line_1, = plt.plot(x,y, label='Предельная')
line_2, = plt.plot(x1,y1,linewidth = 1, label='2m')
#line_3, = plt.plot(x2,y2,linewidth = 1, label='Простой проц')
#line_4, = plt.plot(x3,y3,linewidth = 1, label='Целое усреднение')
plt.legend(handles=[line_1, line_2])
plt.show()